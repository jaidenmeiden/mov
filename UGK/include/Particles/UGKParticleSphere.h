/**
 * @file	inc\UGKParticleSphere.h
 *
 * @brief	Declares the ugk particle sphere class.
 * 			
 * @author	Joaquin Taverner y Fran Munyoz
 * @date	25/02/2017
 */

#pragma once;

#include "UGKParticleEmitter.h"

/**
 * @class	UGKParticleSphere
 *
 * @brief	An ugk particle sphere.
 */

class UGKParticleSphere : public UGKParticleEmitter
{
public:

    /**
     * @fn	UGKParticleSphere::UGKParticleSphere();
     *
     * @brief	Default constructor.
     */

    UGKParticleSphere();

    /**
     * @fn	virtual void UGKParticleSphere::EmitParticle( UGKParticle& particle );
     *
     * @brief	Emit particle.
     *
     * @param [in,out]	particle	The particle.
     */

    virtual void EmitParticle( UGKParticle& particle );

    /**
     * @fn	virtual void UGKParticleSphere::DebugRender();
     *
     * @brief	Debug render.
     */

    virtual void DebugRender();

    float MinimumRadius;	///< The minimum radius
    float MaximumRadius;	///< The maximum radius

    float MinInclination;   ///< The minimum inclination
    float MaxInclination;   ///< The maximum inclination

    float MinAzimuth;   ///< The minimum azimuth
    float MaxAzimuth;   ///< The maximum azimuth

    float MinSpeed; ///< The minimum speed
    float MaxSpeed; ///< The maximum speed

    float MinLifetime;  ///< The minimum lifetime
    float MaxLifetime;  ///< The maximum lifetime

    Vector   Origin; ///< The origin
    
private: 

    /**
     * @fn	void UGKParticleSphere::RenderSphere( glm::vec4 color, float fRadius );
     *
     * @brief	Renders the sphere.
     *
     * @param	color  	The color.
     * @param	fRadius	The radius.
     */

    void RenderSphere( Vector color, float fRadius );
};
