cmake_minimum_required(VERSION 3.6.2)

set(TARGET_NAME RozvrhFMFI)
project(${TARGET_NAME})

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
        src/utilities/Date.cpp
        src/utilities/Date.h
        src/entities/Event.cpp
        src/entities/Person.cpp
        src/entities/User.cpp
        src/entities/User.h
        src/entities/Admin.cpp
        src/entities/Admin.h
        src/managers/EventManager.cpp
        src/managers/EventManager.h
        src/managers/PersonManager.cpp
        src/managers/PersonManager.h
        src/entities/Person.h
        src/entities/Predmet.cpp
        src/entities/Predmet.h
        src/managers/PredmetManager.cpp
        src/managers/PredmetManager.h
)

set(TEST_FILES
        src/tests/test.cpp
)

set(GTEST_SOURCE_FILES
        GoogleTest/gtest-death-test.cc
        GoogleTest/gtest-filepath.cc
        GoogleTest/gtest-port.cc
        GoogleTest/gtest-printers.cc
        GoogleTest/gtest-test-part.cc
        GoogleTest/gtest-typed-test.cc
        GoogleTest/gtest.cc
        GoogleTest/gtest_main.cc)

add_library(tests OBJECT ${TEST_FILES})
add_library(gtest OBJECT ${GTEST_SOURCE_FILES})

find_package(Threads REQUIRED)

include_directories(GoogleTest)
add_executable(${TARGET_NAME} ${SOURCE_FILES} ${TEST_FILES} ${GTEST_SOURCE_FILES})
target_link_libraries(${TARGET_NAME} ${CMAKE_THREAD_LIBS_INIT})
