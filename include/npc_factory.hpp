#pragma once
#include <string>
#include <unordered_map>
#include "INpcFactory.hpp"

class NpcFactory : public INpcFactory {
private:
    std::unordered_map<std::string, CreatorFunc> creators;
public:
    virtual ~NpcFactory() = default;

    void registerCreator(const std::string& type, CreatorFunc creator) override;

    NPCPtr createNPC(const std::string& type, const std::string& name, int x, int y) override;
    NPCPtr loadNPC(const std::string& data) override;
};