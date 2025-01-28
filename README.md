# FMFI-Schedule
A tool for managing student schedules at FMFI. Built with C++17, it allows creating, editing, and viewing timetables, focusing on functionality and ease of use.

# Documentation

## Class Date
The Date class is responsible for working with dates. It validates the correctness of dates and supports comparison operations.

## Class Event
The Event class represents an event with the following attributes:
- title: The title of the event.
- eventStart: The start date of the event.
- eventEnd: The end date of the event.
- priority: The priority level of the event.
- description: A detailed description of the event.
- eventType: The type of the event.

This class allows users to create personal events.

## Class Predmet
The Predmet class is a subclass of Event and includes additional attributes:
- location: The location of the event.
- presenter: The lecturer associated with the event.
- room: The room where the event will take place.
- code: The course code for the event.

The Predmet class allows the creation of courses.

## Class EventManager
The EventManager class is responsible for managing Event objects and their subclasses. It provides the following functionalities:
- Adding events.
- Removing events.
- Searching for events.

## Class PredmetManager
The PredmetManager class manages all Predmet objects and provides the following functionalities:
- Adding Predmet objects.
- Removing Predmet objects.
- Searching for Predmet objects by course code or by their title.

## Class PersonManager
The PersonManager class is responsible for managing users. It provides the following functionalities:
- Adding users.
- Removing users.
- Searching for users.
- Retrieving all users or filtering users by a specific role.

## Class Person
The Person class represents a user with the following attributes:
- username: The username of the user.
- role: The role of the user.
- eventManager: An instance of EventManager for managing the user's events.

Additional functionalities include:
- Adding Predmet objects to the EventManager.
- **Detecting collisions between events and displaying them when found.**
- Exporting or importing Predmet objects by their course codes from the PredmetManager.

## Class Admin
The Admin class is a subclass of Person. In addition to the functionalities inherited from Person, it provides the ability to view the events of any user.

## Class User
The User class is a subclass of Person with the same functionalities as Person. The only difference is its initialization, where the role is set to RegularUser.

## test.cpp
The test.cpp file contains tests to verify the correct functionality of the program.	