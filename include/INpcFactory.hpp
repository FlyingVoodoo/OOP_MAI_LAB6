#pragma once
#include "npc.hpp"

#include <memory>
#include <string>
#include <functional>

class INpcFactory {
public:
    virtual ~INpcFactory() = default;

    virtual NPCPtr createNPC(const std::string& type, const std::string& name, int x, int y) = 0;
    virtual NPCPtr loadNPC(const std::string& data) = 0;

    using CreatorFunc = std::function<NPCPtr(const std::string&, int, int)>;
    virtual void registerCreator(const std::string& type, CreatorFunc creator) = 0;
};

using INpcFactoryPtr = std::shared_ptr<INpcFactory>;