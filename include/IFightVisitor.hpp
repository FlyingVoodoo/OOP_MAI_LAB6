#pragma once

#include "npc.hpp"
class Knight;
class Elf;
class Dragon;

class IFightVisitor {
public:
    virtual ~IFightVisitor() = default;

    virtual void visit(Knight* defender) = 0;
    virtual void visit(Elf* defender) = 0;
    virtual void visit(Dragon* defender) = 0;
};