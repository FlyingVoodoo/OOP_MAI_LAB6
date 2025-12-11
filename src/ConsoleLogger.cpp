#include "ConsoleLogger.hpp"
#include <iostream>

// Реализация статического метода get
IFightObserverPtr ConsoleLogger::get() {
    static ConsoleLogger instance;
    // Возвращаем shared_ptr с кастомным делетером, который ничего не делает
    return std::shared_ptr<IFightObserver>(&instance, [](IFightObserver *) {});
}

// Реализация метода оповещения
void ConsoleLogger::onFightOutcome(const std::string& event_details) {
    std::cout << "[FIGHT LOG] " << event_details << std::endl;
}                                                                                                                                                                                                                                           