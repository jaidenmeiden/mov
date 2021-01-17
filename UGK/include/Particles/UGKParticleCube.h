/**
 * @file	inc\UGKParticleCube.h
 *
 * @brief	Declares the ugk particle cube class.
 * 			
 * @author	Joaquin Taverner y Fran Munyoz
 * @date	25/02/2017
 */

#pragma once;
#include "UGKParticleEmitter.h"

/**
 * @class	UGKParticleCube
 *
 * @brief	An ugk particle cube.
 */

class UGKParticleCube : public UGKParticleEmitter
{
public:

    /**
     * @fn	UGKParticleCube::UGKParticleCube();
     *
     * @brief	Default constructor.
     */

    UGKParticleCube();

    /**
     * @fn	virtual void UGKParticleCube::EmitParticle( UGKParticle& particle );
     *
     * @brief	Emit particle.
     *
     * @param [in,out]	particle	The particle.
     */

    virtual void EmitParticle( UGKParticle& particle );

    /**
     * @fn	virtual void UGKParticleCube::DebugRender();
     *
     * @brief	Debug render.
     */

    virtual void DebugRender();

    float MinWidth; ///< The minimum width
    float MaxWidth; ///< The maximum width

    float MinHeight;	///< The minimum height
    float MaxHeight;	///< The maximum height

    float MinDepth; ///< The minimum depth
    float MaxDepth; ///< The maximum depth

    float MinSpeed; ///< The minimum speed
    float MaxSpeed; ///< The maximum speed

    float MinLifetime;  ///< The minimum lifetime
    float MaxLifetime;  ///< The maximum lifetime

    Vector   Origin; ///< The origin
};