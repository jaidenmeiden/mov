/**
 * @file	inc\UGKParticleCamera.h
 *
 * @brief	Declares the ugk particle camera class.
 * 			
 * @author	Joaquin Taverner y Fran Munyoz
 * @date	25/02/2017
 */

#pragma once;

#include <UGKAlgebra.h>

/**
 * @class	UGKParticleCamera
 *
 * @brief	An ugk particle camera.
 */

namespace UGK
{
	class UGKParticleCamera
	{
	public:

		/**
		 * @fn	UGKParticleCamera::UGKParticleCamera()
		 *
		 * @brief	Default constructor.
		 */

		UGKParticleCamera() : m_Translate(0,0,0) {}

		/**
		 * @fn	virtual UGKParticleCamera::~UGKParticleCamera()
		 *
		 * @brief	Destructor.
		 */

		virtual ~UGKParticleCamera() {};

		/**
		 * @fn	void UGKParticleCamera::SetViewport( int x, int y, int width, int height );
		 *
		 * @brief	Set viewport parameters.
		 *
		 * @param	x	  	The x coordinate.
		 * @param	y	  	The y coordinate.
		 * @param	width 	The width.
		 * @param	height	The height.
		 */

		void SetViewport(int x, int y, int width, int height);

		/**
		 * @fn	void UGKParticleCamera::SetProjection( float fovy, float aspect, float zNear, float zFar );
		 *
		 * @brief	Set projection prameters.
		 *
		 * @param	fovy  	The fovy.
		 * @param	aspect	The aspect.
		 * @param	zNear 	The near.
		 * @param	zFar  	The far.
		 */

		void SetProjection(float fovy, float aspect, float zNear, float zFar);

		/**
		 * @fn	void UGKParticleCamera::AddPitch( float fPitch );
		 *
		 * @brief	Add this pitch (rotation about the X-axis) in degrees to the current camera's pitch.
		 *
		 * @param	fPitch	The pitch.
		 */

		void AddPitch(float fPitch);

		/**
		 * @fn	void UGKParticleCamera::AddYaw( float fYaw );
		 *
		 * @brief	Add this yaw (rotation about the Y-axis) in degrees to the current camera's yaw.
		 *
		 * @param	fYaw	The yaw.
		 */

		void AddYaw(float fYaw);

		/**
		 * @fn	void UGKParticleCamera::AddRoll( float fRoll );
		 *
		 * @brief	Add this roll (rotation about the Z-axis) in degrees to the current camera's roll.
		 *
		 * @param	fRoll	The roll.
		 */

		void AddRoll(float fRoll);

		/**
		 * @fn	void UGKParticleCamera::AddRotation( const Quaternion& rot );
		 *
		 * @brief	Adds a rotation.
		 *
		 * @param	rot	The rot.
		 */

		void AddRotation(const Quaternion& rot);

		/**
		 * @fn	void UGKParticleCamera::TranslateX( float x );
		 *
		 * @brief	Translate the along the camera's X-axis.
		 *
		 * @param	x	The x coordinate.
		 */

		void TranslateX(float x);

		/**
		 * @fn	void UGKParticleCamera::TranslateY( float y );
		 *
		 * @brief	Translate along the camera's Y-axis.
		 *
		 * @param	y	The y coordinate.
		 */

		void TranslateY(float y);

		/**
		 * @fn	void UGKParticleCamera::TranslateZ( float z );
		 *
		 * @brief	Translate along the camera's Z-axis.
		 *
		 * @param	z	The z coordinate.
		 */

		void TranslateZ(float z);

		/**
		 * @fn	void UGKParticleCamera::SetTranslate( const glm::vec3& translate );
		 *
		 * @brief	Set the current translation of the camera, replacing the current value.
		 *
		 * @param	translate	The translate.
		 */

		void SetTranslate(const Vector& translate);

		/**
		 * @fn	void UGKParticleCamera::SetRotate( float pitch, float yaw, float roll );
		 *
		 * @brief	Set the current euler angles in degrees, replacing the current values.
		 *
		 * @param	pitch	The pitch.
		 * @param	yaw  	The yaw.
		 * @param	roll 	The roll.
		 */

		void SetRotate(float pitch, float yaw, float roll);

		/**
		 * @fn	void UGKParticleCamera::SetRotate( const glm::vec3& rotate );
		 *
		 * @brief	Sets a rotate.
		 *
		 * @param	rotate	The rotate.
		 */

		void SetRotate(const Vector& rotate);

		/**
		 * @fn	glm::vec3 UGKParticleCamera::GetTranslation() const;
		 *
		 * @brief	Gets the translation.
		 *
		 * @return	The translation.
		 */

		Vector GetTranslation() const;

		/**
		 * @fn	glm::vec3 UGKParticleCamera::GetRotation() const;
		 *
		 * @brief	Gets the rotation.
		 *
		 * @return	The rotation.
		 */

		Vector GetRotation() const;

		/**
		 * @fn	virtual void UGKParticleCamera::Update( float fDeltaTime ) = 0;
		 *
		 * @brief	Updates the given fDeltaTime.
		 *
		 * @param	fDeltaTime	The delta time.
		 */

		virtual void Update(float fDeltaTime) = 0;

		/**
		 * @fn	virtual void UGKParticleCamera::ApplyViewport();
		 *
		 * @brief	Applies the viewport.
		 */

		virtual void ApplyViewport();

		/**
		 * @fn	virtual void UGKParticleCamera::ApplyProjectionTransform();
		 *
		 * @brief	Applies the projection transform.
		 */

		virtual void ApplyProjectionTransform();

		/**
		 * @fn	virtual void UGKParticleCamera::ApplyViewTransform() = 0;
		 *
		 * @brief	Applies the view transform.
		 */

		virtual void ApplyViewTransform() = 0;
	protected:

		// Viewport parameters
		int         m_ViewportX;	///< The viewport x coordinate
		int         m_ViewportY;	///< The viewport y coordinate
		int         m_ViewportWidth;	///< Width of the viewport
		int         m_ViewportHeight;   ///< Height of the viewport

		// Projection parameters
		float       m_fVFOV;	///< The vfov
		float       m_fAspect;  ///< The aspect
		float       m_fNear;	///< The near
		float       m_fFar; ///< The far

		// View space parameters
		Vector   m_Translate;	///< The translate
		// Rotate in pitch, yaw, roll
		Vector   m_Rotate;   ///< The rotate
	private:

	};
}