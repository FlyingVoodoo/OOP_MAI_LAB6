#include "fight_visitor.hpp"
#include "knight.hpp"
#include "elf.hpp"
#include "dragon.hpp"

FightVisitor::FightVisitor(NPCPtr attacker) : attacker(attacker) {}

void FightVisitor::visit(Knight* defender) {
    if (std::dynamic_pointer_cast<Dragon>(attacker)) {
        attacker->kill();
    }
    else if (std::dynamic_pointer_cast<Elf>(attacker)) {
        defender->kill();
    }
    else if (std::dynamic_pointer_cast<Knight>(attacker)) {
       
    }
}

void FightVisitor::visit(Elf* defender) {
    if (std::dynamic_pointer_cast<Dragon>(attacker)) {
        defender->kill();
    }
    else if (std::dynamic_pointer_cast<Elf>(attacker)) {
    }
    else if (std::dynamic_pointer_cast<Knight>(attacker)) {
        attacker->kill();
    }
}

void FightVisitor::visit(Dragon* defender) {
    if (std::dynamic_pointer_cast<Dragon>(attacker)) {
       defender->kill();
       attacker->kill();
    }
    else if (std::dynamic_pointer_cast<Elf>(attacker)) {
        attacker->kill();
    }
    else if (std::dynamic_pointer_cast<Knight>(attacker)) {
        defender->kill();
    }
}