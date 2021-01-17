/**
 * @file	src\UGKParticleSphere.cpp
 *
 * @brief	Implements the ugk particle sphere class.
 * 			
 * @author	Joaquin Taverner y Fran Munyoz
 * @date	25/02/2017
 */

#include "UGKParticleInclude.h"
#include "Random.h"
#include "UGKParticleSphere.h"

/**
 * @fn	UGKParticleSphere::UGKParticleSphere()
 *
 * @brief	Default constructor.
 */

UGKParticleSphere::UGKParticleSphere()
: MinimumRadius(0)
, MaximumRadius(1)
, MinInclination(0)
, MaxInclination(180)
, MinAzimuth(0)
, MaxAzimuth(360)
, MinSpeed(10)
, MaxSpeed(20)
, MinLifetime(3)
, MaxLifetime(5)
, Origin(0,0,0)
{}

/**
 * @fn	void UGKParticleSphere::EmitParticle( UGKParticle& particle )
 *
 * @brief	Emit particle.
 *
 * @param [in,out]	particle	The particle.
 */

void UGKParticleSphere::EmitParticle( UGKParticle& particle )
{
	float inclination;//ALGEBRA  = glm::radians(RandRange(MinInclination, MaxInclination));
	float azimuth;//ALGEBRA  = glm::radians(RandRange(MinAzimuth, MaxAzimuth));

    float radius = RandRange( MinimumRadius, MaximumRadius );
    float speed = RandRange( MinSpeed, MaxSpeed );
    float lifetime = RandRange( MinLifetime, MaxLifetime );

    float sInclination = sinf( inclination );

    float X = sInclination * cosf( azimuth );
    float Y = sInclination * sinf( azimuth );
    float Z = cosf( inclination );

    Vector vector = Vector( X, Y, Z );

    particle.position = ( vector * radius ) + Origin;
    particle.velocity = vector * speed;

    particle.duration = lifetime;
    particle.life = 0;
}

/**
 * @fn	void UGKParticleSphere::RenderSphere( glm::vec4 color, float fRadius )
 *
 * @brief	Renders the sphere.
 *
 * @param	color  	The color.
 * @param	fRadius	The radius.
 */

void UGKParticleSphere::RenderSphere( Vector color, float fRadius )
{
    float X, Y, Z, inc, azi;

    //ALGEBRA glColor4fv( glm::value_ptr(color) );

    glPointSize(2.0f);
    glBegin( GL_POINTS );

    for ( float azimuth = MinAzimuth; azimuth < MaxAzimuth; azimuth += 5.0f )
    {
        for ( float inclination = MinInclination; inclination < MaxInclination; inclination += 5.0f )
        {
			//ALGEBRA inc = glm::radians(inclination);
			//ALGEBRA azi = glm::radians(azimuth);

            X = fRadius * sinf( inc ) * cosf( azi );
            Y = fRadius * sinf( inc ) * sinf( azi );
            Z = fRadius * cosf( inc );

            glVertex3f(X, Y, Z );
        }

		//ALGEBRA inc = glm::radians(MaxInclination);
		//ALGEBRA azi = glm::radians(azimuth);

        X = fRadius * sinf( inc ) * cosf( azi );
        Y = fRadius * sinf( inc ) * sinf( azi );
        Z = fRadius * cosf( inc );

        glVertex3f(X, Y, Z );
    }

	//ALGEBRA inc = glm::radians(MaxInclination);
	//ALGEBRA azi = glm::radians(MaxAzimuth);

    X = MaximumRadius * sinf( inc ) * cosf( azi );
    Y = MaximumRadius * sinf( inc ) * sinf( azi );
    Z = MaximumRadius * cosf( inc );

    glVertex3f(X, Y, Z );

    glEnd();
}

/**
 * @fn	void UGKParticleSphere::DebugRender()
 *
 * @brief	Debug render.
 */

void UGKParticleSphere::DebugRender()
{
    glTranslatef( Origin.v[XDIM], Origin.v[YDIM], Origin.v[ZDIM]);

//    RenderSphere( glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), MinimumRadius );
    RenderSphere( Vector(1.0f, 0.0f, 0.0f, 1.0f), MaximumRadius );

    glTranslatef( -Origin.v[XDIM], -Origin.v[YDIM], -Origin.v[ZDIM] );
}
