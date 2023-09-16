#######################################################################################################################
##! \file
##! \author Pélégrin Marius
##! \copyright The MIT License (MIT)
##! \date 2019-2023
#######################################################################################################################

cmake_minimum_required(VERSION 3.21)

project(SciPP)

set(CMAKE_CXX_STANDARD 23)

set(
    SCIPP_EXAMPLES_HEADERS
    examples/Constants.hpp
    examples/FluidSimulation.hpp
    examples/MoleDyn.hpp
    examples/SimAnim.hpp
)

set(
    SCIPP_EXAMPLES_SOURCES
    examples/main.cpp
    examples/Constants.cpp
    examples/FluidSimulation.cpp
    examples/MoleDyn.cpp
    examples/SimAnim.cpp
)

add_executable(SciPPExamples ${SCIPP_EXAMPLES_HEADERS} ${SCIPP_EXAMPLES_SOURCES})

target_include_directories(SciPPExamples PUBLIC include)
