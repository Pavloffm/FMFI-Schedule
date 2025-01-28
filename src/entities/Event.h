#pragma once

#include "../utilities/Date.h"
#include <string>

enum Priority {Low, MediumLow, Medium, MediumHigh, High, Critical};

enum Type {Personal, Study};

class Event {
    std::string title;
    Date eventStart;
    Date eventEnd;
    Priority priority;
    std::string description;
    Type eventType;
public:
    Event(const std::string &title, const Date &eventStart, const Date &eventEnd, Priority priority, const std::string &description, Type eventType);
    virtual ~Event() = default;
    const std::string getTitle() const {return title; }
    const Date& getEventStart() const {return eventStart; }
    const Date& getEventEnd() const {return eventEnd; }
    Priority getEventPriority() const { return priority; }
    const std::string& getDescription() const {return description; }
    Type getEventType() const { return eventType; }
};
