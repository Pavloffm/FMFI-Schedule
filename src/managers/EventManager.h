#pragma once

#include "../entities/Event.h"
#include <vector>
#include <string>

class EventManager {
private:
    std::vector<Event*> eventList;;
public:
    EventManager();

    void addEvent(Event* event) {
        eventList.push_back(event);
    }

    bool removeEvent(const std::string& title) {
        for (auto it = eventList.begin(); it != eventList.end(); ++it) {
            if ((*it)->getTitle() == title) {
                delete *it;
                eventList.erase(it);
                return true;
            }
        }
        return false;
    }

    const Event* findEvent(const std::string& title) const {
        for (const auto& event : eventList) {
            if (event->getTitle() == title) {
                return event;
            }
        }
        return nullptr;
    }


    std::vector<Event*>& getEvents() {
        return eventList;
    }

    const std::vector<Event*>& getEvents() const {
        return eventList;
    }
};
