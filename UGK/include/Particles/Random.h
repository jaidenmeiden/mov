/**
 * @file	inc\Random.h
 *
 * @brief	Declares the random class.
 * 			
 * @author	Joaquin Taverner y Fran Munyoz
 * @date	25/02/2017
 */

#pragma once;

#include <UGKAlgebra.h>

using namespace UGK;

/**
 * @fn	inline float Random()
 *
 * @brief	Generate a random number between [0..1)
 *
 * @return	A float.
 */

inline float Random()
{
    return rand() / (float)RAND_MAX;
}

/**
 * @fn	inline float RandRange( float fMin, float fMax )
 *
 * @brief	Random range.
 *
 * @param	fMin	The minimum.
 * @param	fMax	The maximum.
 *
 * @return	A float.
 */

inline float RandRange( float fMin, float fMax )
{
    if ( fMin > fMax ) std::swap( fMin, fMax );
    return ( Random() * ( fMax - fMin ) ) + fMin;
}

/**
 * @fn	inline Vector RandUnitVec()
 *
 * @brief	Random unit vector.
 *
 * @return	A Vector.
 */

inline Vector RandUnitVec()
{
	Vector V;

    V.v[XDIM] = ( Random() * 2.0f ) - 1.0f;
    V.v[YDIM] = ( Random() * 2.0f ) - 1.0f;
    V.v[ZDIM] = ( Random() * 2.0f ) - 1.0f;

    V.Normalize();
	return V;
}
