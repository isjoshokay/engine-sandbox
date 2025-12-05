cmake_minimum_required(VERSION 3.16)
project(engine_sandbox)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Find SDL2 installed on the system (e.g., via Homebrew on macOS)
find_package(SDL2 REQUIRED)
# SDL2's include directories
include_directories(${SDL2_INCLUDE_DIRS})
# All .cpp files in src/
file(GLOB_RECURSE ENGINE_SANDBOX_SOURCES src/*.cpp)
# Build the executable from the source files
add_executable(engine_sandbox ${ENGINE_SANDBOX_SOURCES})
# Link SDL2 to the executable
target_link_libraries(engine_sandbox ${SDL2_LIBRARIES})