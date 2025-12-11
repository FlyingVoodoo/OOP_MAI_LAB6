#pragma once
#include "IFightVisitor.hpp"
#include <memory>
#include <string>

class IFightVisitor;

class NPC {
protected:
    std::string name_;
    int x_;
    int y_;
    bool alive = true;

public:
    NPC(const std::string& name, int x, int y);
    virtual ~NPC() = default;

    virtual bool accept(const std::shared_ptr<IFightVisitor>& visitor) = 0;


    virtual void print () const = 0;
    virtual void save (std::ostream& os) const = 0;
    std::string getName() const { return name_; }
    std::pair<int, int> getPosition() const { return {x_, y_}; }
    bool isAlive() const { return alive; }
    void kill() { alive = false; }

    double distanceTo(const std::shared_ptr<NPC>& other) const;

    virtual std::string getType() const = 0;
};

using NPCPtr = std::shared_ptr<NPC>;