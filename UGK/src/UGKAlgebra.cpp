/**	Common algebra types

	Prefix: UGKALG_

	@author Ramon Molla and Ángel Sanchis
	@version 2014-05 / 2015-01

*/

#include <UGKalgebra.h>
#include "math.h"

using namespace UGK;

#ifdef UGKALG_API_DEFAULT
	UGKALG_NUMERIC_TYPE UGKALG_ModelView[UGKALG_MATRIX_SIZE];
	UGKALG_NUMERIC_TYPE UGKALG_NullVector[UGKALG_DIMENSIONS] = {UGKALG_ZERO, UGKALG_ZERO, UGKALG_ZERO, UGKALG_ZERO};
	UGKALG_NUMERIC_TYPE UGKALG_NullMatrix[UGKALG_MATRIX_SIZE] = 
	{
		UGKALG_ZERO, UGKALG_ZERO, UGKALG_ZERO, UGKALG_ZERO, 
		UGKALG_ZERO, UGKALG_ZERO, UGKALG_ZERO, UGKALG_ZERO, 
		UGKALG_ZERO, UGKALG_ZERO, UGKALG_ZERO, UGKALG_ZERO, 
		UGKALG_ZERO, UGKALG_ZERO, UGKALG_ZERO, UGKALG_ZERO
	};
#elif defined(UGKALG_API_GLM) //Code only valid for a matrix size 16!!! (UGKALG_DIMENSIONS 4)
	using namespace glm;

	m4 UGKALG_ModelView = m4(); //Identity matrix
	v4 UGKALG_NullVector = v4(UGKALG_ZERO, UGKALG_ZERO, UGKALG_ZERO, UGKALG_ZERO);
	m4 UGKALG_NullMatrix = m4(
		UGKALG_ZERO, UGKALG_ZERO, UGKALG_ZERO, UGKALG_ZERO, 
		UGKALG_ZERO, UGKALG_ZERO, UGKALG_ZERO, UGKALG_ZERO, 
		UGKALG_ZERO, UGKALG_ZERO, UGKALG_ZERO, UGKALG_ZERO, 
		UGKALG_ZERO, UGKALG_ZERO, UGKALG_ZERO, UGKALG_ZERO
	);
#endif

Vector::Vector() {}

void Vector::Reset(void)
{
#ifdef UGKALG_API_DEFAULT
	for(unsigned int i=0;i<UGKALG_DIMENSIONS;i++)
		v[i] = UGKALG_ZERO;
#elif defined(UGKALG_API_EIGEN)
	v.setZero();
#elif defined(UGKALG_API_GLM)
	v = v4(UGKALG_ZERO, UGKALG_ZERO, UGKALG_ZERO, UGKALG_ZERO);
#endif
}

void Vector::Set(UGKALG_NUMERIC_TYPE X, UGKALG_NUMERIC_TYPE Y, UGKALG_NUMERIC_TYPE Z)
{
#ifdef UGKALG_API_DEFAULT
	v[XDIM] = X;
	v[YDIM] = Y;
	v[ZDIM] = Z;
	v[WDIM] = 0.0;
#elif defined(UGKALG_API_EIGEN)
	v << X, Y, Z, 0.0f;
#elif defined(UGKALG_API_GLM)
	v = v4(X,Y,Z,0.0f);
#endif

}

Matrix::Matrix() {}

