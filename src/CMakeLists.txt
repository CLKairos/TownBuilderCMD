cmake_minimum_required(VERSION 3.5)
project(TownBuilder)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON) 
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(TownBuilder
        game.cpp
        growth.cpp
        housing.cpp
        input.cpp
        main.cpp
        randomEvents.cpp
        save.cpp
        shop.cpp
        location.cpp
        loan.cpp
        reputation.cpp)
