#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <random>
#include <fstream>
#include <sstream>
#include "npc.hpp"
#include "dragon.hpp"
#include "knight.hpp"
#include "elf.hpp"
#include "INpcFactory.hpp"
#include "npc_factory.hpp"
#include "fight_visitor.hpp"
#include "IFightObserver.hpp"
#include "ConsoleLogger.hpp"
#include "FileLogger.hpp"

class BattleManager {
private:
    std::vector<NPCPtr> npcs;
    std::vector<IFightObserverPtr> observers;

public:
    void addObserver(const IFightObserverPtr& obs) {
        observers.push_back(obs);
    }

    void notifyObservers(const std::string& message) {
        for (const auto& observer : observers) {
            observer->onFightOutcome(message);
        }
    }

    void addNPC(const NPCPtr& npc) {
        npcs.push_back(npc);
    }

    void printNPCs() const {
        std::cout << "NPCs alive: " << npcs.size() << "\n";
        for (const auto& npc : npcs) {
            if (npc->isAlive()) {
                auto pos = npc->getPosition();
                std::cout << npc->getType() << " " << npc->getName() 
                          << " at (" << pos.first << ", " << pos.second << ")\n";
            }
        }
    }

    void battle(double maxDistance) {
        bool changes = true;
        
        while (changes && npcs.size() >= 2) {
            changes = false;
            
            for (size_t i = 0; i < npcs.size(); ++i) {
                if (!npcs[i]->isAlive()) continue;
                
                for (size_t j = i + 1; j < npcs.size(); ++j) {
                    if (!npcs[j]->isAlive()) continue;
                    
                    NPCPtr npc1 = npcs[i];
                    NPCPtr npc2 = npcs[j];
                    
                    if (npc1->distanceTo(npc2) <= maxDistance) {
                        bool npc1WasAlive = npc1->isAlive();
                        bool npc2WasAlive = npc2->isAlive();
                        
                        auto visitor1 = std::make_shared<FightVisitor>(npc1);
                        npc2->accept(visitor1);
                        
                        if (npc1->isAlive() && npc2->isAlive()) {
                            auto visitor2 = std::make_shared<FightVisitor>(npc2);
                            npc1->accept(visitor2);
                        }
                        
                        bool someoneDied = (npc1WasAlive && !npc1->isAlive()) || (npc2WasAlive && !npc2->isAlive());
                        
                        if (someoneDied) {
                            changes = true;
                            std::stringstream ss;
                            
                            if (!npc1->isAlive() && !npc2->isAlive()) {
                                ss << "BOTH DIED: " << npc1->getType() << " (" << npc1->getName() 
                                   << ") and " << npc2->getType() << " (" << npc2->getName() 
                                   << ") killed each other.";
                            } else if (!npc2->isAlive()) {
                                ss << "KILL: " << npc1->getType() << " (" << npc1->getName() 
                                   << ") killed " << npc2->getType() << " (" << npc2->getName() << ").";
                            } else if (!npc1->isAlive()) {
                                ss << "KILL: " << npc2->getType() << " (" << npc2->getName() 
                                   << ") killed " << npc1->getType() << " (" << npc1->getName() << ").";
                            }
                            
                            notifyObservers(ss.str());
                        }
                    }
                }
            }
            
            if (changes) {
                npcs.erase(std::remove_if(npcs.begin(), npcs.end(),
                           [](const NPCPtr& npc) { return !npc->isAlive(); }),
                           npcs.end());
            }
        }
    }

    void saveToFile(const std::string& filename) {
        std::ofstream file(filename);
        for (const auto& npc : npcs) {
            if (npc->isAlive()) {
                npc->save(file);
            }
        }
    }

    size_t getAliveCount() const { 
        return std::count_if(npcs.begin(), npcs.end(),
                            [](const NPCPtr& npc) { return npc->isAlive(); });
    }
};

int main() {
    BattleManager manager;
    
    manager.addObserver(ConsoleLogger::get());
    manager.addObserver(FileLogger::get());

    auto factory = std::make_shared<NpcFactory>();
    factory->registerCreator("Dragon", [](const std::string& name, int x, int y) {
        return std::make_shared<Dragon>(name, x, y);
    });
    factory->registerCreator("Knight", [](const std::string& name, int x, int y) {
        return std::make_shared<Knight>(name, x, y);
    });
    factory->registerCreator("Elf", [](const std::string& name, int x, int y) {
        return std::make_shared<Elf>(name, x, y);
    });

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> typeDist(0, 2);
    std::uniform_int_distribution<> coordDist(0, 100);
    std::uniform_int_distribution<> nameDist(1, 1000);

    std::vector<std::string> types = {"Dragon", "Knight", "Elf"};

    for (int i = 0; i < 50; ++i) {
        std::string type = types[typeDist(gen)];
        std::string name = "NPC_" + std::to_string(nameDist(gen));
        int x = coordDist(gen);
        int y = coordDist(gen);
        
        auto npc = factory->createNPC(type, name, x, y);
        manager.addNPC(npc);
    }

    std::cout << "Initial NPCs:\n";
    manager.printNPCs();

    for (int distance = 10; distance <= 100 && manager.getAliveCount() > 1; distance += 10) {
        std::cout << "\n=== Battle with distance " << distance << " ===\n";
        manager.battle(distance);
        manager.printNPCs();
    }

    manager.saveToFile("survivors.txt");
    std::cout << "\nSurvivors saved to survivors.txt\n";

    return 0;
}