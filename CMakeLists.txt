cmake_minimum_required(VERSION 3.16)

project(portal-credits LANGUAGES CXX)

include_directories(src)
include_directories(lib)
include_directories(include)
include_directories(src/Generated)

if (NOT DEFINED CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

if (WIN32)
    if(MSVC)
        set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded")
    endif()

    add_compile_definitions(PC_WINDOWS)
endif()

#Subdirectories
set(BUILD_SHARED_LIBS OFF)
set(SFML_BUILD_EXAMPLES OFF)
set(SFML_BUILD_GRAPHICS OFF)
set(SFML_BUILD_WINDOW OFF)
set(SFML_BUILD_NETWORK OFF)
set(SFML_USE_STATIC_STD_LIBS ON)
add_compile_definitions(SFML_STATIC)
add_subdirectory(lib/SFML)
include_directories(lib/SFML/include)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_COMPILER g++)

#Debug
if(NOT CMAKE_BUILD_TYPE MATCHES Release)
endif()

#Libraries
add_library(PortalResources STATIC
    src/Generated/Lyrics.cpp
    src/Generated/Song.cpp
    src/Generated/Timing.cpp
    src/Generated/License.cpp
    src/Generated/Title.cpp
    src/Generated/Menu.cpp
    src/Generated/Symbols.cpp
)

add_library(PortalCredits STATIC
    src/PortalCredits/App.cpp
    src/PortalCredits/LoopHandlers.cpp
    src/PortalCredits/RenderHandlers.cpp
    src/PortalCredits/InputHandler.cpp
    src/PortalCredits/SoundHandler.cpp
    src/PortalCredits/SystemHandler.cpp
    src/PortalCredits/ConsoleHandler.cpp
    src/PortalCredits/DrawHandler.cpp
)
target_link_libraries(PortalCredits PRIVATE sfml-audio)

list(APPEND libs
    sfml-system
    sfml-audio
    PortalCredits
    PortalResources
)

#Main program
add_executable(Program src/Main.cpp)
set_target_properties(Program PROPERTIES OUTPUT_NAME "PortalCredits")
target_link_libraries(Program PRIVATE ${libs})

if (MSVC)
    set_target_properties(${libs} PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded")
endif()
