#include "Predmet.h"

Predmet::Predmet(const std::string &title, const Date &eventStart, const Date &eventEnd, Priority priority,
                 const std::string &description, Type eventType, const std::string &location,
                 const std::string &presenter, const std::string &room, const std::string &code)
    : Event(title, eventStart, eventEnd, priority, description, eventType), location(location),
    presenter(presenter), room(room), code(code) {
}