/**
*	\fn void Matrix::SetIdentity()

*	Generates an identity matrix
*	\param[in,out] M External matrix where to set the generated identity matrix
*/
void Matrix::SetIdentity()
{
#ifdef UGKALG_API_DEFAULT
	unsigned int k, l;
	for( k=0; k<UGKALG_DIMENSIONS; k++ ) 
		for( l=0; l<UGKALG_DIMENSIONS; l++ )
		{
			if ( k==l )
				M[k][l] = 1.0f;
			else
				M[k][l] = 0.0f;
		}
		M[UGKALG_DIMENSIONS-1][UGKALG_DIMENSIONS-1] = 0.0f;	//No translation at all
#elif defined(UGKALG_API_EIGEN)
	Eigen::Matrix<UGKALG_NUMERIC_TYPE, UGKALG_DIMENSIONS, UGKALG_DIMENSIONS, Eigen::RowMajor> m;
	m = Eigen::Matrix<UGKALG_NUMERIC_TYPE, UGKALG_DIMENSIONS, UGKALG_DIMENSIONS>::Identity();
	m(UGKALG_DIMENSIONS - 1, UGKALG_DIMENSIONS - 1) = 0.0f;
	v = m.data();
#elif defined(UGKALG_API_GLM)
	M = m4(); // generates identity matrix
	/*mat4 eme(1.0f);
	eme[3][3] = 0.0f;

	const UGKALG_NUMERIC_TYPE *pSource = (const UGKALG_NUMERIC_TYPE*) value_ptr(eme);
	
	//for(int i=0; i< UGKALG_MATRIX_SIZE; i++)
	//	M[i] = pSource[i]; //didn't work, try -> M[][] = pSource[i];
	
	M = make_mat4(pSource); //equivalent lo previous asignment
	crear matriz identidad*/
#endif
}

/**
*	\fn void Matrix::RotScaleReset	()

*	Undo all rotations (beware all scaling is lost as well). No translation is lost
*	\param[in,out] M External matrix where to set the generated identity matrix
*/
void Matrix::RotScaleReset()
{
#ifdef UGKALG_API_DEFAULT
	unsigned int k, l;

	for( k=0; k<UGKALG_DIMENSIONS-1; k++ ) 
		for( l=0; l<UGKALG_DIMENSIONS-1; l++ )
		{
			if ( k==l )
				M[k][l] = 1.0f;
			else
				M[k][l] = 0.0f;
		}
#elif defined(UGKALG_API_EIGEN)
	Eigen::Matrix<UGKALG_NUMERIC_TYPE, UGKALG_DIMENSIONS, ALG_DIMENSION, Eigen::RowMajor> m;
	Eigen::Matrix<UGKALG_NUMERIC_TYPE, UGKALG_DIMENSIONS - 1, 1> vcol;
	Eigen::Matrix<UGKALG_NUMERIC_TYPE, 1, ALG_DIMENSION - 1> vrow;

	for (int i = 0; i < ALG_DIMENSION - 1; i++)
	{
		vcol[i] = v[(i + 1) * ALG_DIMENSION - 1];
		vrow[i] = v[UGKALG_MATRIX_SIZE - ALG_DIMENSION + i];
	}
	m << Eigen::Matrix<UGKALG_NUMERIC_TYPE, ALG_DIMENSION - 1, ALG_DIMENSION - 1>::Identity(), vcol, vrow, v[UGKALG_MATRIX_SIZE - 1];
	v = m.data();
#elif defined(UGKALG_API_GLM)
	m4 eme(1.0f);
	vec3 col3;
	vec3 fil3;
	
	for (int i = 0; i < UGKALG_DIMENSIONS - 1; i++){
		col3[i] = M[i][3];
		fil3[i] = M[3][i]; 
	}

	for(int z=0; z < UGKALG_DIMENSIONS - 1; z++){
		eme[z][3] = col3[z];
		eme[3][z] = fil3[z];
	}

	const UGKALG_NUMERIC_TYPE *pSource = (const UGKALG_NUMERIC_TYPE*)value_ptr(eme);
	M = glm::make_mat4(pSource);
#endif
}

/**
*	\fn Vector::Vector()  

*	Vector constructor with (X, Y, Z, 0)
*	\param[in,out] (X, Y, Z) cordinates v 4 dimensions vector
*/
Vector::Vector(UGKALG_NUMERIC_TYPE X, UGKALG_NUMERIC_TYPE Y, UGKALG_NUMERIC_TYPE Z)
{
#ifdef UGKALG_API_DEFAULT
	v[XDIM] = X;
	v[YDIM] = Y;
	v[ZDIM] = Z;
	v[WDIM] = 0.0;
#elif defined(UGKALG_API_EIGEN)
	v << X, Y, Z, 0.0f;
#elif defined(UGKALG_API_GLM)
	v[XDIM] = X;
	v[YDIM] = Y;
	v[ZDIM] = Z;
	v[WDIM] = 0.0f;
#endif
}

