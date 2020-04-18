#pragma once

/**
 * \file Interpreteur.h
 * \brief Ensemble de fonctions permettant la manipulation d'un petit interpreteur propre à SciPP
 * 
 * Pour l'instant très sommaire, cet interpreteur ne permet que de faire quelques calculs basiques
 * qu'une calculatrice de primaire peut également executer. Mais à terme le but est d'avoir un petit
 * interpreteur de calcul formel.
*/

#include <iostream>
#include <string>
#include "Plot.h"
#include "List.hpp"

/*
	input l0?l! -> instr l0?l1! ENDL input l1?l!
				 | EXIT ENDL						l = l0

	instr l0?l! -> exp2 l?x!						l0[0] = x
				 | SET VAR n! EQUAL exp2 l?x!		l0[n] = x

	exp0 l?x! -> MINUS exp0 l?x0!					x = -x0
			   | OPAR exp2 l?x! CPAR
			   | NUM x!
			   | VAR n!								x = l[n]
	
	exp1 l?x! -> exp0 l?x0! exp1p l?x0?x!

	exp1p l?y?x! -> TIMES exp0 l?x0! exp1p l?y*x0?x!
				  | DIV exp0 l?x0! exp1p l?y/x0?x!
				  | EPS								x = y

	exp2 l?x! -> exp1 l?x0! exp2p l?x0?x!

	exp2p l?y?x! -> PLUS exp1 l?x0! exp2p l?y+x0?x!
				  | MINUS exp1 l?x0! exp2p l?y-x0?x!
				  | EPS								x = y
*/


void lancerInterpreteur();
