#include "npc.hpp"

#include <cmath>
#include <limits>
#include <ostream>

NPC::NPC(const std::string& name, int x, int y) : name_(name), x_(x), y_(y) {}

double NPC::distanceTo(const std::shared_ptr<NPC>& other) const {
    if (!other) {
        return std::numeric_limits<double>::infinity();
    }
    double dx = static_cast<double>(x_ - other->x_);
    double dy = static_cast<double>(y_ - other->y_);

    return std::sqrt(dx * dx + dy * dy);
}

void NPC::save(std::ostream& os) const {
    os << name_ << " " << x_ << " " << y_ << " " << "\n";
}