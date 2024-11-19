cmake_minimum_required(VERSION 3.29)
project(hms)

set(CMAKE_CXX_STANDARD 20)

add_executable(hms main.cpp
        game_state.h
        inventory.h
        inventory.cpp
        items.h
        story.cpp
        story.h
        ui.h
        ui.cpp
        game_state.cpp
        NPC.cpp)
