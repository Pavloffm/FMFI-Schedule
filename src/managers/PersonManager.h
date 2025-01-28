#pragma once

#include "../entities/Person.h"
#include <unordered_map>
#include <string>
#include <vector>

class PersonManager {
private:
    std::unordered_map<std::string, Person*> persons; // Person object storage (by reference or pointer)
public:
    void addPerson(Person* person) {
        persons[person->getUsername()] = person;
    }

    bool removePerson(const std::string& username) {
        auto it = persons.find(username);
        if (it != persons.end()) {
            persons.erase(it);
            return true;
        }
        return false;
    }

    Person* findPerson(const std::string& username) {
        auto it = persons.find(username);
        if (it != persons.end()) {
            return it->second;
        }
        return nullptr;
    }

    std::vector<std::string> getAllUsernames() const {
        std::vector<std::string> usernames;
        for (const auto& pair : persons) {
            usernames.push_back(pair.first);
        }
        return usernames;
    }

    std::vector<Person*> getPersonsByRole(Role role) const {
        std::vector<Person*> result;
        for (const auto& pair : persons) {
            if (pair.second->getRole() == role) {
                result.push_back(pair.second);
            }
        }
        return result;
    }
};