/**
*	\fn Vector::Vector()

*	Vector constructor with (X, Y, Z, W)
*	\param[in,out] (X, Y, Z, W) cordinates v 4 dimensions vector
*/
Vector::Vector(UGKALG_NUMERIC_TYPE X, UGKALG_NUMERIC_TYPE Y, UGKALG_NUMERIC_TYPE Z, UGKALG_NUMERIC_TYPE W)
{
#ifdef UGKALG_API_DEFAULT
	v[XDIM] = X;
	v[YDIM] = Y;
	v[ZDIM] = Z;
	v[WDIM] = W;
#elif defined(UGKALG_API_EIGEN)
	v << X, Y, Z, W;
#elif defined(UGKALG_API_GLM)
	v[XDIM] = X;
	v[YDIM] = Y;
	v[ZDIM] = Z;
	v[WDIM] = W;
#endif
}

void Vector::operator += ( const Vector& A)
{
#ifdef UGKALG_API_DEFAULT
	v[XDIM] += A.v[XDIM];
	v[YDIM] += A.v[YDIM];
	v[ZDIM] += A.v[ZDIM];
#elif defined(UGKALG_API_EIGEN)
	v += A.v;
#elif defined(UGKALG_API_GLM)
	v += A.v;
#endif
}

void Vector::operator -= ( const Vector& A)
{
#ifdef UGKALG_API_DEFAULT
	v[XDIM] -= A.v[XDIM];
	v[YDIM] -= A.v[YDIM];
	v[ZDIM] -= A.v[ZDIM];
#elif defined(UGKALG_API_EIGEN)
	v -= A.v;
#elif defined(UGKALG_API_GLM)
	v -= A.v;
#endif
}

Vector  Vector::operator + ( const Vector& A) const
{
	Vector P;
#ifdef UGKALG_API_DEFAULT
	P.v[XDIM] = v[XDIM] + A.v[XDIM];
	P.v[YDIM] = v[YDIM] + A.v[YDIM];
	P.v[ZDIM] = v[ZDIM] + A.v[ZDIM];
#elif defined(UGKALG_API_EIGEN)
	P.v = v + A.v;
#elif defined(UGKALG_API_GLM)
	P.v = v + A.v;
#endif
	return P;
}

Vector  Vector::operator - ( const Vector& A) const
{
	Vector P;
#ifdef UGKALG_API_DEFAULT
	P.v[XDIM] = v[XDIM] - A.v[XDIM];
	P.v[YDIM] = v[YDIM] - A.v[YDIM];
	P.v[ZDIM] = v[ZDIM] - A.v[ZDIM];
#elif defined(UGKALG_API_EIGEN)
	P.v = v - A.v;
#elif defined(UGKALG_API_GLM)
	P.v = v - A.v;
#endif
	return P;
}

Vector  Vector::operator - (void) const
{
	Vector P;
#ifdef UGKALG_API_DEFAULT
	P.v[XDIM] = -v[XDIM];
	P.v[YDIM] = -v[YDIM];
	P.v[ZDIM] = -v[ZDIM];
#elif defined(UGKALG_API_EIGEN)
	P.v = -v;
#elif defined(UGKALG_API_GLM)
	P.v = -v;
#endif
	return P;
}

Vector	Vector::operator *	(UGKALG_NUMERIC_TYPE V) const
{
	Vector P;
#ifdef UGKALG_API_DEFAULT
	P.v[XDIM] = v[XDIM]*V;
	P.v[YDIM] = v[YDIM]*V;
	P.v[ZDIM] = v[ZDIM]*V;
#elif defined(UGKALG_API_EIGEN)
	P.v = V * v;
#elif defined(UGKALG_API_GLM)
	P.v = V * v;
#endif
	return P;
}

Vector  Vector::operator * ( const Vector& A) const
{
	Vector P;
#ifdef UGKALG_API_DEFAULT
	//Not Implemented
#elif defined(UGKALG_API_EIGEN)
	//Not Implemented
#elif defined(UGKALG_API_GLM)
	P.v = v * A.v;
#endif
	return P;
}

