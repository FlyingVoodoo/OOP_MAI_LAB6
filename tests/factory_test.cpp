                                                                                                                                                                                                                                                                                                        #include <gtest/gtest.h>
#include <sstream>
#include "npc_factory.hpp"
#include "dragon.hpp"
#include "knight.hpp"
#include "elf.hpp"

static std::shared_ptr<NpcFactory> createFactory() {
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
    return factory;
}

TEST(FactoryTest, CreateNPC) {
    auto factory = createFactory();
    
    auto dragon = factory->createNPC("Dragon", "Fafnir", 10, 20);
    auto knight = factory->createNPC("Knight", "Lancelot", 30, 40);
    auto elf = factory->createNPC("Elf", "Legolas", 50, 60);

    EXPECT_NE(dragon, nullptr);
    EXPECT_NE(knight, nullptr);
    EXPECT_NE(elf, nullptr);

    EXPECT_EQ(dragon->getType(), "Dragon");
    EXPECT_EQ(knight->getType(), "Knight");
    EXPECT_EQ(elf->getType(), "Elf");
    
    auto pos = dragon->getPosition();
    EXPECT_EQ(pos.first, 10);
    EXPECT_EQ(pos.second, 20);
}TEST(FactoryTest, Serialization) {
    auto factory = createFactory();
    auto dragon = factory->createNPC("Dragon", "Smaug", 100, 200);
    
    std::stringstream ss;
    dragon->save(ss);
    
    std::string data = ss.str();
    auto loaded = factory->loadNPC(data);
    
    EXPECT_NE(loaded, nullptr);
    EXPECT_EQ(loaded->getType(), "Dragon");
    EXPECT_EQ(loaded->getName(), "Smaug");
    
    auto pos = loaded->getPosition();
    EXPECT_EQ(pos.first, 100);
    EXPECT_EQ(pos.second, 200);
}

TEST(FactoryTest, UnknownTypeThrows) {
    auto factory = createFactory();
    EXPECT_THROW(factory->createNPC("Orc", "Grimgor", 0, 0), std::invalid_argument);
}
