#pragma once
#include "npc.hpp"
#include <iostream>

class IFightVisitor;

class Knight : public NPC, public std::enable_shared_from_this<Knight> {
public:
    Knight(const std::string& name, int x, int y) : NPC(name, x, y) {}

    bool accept(const std::shared_ptr<IFightVisitor>& visitor) override {
        visitor->visit(this); 
        return true;
    }

    std::string getType() const override { return "Knight"; }

    void print() const override {
        std::cout << "Knight: " << name_ << " at (" << x_ << ", " << y_ << ")"
                  << (alive ? " [Alive]" : " [Dead]") << std::endl;
    }

    void save(std::ostream& os) const override {
        os << getType() << std::endl;
        NPC::save(os);
    }
};