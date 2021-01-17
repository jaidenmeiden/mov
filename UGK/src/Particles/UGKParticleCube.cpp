/**
 * @file	src\UGKParticleCube.cpp
 *
 * @brief	Implements the ugk particle cube class.
 * 			
 * @author	Joaquin Taverner y Fran Munyoz
 * @date	25/02/2017
 */

#include "UGKParticleInclude.h"
#include "Random.h"
#include "UGKParticleCube.h"

/**
 * @fn	UGKParticleCube::UGKParticleCube()
 *
 * @brief	Default constructor.
 */

UGKParticleCube::UGKParticleCube()
: MinWidth(-1)
, MaxWidth(1)
, MinHeight(-1)
, MaxHeight(1)
, MinDepth(-1)
, MaxDepth(1)
, MinSpeed(10)
, MaxSpeed(20)
, MinLifetime(3)
, MaxLifetime(5)
, Origin(0,0,0)
{}

/**
 * @fn	void UGKParticleCube::EmitParticle( UGKParticle& particle )
 *
 * @brief	Emit particle.
 *
 * @param [in,out]	particle	The particle.
 */

void UGKParticleCube::EmitParticle( UGKParticle& particle )
{
    float X = RandRange( MinWidth, MaxWidth );
    float Y = RandRange( MinHeight, MaxHeight );
    float Z = RandRange( MinDepth, MaxDepth );

    float lifetime = RandRange( MinLifetime, MaxLifetime );
    float speed = RandRange( MinSpeed, MaxSpeed );

    Vector vector( X, Y, Z );

    particle.position = vector + Origin;
    //ALGEBRA particle.velocity = glm::normalize(vector) * speed;

    particle.duration = lifetime;
    particle.life = 0;
}

/**
 * @fn	void UGKParticleCube::DebugRender()
 *
 * @brief	Debug render.
 */

void UGKParticleCube::DebugRender()
{
    glTranslatef( Origin.v[XDIM], Origin.v[YDIM], Origin.v[ZDIM] );

    glColor4f( 1.0f, 0.0f, 1.0f, 1.0f );
    
    glutWireCube( MaxWidth * 2 );

    glTranslatef( -Origin.v[XDIM], -Origin.v[YDIM], -Origin.v[ZDIM] );
}