Vector Vector::operator / (float A) const
{
	Vector P;
#ifdef UGKALG_API_DEFAULT
	//Not Implemented
#elif defined(UGKALG_API_EIGEN)
	//Not Implemented
#elif defined(UGKALG_API_GLM)
	P.v = v / A;
#endif
	return P;
}


void Matrix::operator += ( const Matrix& A)
{
	#ifdef UGKALG_API_DEFAULT
		//Not Implemented
	#elif defined(UGKALG_API_EIGEN)
		//Not Implemented
	#elif defined(UGKALG_API_GLM)
		M += A.M;
	#endif
}

void Matrix::operator -= ( const Matrix& A)
{
	#ifdef UGKALG_API_DEFAULT
		//Not Implemented
	#elif defined(UGKALG_API_EIGEN)
		//Not Implemented
	#elif defined(UGKALG_API_GLM)
		M -= A.M;
	#endif
}

Matrix  Matrix::operator + ( const Matrix& A) const
{
	Matrix P;
	#ifdef UGKALG_API_DEFAULT
		//Not Implemented
	#elif defined(UGKALG_API_EIGEN)
		//Not Implemented
	#elif defined(UGKALG_API_GLM)
		P.M = M + A.M;
	#endif
		return P;
}

Matrix  Matrix::operator - ( const Matrix& A) const
{
	Matrix P;
	#ifdef UGKALG_API_DEFAULT
		//Not Implemented
	#elif defined(UGKALG_API_EIGEN)
		//Not Implemented
	#elif defined(UGKALG_API_GLM)
		P.M = M - A.M;
	#endif
		return P;
}

Matrix  Matrix::operator - (void) const
{
	Matrix P;
	#ifdef UGKALG_API_DEFAULT
		//Not Implemented
	#elif defined(UGKALG_API_EIGEN)
		//Not Implemented
	#elif defined(UGKALG_API_GLM)
		P.M = - M;
	#endif
		return P;
}

Matrix	Matrix::operator *	(UGKALG_NUMERIC_TYPE V) const
{
	Matrix P;
	#ifdef UGKALG_API_DEFAULT
		//Not Implemented
	#elif defined(UGKALG_API_EIGEN)
		//Not Implemented
	#elif defined(UGKALG_API_GLM)
		P.M = V * M;
	#endif
		return P;
}

Matrix  Matrix::operator * ( const Matrix& A) const
{
	Matrix P;
	#ifdef UGKALG_API_DEFAULT
		//Not Implemented
	#elif defined(UGKALG_API_EIGEN)
		//Not Implemented
	#elif defined(UGKALG_API_GLM)
		P.M = M * A.M;
	#endif
		return P;
}

/**
   * General Bezier curve
   * Interpolates the position for any given time.
   * @param p Vector of control points for determining the shape of the Bezier curve.
   * @param n	The amount of control points to be taken into account. The size of parameter p plus one
   *			Uses Vector control_points[n+1];
   *			Defined by:  control_points[0].Position.v[XDIM]=... until control_points[n].Position.v[ZDIM]=...
   * @param mu The time elapsed in normalized coordinates between [0,1]. Determines the exact position on the curve
   * @see Vector
   * @return A given 3D point that belongs to the curve for mu in the interval [0,1]. Where the curve is at a moment given by parameter mu
   * Calling example => return_point = UGKALG_Bezier(control_points, 5, t); (example for 6 control points)
   */

Vector UGK::Bezier(Vector *p, int n,UGKALG_NUMERIC_TYPE mu)
{
   int k,kn,nn,nkn;
   UGKALG_NUMERIC_TYPE blend,muk,munk;
   Vector b;

   b.Reset();

   // Particular case for mu = 1
   if (mu == UGKALG_ONE)
   {
		b = p[n];
		return(b);
   }

   // General case
   muk = UGKALG_ONE;
   munk = pow(UGKALG_ONE-mu,(UGKALG_NUMERIC_TYPE)n);

   for (k=0;k<=n;k++) {
      nn = n;
      kn = k;
      nkn = n - k;
      blend = muk * munk;
      muk *= mu;
      munk /= (UGKALG_ONE-mu);
      while (nn >= 1) {
         blend *= nn;
         nn--;
         if (kn > 1) {
            blend /= (UGKALG_NUMERIC_TYPE)kn;
            kn--;
         }
         if (nkn > 1) {
            blend /= (UGKALG_NUMERIC_TYPE)nkn;
            nkn--;
         }
      }
	  b += p[k] * (UGKALG_NUMERIC_TYPE)blend;
   }
   return(b);
}

