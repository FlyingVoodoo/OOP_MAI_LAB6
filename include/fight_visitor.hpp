#pragma once
#include "IFightVisitor.hpp"
#include "npc.hpp"

class FightVisitor : public IFightVisitor {
private:
    NPCPtr attacker;

public:
    FightVisitor(NPCPtr attacker);
    ~FightVisitor() override = default;

    void visit(Knight* defender) override;
    void visit(Elf* defender) override;
    void visit(Dragon* defender) override;

    NPCPtr getAttacker() const {
        return attacker;
    }
};