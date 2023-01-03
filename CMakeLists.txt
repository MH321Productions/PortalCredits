cmake_minimum_required(VERSION 3.16)

project(portal-credits LANGUAGES CXX)

include_directories(src)
include_directories(lib)
include_directories(include)
include_directories(src/Generated)

#Subdirectories
set(BUILD_SHARED_LIBS OFF)
set(SFML_BUILD_EXAMPLES OFF)
set(SFML_BUILD_GRAPHICS OFF)
set(SFML_BUILD_WINDOW OFF)
set(SFML_BUILD_NETWORK OFF)
add_subdirectory(lib/SFML)
include_directories(lib/SFML/include)

if (WIN32)
    set(CMAKE_BUILD_TYPE Release)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded")
    add_compile_definitions(PC_WINDOWS)
else()
    set(CMAKE_CXX_FLAGS -no-pie)
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_COMPILER g++)

#Debug
if(NOT CMAKE_BUILD_TYPE MATCHES Release)
endif()

#Libraries
add_library(PortalCredits STATIC
    src/PortalCredits/SoundHandler.cpp
    src/PortalCredits/Util.cpp
    src/PortalCredits/ConsoleHandler.cpp
    src/PortalCredits/DrawHandler.cpp
)

list(APPEND libs
    PortalCredits
    sfml-audio
    ncurses
)

#Main program
add_executable(Program src/Main.cpp)
set_target_properties(Program PROPERTIES OUTPUT_NAME "PortalCredits")
target_link_libraries(Program PRIVATE ${libs})

if (WIN32)
    set_target_properties(${libs} PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded")
endif()
