cmake_minimum_required(VERSION 3.0.0)
project(nodepp-input VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(NODEPP_INPUT_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")

# Search for Nodepp
find_package(nodepp REQUIRED) 
if(NOT nodepp_FOUND)
    message(FATAL_ERROR "Nodepp not found. Please install nodepp.")
endif()

if(NOT WIN32)
    message(STATUS "Searching for X-libraries (libxtst-dev, libx11-dev, libxi-dev)...")
    
    # Search for X11 Core
    find_package(X11 REQUIRED) 
    if(NOT X11_FOUND)
        message(FATAL_ERROR "X11 libraries not found. Please install libx11-dev.")
    endif()

    
    # Search for X11-XTest
    find_library(XTEST_LIBRARY NAMES Xtst) 
    if(NOT XTEST_LIBRARY)
        message(FATAL_ERROR "XTest library not found. Please install libxtst-dev.")
    endif()

    # Search for X11-XInput
    find_library(XINPUT_LIBRARY NAMES Xi)
    if(NOT XINPUT_LIBRARY)
        message(FATAL_ERROR "XInput library not found. Please install libxi-dev.")
    endif()

endif()

add_library(nodepp-input INTERFACE)
target_include_directories(nodepp-input INTERFACE ${NODEPP_INPUT_INCLUDE_DIR})

if(NOT WIN32)

    set(INPUT_LINK_DEPS
        nodepp
        ${X11_LIBRARIES}
        ${XTEST_LIBRARY}
        ${XINPUT_LIBRARY}
    )

    if(X11_INCLUDE_DIR)
        target_include_directories(nodepp-input INTERFACE ${X11_INCLUDE_DIR})
    endif()

else()
    set(INPUT_LINK_DEPS nodepp)
endif()

target_link_libraries(nodepp-input 
    INTERFACE ${INPUT_LINK_DEPS}
)