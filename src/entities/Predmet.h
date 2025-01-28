#pragma once
#include "Event.h"

class Predmet : public Event {
private:
    std::string location;
    std::string presenter;
    std::string room;
    std::string code;
public:
    Predmet(const std::string &title, const Date &eventStart, const Date &eventEnd, Priority priority,
            const std::string &description, Type eventType, const std::string &location,
            const std::string &presenter, const std::string &room, const std::string &code);

    const std::string& getLocation() const { return location; }
    const std::string& getPresenter() const { return presenter; }
    const std::string& getRoom() const { return room; }
    const std::string& getCode() const { return code; }
};

