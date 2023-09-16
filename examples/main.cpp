///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! \file
//! \author Pélégrin Marius
//! \copyright The MIT License (MIT)
//! \date 2019-2023
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <SciPP/SciPP.hpp>

#include "Constants.hpp"
#include "FluidSimulation.hpp"
#include "MoleDyn.hpp"

int main()
{
	/*
	
	TODO:
		- Graphs:
			- Check data structure
			- Typedefs "NodeId/EdgeId" instead of "uint64_t" everywhere
		- For matrix/vector operators, add "Matrix<TValue>/Vector<TValue>&&" versions when possible...
	*/

	// std::cout << "Neper constant: e = " << neper(200).decimals(200) << std::endl;
	// std::cout << "Sqrt(2): " << squareRoot(2, 500).decimals(500) << std::endl;
	// std::cout << "Phi: " << ((1 + squareRoot(5, 500)) / 2).decimals(500) << std::endl;
	
	// simuFluide2D("build/fluid/", 512, 512);
	// lennardJones2D("build/moledyn/", 200);

	return 0;
}
