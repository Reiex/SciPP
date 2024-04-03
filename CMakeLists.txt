#######################################################################################################################
##! \file
##! \author Pélégrin Marius
##! \copyright The MIT License (MIT)
##! \date 2019-2024
#######################################################################################################################

# Global project definitions

cmake_minimum_required(VERSION 3.21)

project(SciPP)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# SciPP

add_custom_target(
    scipp SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/include/SciPP/SciPP.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/SciPP/SciPPDecl.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/SciPP/SciPPTypes.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/SciPP/Core/Core.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/SciPP/Core/CoreDecl.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/SciPP/Core/CoreTypes.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/SciPP/Core/BigInt.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/SciPP/Core/Frac.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/SciPP/Core/Graph.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/SciPP/Core/Mat.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/SciPP/Core/Matrix.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/SciPP/Core/misc.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/SciPP/Core/Quat.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/SciPP/Core/Rational.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/SciPP/Core/SpTensor.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/SciPP/Core/Tensor.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/SciPP/Core/TensorUtils.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/SciPP/Core/Vec.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/SciPP/Core/Vector.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/SciPP/Core/templates/BigInt.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/SciPP/Core/templates/Frac.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/SciPP/Core/templates/Graph.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/SciPP/Core/templates/Mat.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/SciPP/Core/templates/Matrix.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/SciPP/Core/templates/misc.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/SciPP/Core/templates/Quat.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/SciPP/Core/templates/Rational.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/SciPP/Core/templates/SpTensor.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/SciPP/Core/templates/Tensor.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/SciPP/Core/templates/TensorUtils.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/SciPP/Core/templates/Vector.hpp
)

# SciPP examples

option(SCIPP_BUILD_EXAMPLES "Add target scipp-examples" ON)

if(SCIPP_BUILD_EXAMPLES)

    add_executable(
        scipp-examples
        ${CMAKE_CURRENT_LIST_DIR}/examples/main.cpp
        ${CMAKE_CURRENT_LIST_DIR}/examples/Constants.hpp
        ${CMAKE_CURRENT_LIST_DIR}/examples/Constants.cpp
        ${CMAKE_CURRENT_LIST_DIR}/examples/FluidSimulation.hpp
        ${CMAKE_CURRENT_LIST_DIR}/examples/FluidSimulation.cpp
        ${CMAKE_CURRENT_LIST_DIR}/examples/MoleDyn.hpp
        ${CMAKE_CURRENT_LIST_DIR}/examples/MoleDyn.cpp
        ${CMAKE_CURRENT_LIST_DIR}/examples/SimAnim.hpp
        ${CMAKE_CURRENT_LIST_DIR}/examples/SimAnim.cpp
    )

    add_dependencies(
        scipp-examples
        scipp
    )

    target_include_directories(
        scipp-examples
        PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include
    )

endif()
