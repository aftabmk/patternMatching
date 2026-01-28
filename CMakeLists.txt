cmake_minimum_required(VERSION 3.10)
project(patternDetector LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE PATTERN_SOURCES
    pattern/*.cpp
)

add_executable(app
    main.cpp
    ${PATTERN_SOURCES}
)

target_compile_options(app PRIVATE -Wall -Wextra -Wpedantic)
