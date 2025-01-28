#pragma once

#include <string>
#include "../managers/EventManager.h"
#include "../managers/PredmetManager.h"

enum Role { RegularUser, SuperUser };

class Person {
    std::string username;
    Role role;
    EventManager eventManager;
public:
    Person(const std::string &username, Role role);
    virtual ~Person() {}

    std::string getUsername() const { return username; };

    EventManager& getEventManager() { return eventManager; };
    const EventManager& getEventManager() const { return eventManager; }

    Role getRole() const { return role; };

    void addPredmetToEventManager(PredmetManager& predmetManager, const std::string& predmetCode) {
        try {
            Predmet predmet = predmetManager.getPredmetByCode(predmetCode);
            Predmet* predmetPtr = new Predmet(predmet);
            eventManager.addEvent(predmetPtr); // Using private eventManager
        } catch (const std::exception& e) {
            throw std::runtime_error("Failed to add predmet: " + std::string(e.what()));
        }
    }

    void exportPredmetCodesToFile() const;

    void importPredmetCodesFromFile(PredmetManager& predmetManager);

    std::vector<std::string> findTimeCollisions() const;
};

