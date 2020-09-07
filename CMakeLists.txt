cmake_minimum_required(VERSION 3.10)

project(nes-tetris)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_FILES
    source/collision.cpp
    source/game-logic.cpp
    source/game-over.cpp
    source/main.cpp
    source/play-field.cpp
    source/menu.cpp
    source/score.cpp
    source/tetromino.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE include)

target_link_libraries(${PROJECT_NAME} PRIVATE sfml-window sfml-system sfml-graphics sfml-audio)

