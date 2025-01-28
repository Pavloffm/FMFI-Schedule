#include "Admin.h"

Admin::Admin(const std::string &name) : Person(name, SuperUser) {}

std::vector<Event*> Admin::viewUserEvents(const User& user) const {
    return user.getEventManager().getEvents();
}
