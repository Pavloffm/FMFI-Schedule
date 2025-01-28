#include <iostream>
#include <fstream>
#include <sstream>

#include "../entities/Admin.h"
#include "gtest/gtest.h"
#include "../entities/Person.h"
#include "../utilities/Date.h"
#include "../entities/Event.h"
#include "../managers/EventManager.h"
#include "../managers/PersonManager.h"
#include "../entities/User.h"

using namespace ::testing;

TEST(TestDate, DateToString) {
    Date defaultDate;
    ASSERT_EQ("0000-00-00 00:00:00", defaultDate.ToString());

    Date validDate(2025, 1, 13, 14, 30, 45);
    ASSERT_EQ("2025-01-13 14:30:45", validDate.ToString());

    Date minDate(2025, 1, 1, 0, 0, 0);
    ASSERT_EQ("2025-01-01 00:00:00", minDate.ToString());

    Date maxDate(2035, 12, 31, 23, 59, 59);
    ASSERT_EQ("2035-12-31 23:59:59", maxDate.ToString());

    Date leapYearDate(2025, 3, 29, 12, 0, 0);
    ASSERT_EQ("2025-03-29 12:00:00", leapYearDate.ToString());

    ASSERT_THROW(Date invalidDate(2025, 13, 1, 12, 0, 0), std::invalid_argument);
    ASSERT_THROW(Date invalidDate(2025, 0, 1, 12, 0, 0), std::invalid_argument);
    ASSERT_THROW(Date invalidDate(2025, 2, 30, 12, 0, 0), std::invalid_argument);
    ASSERT_THROW(Date invalidDate(2025, 4, 31, 12, 0, 0), std::invalid_argument);
    ASSERT_THROW(Date invalidDate(2025, 1, 1, 24, 0, 0), std::invalid_argument);
    ASSERT_THROW(Date invalidDate(2025, 1, 1, 12, 60, 0), std::invalid_argument);
    ASSERT_THROW(Date invalidDate(2025, 1, 1, 12, 0, 60), std::invalid_argument);
}


TEST(TestUser, CreateUser) {
    User person("TestUser");

    ASSERT_EQ(RegularUser, person.getRole());
}

TEST(TestAdmin, CreateAdmin) {
    Admin person("TestAdmin");

    ASSERT_EQ(SuperUser, person.getRole());
}

TEST(PersonManagerTest, AddFindAndRemovePerson) {
    PersonManager personManager;

    User user1("User1");
    Admin admin1("Admin1");

    personManager.addPerson(&user1);
    personManager.addPerson(&admin1);

    Person* foundPerson = personManager.findPerson("User1");
    ASSERT_NE(foundPerson, nullptr);
    ASSERT_EQ(foundPerson->getUsername(), "User1");

    auto regularUsers = personManager.getPersonsByRole(RegularUser);
    ASSERT_EQ(regularUsers.size(), 1);
    ASSERT_EQ(regularUsers[0]->getUsername(), "User1");

    ASSERT_TRUE(personManager.removePerson("User1"));
    ASSERT_EQ(personManager.findPerson("User1"), nullptr);
}

TEST(AdminTest, ViewUserEvents) {
    PersonManager personManager;

    Admin admin("AdminName");
    User user("UserName");

    personManager.addPerson(&admin);
    personManager.addPerson(&user);

    Date StartDate(2025, 1, 13, 10, 0, 0);
    Date EndDate(2025, 1, 13, 12, 0, 0);

    auto* event1 = new Event("Meeting", StartDate, EndDate, High, "Project discussion", Personal);
    user.getEventManager().addEvent(event1);

    Person* foundUser = personManager.findPerson("UserName");
    ASSERT_NE(foundUser, nullptr);

    User* foundUserAsUser = dynamic_cast<User*>(foundUser);
    ASSERT_NE(foundUserAsUser, nullptr);

    auto events = admin.viewUserEvents(*foundUserAsUser);

    ASSERT_EQ(events.size(), 1);
    ASSERT_EQ(events[0]->getTitle(), "Meeting");
    ASSERT_EQ(events[0]->getDescription(), "Project discussion");

    for (auto* event : events) {
        delete event;
    }
}

TEST(TestUserPredmetWithDefaultDate, AddPredmetToEventManager) {
    PredmetManager predmetManager;
    predmetManager.addPredmet(Predmet("Math Class", Date(2025, 2, 23, 5, 20, 0), Date(2025, 2, 23, 7, 50, 0), High,
                                      "Algebra lesson", Study, "Room 101", "Dr. Smith", "101", "MATH101"));
    predmetManager.addPredmet(Predmet("Physics Class", Date(2026, 2, 23, 5, 20, 0), Date(2026, 2, 23, 6, 50, 0), Medium,
                                      "Mechanics lecture", Study, "Room 102", "Dr. Johnson", "102", "PHYS101"));

    User user("John");

    user.addPredmetToEventManager(predmetManager, "MATH101");

    auto events = user.getEventManager().getEvents();
    ASSERT_EQ(events.size(), 1);
    ASSERT_EQ(events[0]->getTitle(), "Math Class");
    ASSERT_EQ(events[0]->getDescription(), "Algebra lesson");
    ASSERT_EQ(events[0]->getEventType(), Study);

    for (auto* event : events) {
        delete event;
    }
}

