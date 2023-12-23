#######################################################################################################################
##! \file
##! \author Pélégrin Marius
##! \copyright The MIT License (MIT)
##! \date 2019-2023
#######################################################################################################################

# Global project definitions

cmake_minimum_required(VERSION 3.21)

project(SciPP)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# SciPP examples

if(NOT DEFINED SCIPP_LIB_ONLY)

    add_executable(
        scipp-examples
        ${CMAKE_CURRENT_LIST_DIR}/examples/main.cpp
        ${CMAKE_CURRENT_LIST_DIR}/examples/Constants.cpp
        ${CMAKE_CURRENT_LIST_DIR}/examples/FluidSimulation.cpp
        ${CMAKE_CURRENT_LIST_DIR}/examples/MoleDyn.cpp
        ${CMAKE_CURRENT_LIST_DIR}/examples/SimAnim.cpp
    )

    target_include_directories(
        scipp-examples
        PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include
    )

endif()
