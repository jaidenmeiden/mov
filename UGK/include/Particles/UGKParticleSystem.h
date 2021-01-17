/**
 * @file	inc\UGKParticleSystem.h
 *
 * @brief	Declares the ugk particle system class.
 * 		
 *	Prefix: UGKPSYS_
 * @author	Joaquin Taverner y Fran Munyoz
 * @date	25/02/2017
 */

#ifndef UGKPSYS_PARTICLE_SYS
#define UGKPSYS_PARTICLE_SYS

#pragma once

#include "UGKParticle.h"
#include "UGKParticleInterpolator.h"

	namespace UGK
	{
	/**
	 * @class	UGKParticleCamera
	 *
	 * @brief	An ugk particle camera.
	 */

		class UGKParticleCamera;

	/**
	 * @class	UGKParticleEmitter
	 *
	 * @brief	An ugk particle emitter.
	 */

		class UGKParticleEmitter;

	/**
	 * @class	UGKParticleSystem
	 *
	 * @brief	ParticleEffect class that demonstrates one possible implementation for billboard
	 * 			particles.
	 */
		class UGKParticleSystem
		{
		public:

			/**
			 * @struct	Vertex
			 *
			 * @brief	A vertex for the particle.
			 */

			struct Vertex
			{
				Vertex()
					: m_Pos(0,0,0)
					, m_Diffuse(0, 0, 0)
					, m_Tex0(0, 0, 0)
				{}  ///< .

				Vector		m_Pos,		///< Vertex position
							m_Diffuse,  ///< Diffuse color
							m_Tex0;		///< Texture coordinate
			};

			/**
			 * @typedef	std::vector<Vertex> VertexBuffer
			 *
			 * @brief	Defines an alias representing buffer for vertex data.
			 */

			typedef std::vector<Vertex> VertexBuffer;

			/**
			 * @typedef	UGKParticleInterpolator<glm::vec4> ColorInterpolator
			 *
			 * @brief	Defines an alias representing the color interpolator.
			 */

			typedef UGKParticleInterpolator<Vector> ColorInterpolator;

			/**
			 * @fn	UGKParticleSystem::UGKParticleSystem( unsigned int numParticles = 0 );
			 *
			 * @brief	Constructor.
			 *
			 * @param	numParticles	(Optional) Number of particles.
			 */

			UGKParticleSystem(unsigned int numParticles = 0);

			/**
			 * @fn	virtual UGKParticleSystem::~UGKParticleSystem();
			 *
			 * @brief	Destructor.
			 */

			virtual ~UGKParticleSystem();

			/**
			 * @fn	void UGKParticleSystem::SetCamera( UGKParticleCamera* pCamera );
			 *
			 * @brief	Sets a camera.
			 *
			 * @param [in,out]	pCamera	If non-null, the camera.
			 */

			void SetCamera(UGKParticleCamera* pCamera);

			/**
			 * @fn	void UGKParticleSystem::SetParticleEmitter( UGKParticleEmitter* pEmitter );
			 *
			 * @brief	Sets particle emitter.
			 *
			 * @param [in,out]	pEmitter	If non-null, the emitter.
			 */

			void SetParticleEmitter(UGKParticleEmitter* pEmitter);

			/**
			 * @fn	void UGKParticleSystem::SetColorInterplator( const ColorInterpolator& colors );
			 *
			 * @brief	Sets color interplator.
			 *
			 * @param	colors	The colors.
			 */

			void SetColorInterplator(const ColorInterpolator& colors);

			/**
			 * @fn	void UGKParticleSystem::RandomizeParticles();
			 *
			 * @brief	Test method to randomize the particles in an interesting way.
			 */

			void RandomizeParticles();

			/**
			 * @fn	void UGKParticleSystem::EmitParticles();
			 *
			 * @brief	Emit particles.
			 */

			void EmitParticles();

			/**
			 * @fn	virtual void UGKParticleSystem::Update( float fDeltaTime );
			 *
			 * @brief	Updates the given fDeltaTime.
			 *
			 * @param	fDeltaTime	The delta time.
			 */

			virtual void Update(float fDeltaTime);

			/**
			 * @fn	virtual void UGKParticleSystem::Render();
			 *
			 * @brief	Renders this object.
			 */

			virtual void Render();

			/**
			 * @fn	bool UGKParticleSystem::LoadTexture( const std::string& fileName );
			 *
			 * @brief	Loads a texture.
			 *
			 * @param	fileName	Filename of the file.
			 *
			 * @return	True if it succeeds, false if it fails.
			 */

			bool LoadTexture(const std::string& fileName);

			/**
			 * @fn	void UGKParticleSystem::Resize( unsigned int numParticles );
			 *
			 * @brief	Resize the particle buffer with numParticles.
			 *
			 * @param	numParticles	Number of particles.
			 */

			void Resize(unsigned int numParticles);

		protected:

			/**
			 * @fn	void UGKParticleSystem::RandomizeParticle( UGKParticle& particle );
			 *
			 * @brief	Randomize particle.
			 *
			 * @param [in,out]	particle	The particle.
			 */

			void RandomizeParticle(UGKParticle& particle);

			/**
			 * @fn	void UGKParticleSystem::EmitParticle( UGKParticle& particle );
			 *
			 * @brief	Emit particle.
			 *
			 * @param [in,out]	particle	The particle.
			 */

			void EmitParticle(UGKParticle& particle);
		public:

			/**
			 * @fn	void UGKParticleSystem::BuildVertexBuffer();
			 *
			 * @brief	Build the vertex buffer from the particle buffer.
			 */

			void BuildVertexBuffer();

		private:
			UGKParticleCamera*  m_pCamera;				///< The camera
			UGKParticleEmitter* m_pParticleEmitter;		///< The particle emitter
			ColorInterpolator   m_ColorInterpolator;	///< The color interpolator

			ParticleBuffer      m_Particles;			///< The particles
			VertexBuffer        m_VertexBuffer;			///< Buffer for vertex data
			Matrix		        m_LocalToWorldMatrix;   ///< The local to world matrix
			GLuint              m_TextureID;			///< Identifier for the texture

			// Apply this force to every particle in the effect
			Vector			    m_Force;				///< The force
		};
	}
#endif