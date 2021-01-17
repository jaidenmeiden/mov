/**
 * @file	src\UGKParticleSystem.cpp
 *
 * @brief	Implements the ugk particle system class.
 * 			
 * @author	Joaquin Taverner y Fran Munyoz
 * @date	25/02/2017
 */

#include <assert.h>
#include "UGKParticleInclude.h"
#include "UGKParticleEmitter.h"
#include "UGKParticleCamera.h"
#include "Random.h"
#include "UGKParticleSystem.h"

/**
 * @fn	UGKParticleSystem::UGKParticleSystem( unsigned int numParticles ) : m_pCamera( NULL ) , m_pParticleEmitter( NULL ) , m_ColorInterpolator( glm::vec4(1) ) , m_LocalToWorldMatrix(1) , m_TextureID(0) , m_Force( 0, -9.81f, 0 )
 *
 * @brief	Constructor.
 *
 * @param	numParticles	Number of particles.
 */

UGKParticleSystem::UGKParticleSystem( unsigned int numParticles /* = 0 */ )
: m_pCamera( NULL )
, m_pParticleEmitter( NULL )
, m_ColorInterpolator( Vector(1,0,0) )
, m_LocalToWorldMatrix()	//(1)
, m_TextureID(0)
, m_Force( 0, -9.81f, 0 ) 
{
    Resize(numParticles);
}

/**
 * @fn	UGKParticleSystem::~UGKParticleSystem()
 *
 * @brief	Destructor.
 */

UGKParticleSystem::~UGKParticleSystem()
{
    if ( m_TextureID != 0 )
    {
        glDeleteTextures( 1, &m_TextureID );
        m_TextureID = 0;
    }
}

/**
 * @fn	void UGKParticleSystem::SetCamera( UGKParticleCamera* pCamera )
 *
 * @brief	Sets a camera.
 *
 * @param [in,out]	pCamera	If non-null, the camera.
 */

void UGKParticleSystem::SetCamera( UGKParticleCamera* pCamera )
{
    m_pCamera = pCamera;
}

/**
 * @fn	void UGKParticleSystem::SetParticleEmitter( UGKParticleEmitter* pEmitter )
 *
 * @brief	Sets particle emitter.
 *
 * @param [in,out]	pEmitter	If non-null, the emitter.
 */

void UGKParticleSystem::SetParticleEmitter( UGKParticleEmitter* pEmitter )
{
    m_pParticleEmitter = pEmitter;
}

/**
 * @fn	void UGKParticleSystem::SetColorInterplator( const ColorInterpolator& colors )
 *
 * @brief	Sets color interplator.
 *
 * @param	colors	The colors.
 */

void UGKParticleSystem::SetColorInterplator( const ColorInterpolator& colors )
{
    m_ColorInterpolator = colors;
}

/**
 * @fn	bool UGKParticleSystem::LoadTexture( const std::string& fileName )
 *
 * @brief	Loads a texture.
 *
 * @param	fileName	Filename of the file.
 *
 * @return	True if it succeeds, false if it fails.
 */

bool UGKParticleSystem::LoadTexture( const std::string& fileName )
{
    if ( m_TextureID != 0 )
    {
        glDeleteTextures(1, &m_TextureID );
    }

    m_TextureID = SOIL_load_OGL_texture( fileName.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS );

    return ( m_TextureID != 0 );
}

/**
 * @fn	void UGKParticleSystem::RandomizeParticle( UGKParticle& particle )
 *
 * @brief	Randomize particle.
 *
 * @param [in,out]	particle	The particle.
 */

void UGKParticleSystem::RandomizeParticle( UGKParticle& particle )
{
    particle.life = 0.0f;
    particle.duration = RandRange( 3, 5 );

    Vector unitVec = RandUnitVec();

    particle.position = unitVec * 1.0f;
    particle.velocity = unitVec * RandRange( 10, 20 );
}

/**
 * @fn	void UGKParticleSystem::RandomizeParticles()
 *
 * @brief	Randomize particles.
 */

void UGKParticleSystem::RandomizeParticles()
{
    for ( unsigned int i = 0; i < m_Particles.size(); ++i )
    {
        RandomizeParticle(m_Particles[i]);
    }
}

/**
 * @fn	void UGKParticleSystem::EmitParticle( UGKParticle& particle )
 *
 * @brief	Emit particle.
 *
 * @param [in,out]	particle	The particle.
 */

void UGKParticleSystem::EmitParticle( UGKParticle& particle )
{
    assert( m_pParticleEmitter != NULL );
    m_pParticleEmitter->EmitParticle( particle );
}

/**
 * @fn	void UGKParticleSystem::EmitParticles()
 *
 * @brief	Emit particles.
 */

void UGKParticleSystem::EmitParticles()
{
    if ( m_pParticleEmitter == NULL )
    {
        RandomizeParticles();
    }
    else 
    {
        for ( unsigned int i = 0; i < m_Particles.size(); ++i )
        {
            EmitParticle(m_Particles[i]);
        }
    }
}

/**
 * @fn	void UGKParticleSystem::BuildVertexBuffer()
 *
 * @brief	Builds vertex buffer.
 */

