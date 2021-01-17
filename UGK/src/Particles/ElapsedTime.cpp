/**
 * @file	src\ElapsedTime.cpp
 *
 * @brief	Implements the elapsed time class.
 * 			
 * @author	Joaquin Taverner y Fran Munyoz
 * @date	25/02/2017
 */

#include "UGKParticleInclude.h"
#include "ElapsedTime.h"
#include <algorithm>

/**
 * @fn	ElapsedTime::ElapsedTime( float maxTimeStep ) : m_fMaxTimeStep( maxTimeStep ) , m_fPrevious ( std::clock() / (float)CLOCKS_PER_SEC )
 *
 * @brief	Constructor.
 *
 * @param	maxTimeStep	The maximum time step.
 */

ElapsedTime::ElapsedTime( float maxTimeStep /* = 0.03333f */ )
: m_fMaxTimeStep( maxTimeStep )
, m_fPrevious ( std::clock() / (float)CLOCKS_PER_SEC )
{}

/**
 * @fn	float ElapsedTime::GetElapsedTime() const
 *
 * @brief	Gets elapsed time.
 *
 * @return	The elapsed time.
 */

float ElapsedTime::GetElapsedTime() const
{
    float fCurrentTime = std::clock() / (float)CLOCKS_PER_SEC;
    float fDeltaTime = fCurrentTime - m_fPrevious;
    m_fPrevious = fCurrentTime;

    // Clamp to the max time step
    fDeltaTime = std::min( fDeltaTime, m_fMaxTimeStep );

    return fDeltaTime;
}
