#include <gtest/gtest.h>
#include "dragon.hpp"
#include "knight.hpp"
#include "elf.hpp"
#include <cmath>
#include <sstream>

TEST(NPCTest, InitialState) {
    auto dragon = std::make_shared<Dragon>("Smaug", 0, 0);
    
    EXPECT_TRUE(dragon->isAlive());
    EXPECT_EQ(dragon->getName(), "Smaug");
    EXPECT_EQ(dragon->getType(), "Dragon");
    
    auto pos = dragon->getPosition();
    EXPECT_EQ(pos.first, 0);
    EXPECT_EQ(pos.second, 0);
}

TEST(NPCTest, KillNPC) {
    auto knight = std::make_shared<Knight>("Arthur", 10, 10);
    
    EXPECT_TRUE(knight->isAlive());
    knight->kill();
    EXPECT_FALSE(knight->isAlive());
}

TEST(NPCTest, DistanceCalculation) {
    auto dragon = std::make_shared<Dragon>("D", 0, 0);
    auto knight = std::make_shared<Knight>("K", 3, 4);
    
    std::shared_ptr<NPC> npc_knight = knight;
    double distance = dragon->distanceTo(npc_knight);
    EXPECT_DOUBLE_EQ(distance, 5.0);
}

TEST(NPCTest, DistanceToNull) {
    auto elf = std::make_shared<Elf>("E", 0, 0);
    double distance = elf->distanceTo(nullptr);
    EXPECT_TRUE(std::isinf(distance));
}

TEST(NPCTest, SaveToStream) {
    auto dragon = std::make_shared<Dragon>("Smaug", 100, 200);
    std::ostringstream oss;
    dragon->save(oss);
    
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
    EXPECT_NE(output.find("Smaug"), std::string::npos);
}

// Отдельная строка для EOF