/**
   * General Transformation Matrix
   * @see TRANSFORMATION_TYPE
   * @param transf_type Type os transformation
   * @param angle	angle to rotate - only for rotations, default null
   * @param axis	rotation axis - only for rotations, default null
   * @param x_value	translation or scale in x axis - only if not rotation, default null
   * @param y_value	translation or scale in y axis - only if not rotation, default null
   * @param z_value	translation or scale in z axis - only if not rotation, default null
   * @return a matrix to do the desired transformation.
   * Calling example => M = UGK::getGenericTransfMatrix(TRASLATION, 0, XDIM,-10, 0, 5);
   */
void Matrix::SetGenericTransfMatrix(TRANSFORMATION_TYPE transf_type, float angle, SpaceCoords axis,float x_value, float y_value, float z_value)
{
	switch(transf_type)
		{case TRASLATION: //Rotate x axis
				return SetTranslationMatrix(x_value, y_value,z_value);	
			break;
		case SCALE:	//Rotate y axis
				return SetScaleMatrix(x_value, y_value,z_value);
			break;
		case ROTATION:	//Rotate y axis
				return SetRotationMatrix(angle, axis);		
			break;
		default:
			break;
	};
}

/**
   * Rotation Matrix
   * @param angle	angle to rotate
   * @param axis	rotation axis
   * Calling example => M = UGK::getRotationMatrix(15.5f, YDIM);
   */
void Matrix::SetRotationMatrix(float angle, SpaceCoords axis)
{
	#ifdef UGKALG_API_DEFAULT
		//Implement the code for default api
	#elif defined(UGKALG_API_EIGEN)
		//Implement the code for Eigen api
	#elif defined(UGKALG_API_GLM)
		vec3 axis_vector;
		switch(axis)
		{case XDIM: //Rotate x axis
				axis_vector = vec3(1.0f, 0.0f, 0.0f);
			break;
		 case YDIM:	//Rotate y axis
				axis_vector = vec3(0.0f, 1.0f, 0.0f);
			break;
		case ZDIM:	//Rotate y axis
				axis_vector = vec3(0.0f, 0.0f, 1.0f);
			break;
		default:;
		};
		M = rotate(m4(), angle, axis_vector);
	#endif
}


/**
   * Scale Matrix
   * @param x_scale	x axis scale value
   * @param y_scale	y axis scale value
   * @param z_scale	z axis scale value
   * Calling example => M = UGK::getScaleMatrix(1.5f, 1.0f, 1.0f);
   */
void Matrix::SetScaleMatrix(float x_scale, float y_scale,float z_scale)
{
	#ifdef UGKALG_API_DEFAULT
		//Implement the code for default api
	#elif defined(UGKALG_API_EIGEN)
		//Implement the code for Eigen api
	#elif defined(UGKALG_API_GLM)
		M = scale(m4(), vec3(x_scale, y_scale, z_scale));
	#endif
}

/**
   * Translation Matrix
   * @param x_incr x axis increment value
   * @param y_incr y axis increment value
   * @param z_incr z axis increment value
   * Calling example => M = UGK::getTranslationMatrix(-2.0f, 0.0f, 3.0f);
   */
void Matrix::SetTranslationMatrix(float x_incr, float y_incr,float z_incr)
{
	#ifdef UGKALG_API_DEFAULT
		//Implement the code for default api
	#elif defined(UGKALG_API_EIGEN)
		//Implement the code for Eigen api
	#elif defined(UGKALG_API_GLM)
		M = translate(m4(), vec3(x_incr, y_incr, z_incr));
	#endif
}