void UGKParticleSystem::BuildVertexBuffer()
{
    const Vector X( 0.5, 0, 0 ),
				 Y( 0, 0.5, 0 ),
				 Z( 0, 0 ,1.0 );

	Quaternion cameraRotation;

    if ( m_pCamera != NULL )
    {
       //Rehacer según Algebra cameraRotation = Quaternion( glm::radians(m_pCamera->GetRotation()) );    
    }

    // Make sure the vertex buffer has enough vertices to render the effect
    // If the vertex buffer is already the correct size, no change is made.
    m_VertexBuffer.resize(m_Particles.size() * 4, Vertex() );

    for ( unsigned int i = 0; i < m_Particles.size(); ++i )
    {
        UGKParticle& particle = m_Particles[i];
		Quaternion rotation;//ALGEBRA  = glm::angleAxis(particle.rotate, Z);

        unsigned int vertexIndex = i * 4;
        Vertex& v0 = m_VertexBuffer[vertexIndex + 0];   // Bottom-left
        Vertex& v1 = m_VertexBuffer[vertexIndex + 1];   // Bottom-right
        Vertex& v2 = m_VertexBuffer[vertexIndex + 2];   // Top-right
        Vertex& v3 = m_VertexBuffer[vertexIndex + 3];   // Top-left

        // Bottom-left
        v0.m_Pos = particle.position + cameraRotation*( rotation * ( -X - Y ) * particle.size );
        v0.m_Tex0 = Vector( 0, 1, 0 );
        v0.m_Diffuse = particle.color;

        // Bottom-right
        v1.m_Pos = particle.position + cameraRotation*( rotation * ( X - Y ) * particle.size );
        v1.m_Tex0 = Vector( 1, 1, 0 );
        v1.m_Diffuse = particle.color;

        // Top-right
        v2.m_Pos = particle.position + cameraRotation*( rotation * ( X + Y ) * particle.size );
        v2.m_Tex0 = Vector( 1, 0, 0 );
        v2.m_Diffuse = particle.color;

        // Top-left
        v3.m_Pos = particle.position + cameraRotation*( rotation * ( -X + Y ) * particle.size );
        v3.m_Tex0 = Vector( 0, 0, 0 );
        v3.m_Diffuse = particle.color;
    }
}

/**
 * @fn	void UGKParticleSystem::Update(float fDeltaTime)
 *
 * @brief	Updates the given fDeltaTime.
 *
 * @param	fDeltaTime	The delta time.
 */

void UGKParticleSystem::Update(float fDeltaTime)
{
    for ( unsigned int i = 0; i < m_Particles.size(); ++i )
    {
        UGKParticle& particle = m_Particles[i];

        particle.life += fDeltaTime;
        if ( particle.life > particle.duration )
        {
            if ( m_pParticleEmitter != NULL ) EmitParticle(particle);
            else RandomizeParticle(particle);
        }

		float lifeRatio;	//ALGEBRA = glm::saturate(particle.life / particle.duration);
        particle.velocity += ( m_Force * fDeltaTime );
        particle.position += ( particle.velocity * fDeltaTime );
        particle.color = m_ColorInterpolator.GetValue( lifeRatio );
		//ALGEBRA particle.rotate = glm::lerp<float>( 0.0f, 720.0f, lifeRatio );
		//ALGEBRA particle.size = glm::lerp<float>( 5.0f, 0.0f, lifeRatio );
    }

    BuildVertexBuffer();
}

/**
 * @fn	void UGKParticleSystem::Render()
 *
 * @brief	Renders this object.
 */

void UGKParticleSystem::Render()
{
    glDisable(GL_DEPTH_TEST);           // Disables Depth Testing
    glEnable(GL_BLEND);                 // Enable Blending
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);   // Type Of Blending To Perform
    glEnable(GL_TEXTURE_2D);            // Enable textures

    glPushMatrix();
	//ALGEBRA glMultMatrixf( glm::value_ptr(m_LocalToWorldMatrix) );
    
    glBindTexture( GL_TEXTURE_2D, m_TextureID );

    glEnableClientState( GL_VERTEX_ARRAY );
    glEnableClientState( GL_TEXTURE_COORD_ARRAY );
    glEnableClientState( GL_COLOR_ARRAY );

    glVertexPointer( 3, GL_FLOAT, sizeof(Vertex), &(m_VertexBuffer[0].m_Pos) );
    glTexCoordPointer( 2, GL_FLOAT, sizeof(Vertex), &(m_VertexBuffer[0].m_Tex0) );
    glColorPointer( 4, GL_FLOAT, sizeof(Vertex), &(m_VertexBuffer[0].m_Diffuse) );

    glDrawArrays( GL_QUADS, 0, m_VertexBuffer.size() );

    glDisableClientState( GL_VERTEX_ARRAY );
    glDisableClientState( GL_TEXTURE_COORD_ARRAY );
    glDisableClientState( GL_COLOR_ARRAY );

    glBindTexture( GL_TEXTURE_2D, 0 );

#if _DEBUG
    if ( m_pParticleEmitter != NULL )
    {
        m_pParticleEmitter->DebugRender();
    }
#endif

    glPopMatrix();

}

/**
 * @fn	void UGKParticleSystem::Resize( unsigned int numParticles )
 *
 * @brief	Resizes the given number particles.
 *
 * @param	numParticles	Number of particles.
 */

void UGKParticleSystem::Resize( unsigned int numParticles )
{
    m_Particles.resize( numParticles,  UGKParticle() );
    m_VertexBuffer.resize( numParticles * 4, Vertex() );
}
