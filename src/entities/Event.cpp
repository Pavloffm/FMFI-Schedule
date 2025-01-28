#include "Event.h"
#include <stdexcept>

Event::Event(const std::string &title, const Date &eventStart, const Date &eventEnd, Priority priority,
    const std::string &description, Type eventType)
    : title(title), eventStart(eventStart), eventEnd(eventEnd), priority(priority),
    description(description), eventType(eventType) {

    // Validate eventStart
    try {
        Date tempStart(eventStart.getYear(), eventStart.getMonth(), eventStart.getDay(),
                       eventStart.getHour(), eventStart.getMinute(), eventStart.getSecond());
    } catch (const std::invalid_argument &e) {
        throw std::invalid_argument("Invalid eventStart date: " + std::string(e.what()));
    }

    // Validate eventEnd
    try {
        Date tempEnd(eventEnd.getYear(), eventEnd.getMonth(), eventEnd.getDay(),
                     eventEnd.getHour(), eventEnd.getMinute(), eventEnd.getSecond());
    } catch (const std::invalid_argument &e) {
        throw std::invalid_argument("Invalid eventEnd date: " + std::string(e.what()));
    }

    // Ensure eventEnd is after or equal to eventStart
    if (eventEnd < eventStart) {
        throw std::invalid_argument("eventEnd cannot be before eventStart.");
    }
}
