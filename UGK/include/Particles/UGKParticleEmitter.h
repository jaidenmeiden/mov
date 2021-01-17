/**
 * @file	inc\UGKParticleEmitter.h
 *
 * @brief	Declares the ugk particle emitter class.
 * 			
 * @author	Joaquin Taverner y Fran Munyoz
 * @date	25/02/2017
 */

#pragma once;

#include "UGKParticle.h"

/**
 * @class	UGKParticleEmitter
 *
 * @brief	An ugk particle emitter.
 */

namespace UGK
{
	class UGKParticleEmitter
	{
	public:

		/**
		 * @fn	virtual UGKParticleEmitter::~UGKParticleEmitter()
		 *
		 * @brief	Destructor.
		 */

		virtual ~UGKParticleEmitter() {}

		/**
		 * @fn	virtual void UGKParticleEmitter::EmitParticle( UGKParticle& particle ) = 0;
		 *
		 * @brief	Emit particle.
		 *
		 * @param [in,out]	particle	The particle.
		 */

		virtual void EmitParticle(UGKParticle& particle) = 0;

		/**
		 * @fn	virtual void UGKParticleEmitter::DebugRender()
		 *
		 * @brief	Debug render.
		 */

		virtual void DebugRender() {}
	};
}