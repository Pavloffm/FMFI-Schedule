#pragma once

#include "Person.h"
#include "User.h"

class Admin : public Person {
private:
public:
    Admin(const std::string &name);
    std::vector<Event*> viewUserEvents(const User& user) const;
};

