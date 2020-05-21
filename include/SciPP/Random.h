#pragma once

/**
 * \file Random.h
 * \brief Ensemble des fonctions et classes permettant la gestion de l'aléatoire.
 * \author Reiex
 */

#include <cstdint>
#include <time.h>
#include <math.h>

namespace scp
{
    /** \brief Retourne un entier aléatoire dans l'intervale [min, max]. */
	uint16_t randInt(uint16_t min=0, uint16_t max=-1);
    /**
     * \brief Retourne un nombre aléatoire dans l'intervale [min, max].
     * 
     * Le pas entre deux valeurs possibles est de \f$(max - min)2^{-64}\f$.
     */
	long double randDouble(long double min=0.0, long double max=1.0);
    /** \brief Retourne un nombre aléatoire selon une distribution normale. */
	long double normalRand(long double mean=0.0, long double sigma=1.0);
}
