#include "Person.h"

#include <fstream>
#include <stdexcept>
#include <filesystem>
#include <iostream>

Person::Person(const std::string &username, Role role) : username(username), role(role) {
    eventManager = EventManager();
}

void Person::exportPredmetCodesToFile() const {
    std::string directory = "tests/tmp";
    std::string filename = directory + "/" + username + ".list";

    if (!std::filesystem::exists(directory)) {
        if (!std::filesystem::create_directories(directory)) {
            throw std::runtime_error("Failed to create directory: " + directory);
        }
    }

    std::ofstream outFile(filename, std::ios::trunc);
    if (!outFile.is_open()) {
        throw std::runtime_error("Unable to create file: " + filename);
    }

    for (const auto& event : eventManager.getEvents()) {
        if (event->getEventType() == Study) {
            const Predmet* predmet = dynamic_cast<const Predmet*>(event);
            outFile << predmet->getCode() << "\n";
        }
    }

    outFile.close();
}

void Person::importPredmetCodesFromFile(PredmetManager& predmetManager) {
    std::string filename = "tests/tmp/" + username + ".list";

    if (!std::filesystem::exists(filename)) {
        throw std::runtime_error("File does not exist: " + filename);
    }

    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        throw std::runtime_error("Unable to open file: " + filename);
    }

    std::string code;
    while (std::getline(inFile, code)) {
        try {
            Predmet predmet = predmetManager.getPredmetByCode(code);
            Predmet* predmetPtr = new Predmet(predmet);
            eventManager.addEvent(predmetPtr);
        } catch (const std::exception& e) {
            throw std::runtime_error("Failed to import predmet with code " + code + ": " + e.what());
        }
    }

    inFile.close();
}

std::vector<std::string> Person::findTimeCollisions() const {
    std::vector<std::string> collisions;
    const auto& events = eventManager.getEvents();

    for (size_t i = 0; i < events.size(); ++i) {
        const Event* event1 = events[i];
        for (size_t j = i + 1; j < events.size(); ++j) {
            const Event* event2 = events[j];

            if (event1->getEventStart() < event2->getEventEnd() &&
                event1->getEventEnd() > event2->getEventStart()) {
                collisions.push_back(event1->getTitle() + " : " + event2->getTitle());
                }
        }
    }

    return collisions;
}



