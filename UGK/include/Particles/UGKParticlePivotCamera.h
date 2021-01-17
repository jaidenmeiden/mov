/**
 * @file	inc\UGKParticlePivotCamera.h
 *
 * @brief	Declares the ugk particle pivot camera class.
 * 			
 * @author	Joaquin Taverner y Fran Munyoz
 * @date	25/02/2017
 */

#pragma once;

#include "UGKParticleCamera.h"
using namespace UGK;

/**
 * @class	UGKParticlePivotCamera
 *
 * @brief	An ugk particle pivot camera.
 */

class UGKParticlePivotCamera : public UGKParticleCamera
{
public:

    /**
     * @typedef	UGKParticleCamera base
     *
     * @brief	Defines an alias representing the base.
     */

    typedef UGKParticleCamera base;

    /**
     * @fn	UGKParticlePivotCamera::UGKParticlePivotCamera();
     *
     * @brief	Default constructor.
     */

    UGKParticlePivotCamera();

    /**
     * @fn	virtual void UGKParticlePivotCamera::Update( float fDeltaTime );
     *
     * @brief	Updates the given fDeltaTime.
     *
     * @param	fDeltaTime	The delta time.
     */

    virtual void Update( float fDeltaTime );

    /**
     * @fn	virtual void UGKParticlePivotCamera::ApplyViewTransform();
     *
     * @brief	Applies the view transform.
     */

    virtual void ApplyViewTransform();

    /**
     * @fn	glm::vec3 UGKParticlePivotCamera::ProjectOntoUnitSphere( glm::vec2 screenPos );
     *
     * @brief	Project a position in screen coordinates onto a unit sphere centered at the origin
     * 			and return the projected point .
     *
     * @param	screenPos	The screen position.
     *
     * @return	A glm::vec3.
     */

    Vector ProjectOntoUnitSphere( Vector screenPos );

    /**
     * @fn	void UGKParticlePivotCamera::TranslatePivotX( float x );
     *
     * @brief	Translate pivot x coordinate.
     *
     * @param	x	The x coordinate.
     */

    void TranslatePivotX( float x );

    /**
     * @fn	void UGKParticlePivotCamera::TranslatePivotY( float y );
     *
     * @brief	Translate pivot y coordinate.
     *
     * @param	y	The y coordinate.
     */

    void TranslatePivotY( float y );

    /**
     * @fn	void UGKParticlePivotCamera::TranslatePivotZ( float z );
     *
     * @brief	Translate pivot z coordinate.
     *
     * @param	z	The z coordinate.
     */

    void TranslatePivotZ( float z );

    /**
     * @fn	void UGKParticlePivotCamera::SetPivot( const glm::vec3& pivot );
     *
     * @brief	Sets a pivot.
     *
     * @param	pivot	The pivot.
     */

    void SetPivot( const Vector& pivot );

    /**
     * @fn	glm::vec3 UGKParticlePivotCamera::GetPivot() const;
     *
     * @brief	Gets the pivot.
     *
     * @return	The pivot.
     */

	Vector GetPivot() const;

protected:
    // The point around which the camera will pivot.
    Vector   m_PivotPoint;   ///< The pivot point

private:

};