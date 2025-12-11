#include <gtest/gtest.h>
#include <memory>
#include <sstream>
#include "dragon.hpp"
#include "knight.hpp"
#include "elf.hpp"
#include "fight_visitor.hpp"

TEST(NPCBasic, Creation) {
    Dragon d("Smaug", 10, 20);
    EXPECT_EQ(d.getName(), "Smaug");
    auto pos = d.getPosition();
    EXPECT_EQ(pos.first, 10);
    EXPECT_EQ(pos.second, 20);
    EXPECT_TRUE(d.isAlive());
    EXPECT_EQ(d.getType(), "Dragon");
}

TEST(NPCDistance, DistanceCalculation) {
    auto a = std::make_shared<Knight>("Arthur", 0, 0);
    auto b = std::make_shared<Elf>("Legolas", 3, 4);
    double dist = a->distanceTo(b);
    EXPECT_NEAR(dist, 5.0, 0.0001);
}

TEST(NPCFight, KnightKillsDragon) {
    auto dragon = std::make_shared<Dragon>("Fafnir", 100, 100);
    auto knight = std::make_shared<Knight>("Lancelot", 105, 100);
    
    EXPECT_TRUE(dragon->isAlive());
    EXPECT_TRUE(knight->isAlive());
    
    auto visitor = std::make_shared<FightVisitor>(knight);
    dragon->accept(visitor);
    
    EXPECT_FALSE(dragon->isAlive());
    EXPECT_TRUE(knight->isAlive());
}

TEST(NPCFight, ElfKillsKnight) {
    auto elf = std::make_shared<Elf>("Elrond", 50, 50);
    auto knight = std::make_shared<Knight>("Galahad", 51, 50);
    
    auto visitor = std::make_shared<FightVisitor>(elf);
    knight->accept(visitor);
    
    EXPECT_FALSE(knight->isAlive());
    EXPECT_TRUE(elf->isAlive());
}

TEST(NPCFight, DragonKillsElf) {
    auto dragon = std::make_shared<Dragon>("Alduin", 10, 10);
    auto elf = std::make_shared<Elf>("Galadriel", 15, 10);
    
    auto visitor = std::make_shared<FightVisitor>(dragon);
    elf->accept(visitor);
    
    EXPECT_FALSE(elf->isAlive());
    EXPECT_TRUE(dragon->isAlive());
}

TEST(NPCFight, MutualKill) {
    auto dragon1 = std::make_shared<Dragon>("Smaug", 100, 100);
    auto dragon2 = std::make_shared<Dragon>("Glaurung", 100, 100);
    
    auto visitor1 = std::make_shared<FightVisitor>(dragon1);
    dragon2->accept(visitor1);
    
    EXPECT_FALSE(dragon1->isAlive());
    EXPECT_FALSE(dragon2->isAlive());
}

TEST(NPCSave, SaveToStream) {
    auto npc = std::make_shared<Elf>("Galadriel", 30, 40);
    
    std::ostringstream oss;
    npc->save(oss);
    std::string output = oss.str();
    
    EXPECT_FALSE(output.empty());
    EXPECT_NE(output.find("Galadriel"), std::string::npos);
    EXPECT_NE(output.find("30"), std::string::npos);
    EXPECT_NE(output.find("40"), std::string::npos);
}

TEST(NPCDeath, DieOnce) {
    auto dragon = std::make_shared<Dragon>("Victim", 0, 0);
    auto knight = std::make_shared<Knight>("Killer", 5, 0);
    
    auto visitor = std::make_shared<FightVisitor>(knight);
    dragon->accept(visitor);
    
    EXPECT_FALSE(dragon->isAlive());
    
    dragon->accept(visitor);
    EXPECT_FALSE(dragon->isAlive());
}

TEST(NPCFight, KnightVsKnightNoDamage) {
    auto knight1 = std::make_shared<Knight>("Arthur", 0, 0);
    auto knight2 = std::make_shared<Knight>("Lancelot", 0, 0);
    
    auto visitor = std::make_shared<FightVisitor>(knight1);
    knight2->accept(visitor);
    
    EXPECT_TRUE(knight1->isAlive());
    EXPECT_TRUE(knight2->isAlive());
}

TEST(NPCFight, ElfVsElfNoDamage) {
    auto elf1 = std::make_shared<Elf>("Legolas", 0, 0);
    auto elf2 = std::make_shared<Elf>("Elrond", 0, 0);
    
    auto visitor = std::make_shared<FightVisitor>(elf1);
    elf2->accept(visitor);
    
    EXPECT_TRUE(elf1->isAlive());
    EXPECT_TRUE(elf2->isAlive());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