TEST(TestExportAndImportPredmetCodes, ExportAndImportCodes) {
    PredmetManager predmetManager;

    std::vector<std::string> codes = {
        "1-AIN-105", "1-AIN-152", "1-AIN-171",
        "1-AIN-186", "1-AIN-221", "1-AIN-319",
        "1-MXX-151", "1-MXX-231"
    };

    for (const auto& code : codes) {
        predmetManager.addPredmet(Predmet(
        "Title for " + code, Date(2025, 2, 23, 5, 20, 0), Date(2025, 2, 23, 6, 0, 0), Medium, "Description", Study,
        "Location", "Presenter", "Room", code));
    }

    User user("TestUser");
    for (const auto& code : codes) {
        user.getEventManager().addEvent(new Predmet(
        "Title for " + code, Date(2025, 2, 23, 5, 20, 0), Date(2025, 2, 23, 6, 0, 0), Medium, "Description", Study,
        "Location", "Presenter", "Room", code));
    }

    user.exportPredmetCodesToFile();

    std::ifstream inFile("tests/tmp/TestUser.list");
    ASSERT_TRUE(inFile.is_open());

    std::vector<std::string> exportedCodes;
    std::string line;
    while (std::getline(inFile, line)) {
        exportedCodes.push_back(line);
    }

    inFile.close();

    ASSERT_EQ(codes.size(), exportedCodes.size());
    for (size_t i = 0; i < codes.size(); ++i) {
        ASSERT_EQ(codes[i], exportedCodes[i]);
    }

    auto& events = user.getEventManager().getEvents();
    for (auto* event : events) {
        delete event;
    }
    events.clear();

    ASSERT_EQ(user.getEventManager().getEvents().size(), 0);

    user.importPredmetCodesFromFile(predmetManager);

    const auto& importedEvents = user.getEventManager().getEvents();
    ASSERT_EQ(importedEvents.size(), codes.size());

    for (size_t i = 0; i < codes.size(); ++i) {
        const auto* importedPredmet = dynamic_cast<const Predmet*>(importedEvents[i]);
        ASSERT_NE(importedPredmet, nullptr);
        ASSERT_EQ(importedPredmet->getCode(), codes[i]);
    }

    for (auto* event : importedEvents) {
        delete event;
    }
}

TEST(PersonTest, NoCollisions) {
    Person person("TestUser", RegularUser);

    person.getEventManager().addEvent(new Event("Event1", Date(2025, 1, 13, 10, 0, 0), Date(2025, 1, 13, 11, 0, 0), Medium, "Description1", Personal));
    person.getEventManager().addEvent(new Event("Event2", Date(2025, 1, 13, 12, 0, 0), Date(2025, 1, 13, 13, 0, 0), Medium, "Description2", Personal));

    auto collisions = person.findTimeCollisions();

    ASSERT_TRUE(collisions.empty());
}

TEST(PersonTest, SingleCollision) {
    Person person("TestUser", RegularUser);

    person.getEventManager().addEvent(new Event("Event1", Date(2025, 1, 13, 10, 0, 0), Date(2025, 1, 13, 11, 30, 0), Medium, "Description1", Personal));
    person.getEventManager().addEvent(new Event("Event2", Date(2025, 1, 13, 11, 0, 0), Date(2025, 1, 13, 12, 0, 0), Medium, "Description2", Personal));

    auto collisions = person.findTimeCollisions();

    ASSERT_EQ(collisions.size(), 1);
    ASSERT_EQ(collisions[0], "Event1 : Event2");
}

TEST(PersonTest, MultipleCollisions) {
    Person person("TestUser", RegularUser);

    person.getEventManager().addEvent(new Event("Event1", Date(2025, 1, 13, 10, 0, 0), Date(2025, 1, 13, 12, 0, 0), Medium, "Description1", Personal));
    person.getEventManager().addEvent(new Event("Event2", Date(2025, 1, 13, 11, 0, 0), Date(2025, 1, 13, 13, 0, 0), Medium, "Description2", Personal));
    person.getEventManager().addEvent(new Event("Event3", Date(2025, 1, 13, 11, 30, 0), Date(2025, 1, 13, 12, 30, 0), Medium, "Description3", Personal));

    auto collisions = person.findTimeCollisions();

    ASSERT_EQ(collisions.size(), 3);
    ASSERT_EQ(collisions[0], "Event1 : Event2");
    ASSERT_EQ(collisions[1], "Event1 : Event3");
    ASSERT_EQ(collisions[2], "Event2 : Event3");
}

TEST(PersonTest, IdenticalEventsCollision) {
    Person person("TestUser", RegularUser);

    person.getEventManager().addEvent(new Event("Event1", Date(2025, 1, 13, 10, 0, 0), Date(2025, 1, 13, 12, 0, 0), Medium, "Description1", Personal));
    person.getEventManager().addEvent(new Event("Event1 Copy", Date(2025, 1, 13, 10, 0, 0), Date(2025, 1, 13, 12, 0, 0), Medium, "Description1", Personal));

    auto collisions = person.findTimeCollisions();

    ASSERT_EQ(collisions.size(), 1);
    ASSERT_EQ(collisions[0], "Event1 : Event1 Copy");
}