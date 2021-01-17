/**
 * @file	inc\UGKParticle.h
 *
 * @brief	Declares the ugk particle class.
 * 			
 *	Prefix: UGKPRC_
 * @author	Joaquin Taverner y Fran Munyoz
 * @date	25/02/2017
 */

#ifndef UGKPRC_PARTICLE
#define UGKPRC_PARTICLE
#pragma once

	/**
	 * @struct	UGKParticle
	 *
	 * @brief	An ugk particle.
	 */

	#include <UGKAlgebra.h>

	namespace UGK
	{
		struct UGKParticle
		{
			UGKParticle()
				: position(0,0,0)
				, velocity(0, 0, 0)
				, color(0, 0, 0)
				, rotate(0)
				, life(0)
				, duration(0)
			{}  ///< .

			Vector		position,   ///< Center point of particle
						velocity,   ///< Current particle velocity
						color;		///< Particle color
			float       rotate;		///< Rotate the particle the center
			float       size;		///< Size of the particle
			float       life;		///< The life
			float       duration;   ///< The duration
		};

		/**
		 * @typedef	std::vector<UGKParticle> ParticleBuffer
		 *
		 * @brief	Defines an alias representing buffer for particle data.
		 */

		typedef std::vector<UGKParticle> ParticleBuffer;
	}
#endif