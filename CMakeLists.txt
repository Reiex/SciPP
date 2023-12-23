#######################################################################################################################
##! \file
##! \author Pélégrin Marius
##! \copyright The MIT License (MIT)
##! \date 2019-2023
#######################################################################################################################

cmake_minimum_required(VERSION 3.21)

project(SciPP)

set(CMAKE_CXX_STANDARD 23)


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
