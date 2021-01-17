/**	Definition common algebra types

*	Prefix: UGKALG_

	@author Ramon Molla and Ángel Sanchis
	@version 2014-05 / 2017-03

*/

#ifndef UGKALG_ALGEBRA
#define UGKALG_ALGEBRA

//UGKALG_MATRIX_SIZE = UGKALG_DIMENSIONS x UGKALG_DIMENSIONS
#define UGKALG_MATRIX_SIZE 16

//#define UGKALG_2D
//2.5 dimensions. Isometric rendering where Z coordinate maps directly on X,Y screen coordinates
//#define UGKALG_2D5
//#define UGKALG_3D
#define UGKALG_4D

//Selection of the Algebra API used
//#define UGKALG_API_DEFAULT			0
//#define UGKALG_API_EIGEN				1
#define UGKALG_API_GLM					2
//#define UGKALG_API_BLAS				3
//#define UGKALG_API_FIXED_POINT		4

//Template to include/define depending on the API loaded
#ifdef UGKALG_API_DEFAULT
#elif defined(UGKALG_API_EIGEN)
#elif defined(UGKALG_API_GLM)
#endif

#ifdef UGKALG_API_DEFAULT
#include <math.h>
	#define UGKALG_SIMPLE
	//#define UGKALG_DOUBLE
	//#define UGKALG_FIXED_POINT

	#ifdef UGKALG_SIMPLE
		#define UGKALG_NUMERIC_TYPE float
		#define UGKALG_MAX_VALUE FLT_MAX
		#define UGKALG_ONE			1.0f
		#define UGKALG_ZERO			0.0f
	#elif defined (UGKALG_DOUBLE)
		#define UGKALG_NUMERIC_TYPE double
		#define UGKALG_MAX_VALUE DBL_MAX
		#define UGKALG_ONE			1.0
		#define UGKALG_ZERO			0.0
	#elif defined (UGKALG_FIXED_POINT)
		#include <UGKFPA64b.h>
		#define UGKALG_NUMERIC_TYPE UGKFPA64b
		#define UGKALG_ONE			UGKFPA64b_ONE	
		#define UGKALG_ZERO			UGKFPA64b_ZERO
	#endif
#elif defined(UGKALG_API_EIGEN)
	#include <Eigen/Core>
	#include <Eigen/Geometry>
	#define UGKALG_NUMERIC_TYPE float
	#define UGKALG_MAX_VALUE FLT_MAX
	#define UGKALG_ONE			1.0f
	#define UGKALG_ZERO			0.0f
#elif defined(UGKALG_API_GLM)
	#define UGKALG_SIMPLE
	//#define UGKALG_DOUBLE
	#ifdef UGKALG_SIMPLE
		#define UGKALG_NUMERIC_TYPE float
		#define UGKALG_MAX_VALUE FLT_MAX
//		#define GLM_PRECISION_MEDIUMP_FLOAT
		#define UGKALG_ONE			1.0f
		#define UGKALG_ZERO			0.0f
	#elif defined (UGKALG_DOUBLE)
		#define UGKALG_NUMERIC_TYPE double
		#define UGKALG_MAX_VALUE DBL_MAX
		#define GLM_PRECISION_HIGHP_DOUBLE
		#define UGKALG_ONE			1.0f
		#define UGKALG_ZERO			0.0f
	#endif
	#include <glm.hpp>
	#include <gtc/type_ptr.hpp>
	#include <gtc/matrix_transform.hpp>
	//#include <gtc/swizzle.hpp>
	#include <gtc/quaternion.hpp>
	/*#include <gtx/vector_angle.hpp>
	#include <gtx/compatibility.hpp>
	#include <gtx/matrix_operation.hpp>
	#include <gtx/transform.hpp>
	#include <gtx/quaternion.hpp>
	#include <gtx/euler_angles.hpp>
	#include <gtx/norm.hpp>*/

#endif

#include <UGK.h>

namespace UGK
{
	typedef enum {
		TRASLATION,
		ROTATION,
		SCALE,
		MAX_TRANSFORMATION
	} TRANSFORMATION_TYPE;

	typedef enum {
		XDIM,
		YDIM,
		ZDIM,
		WDIM,
		UGKALG_DIMENSIONS
	} SpaceCoords;

	//Do not alter the order of these labels
	typedef enum {
		UGKALG_NO_DIM,
		UGKALG_1D,
		UGKALG_2D,
		UGKALG_3D
	} UGKALG_SpaceDims;

	#ifdef UGKALG_API_DEFAULT
		typedef UGKALG_NUMERIC_TYPE v4[UGKALG_DIMENSIONS];
		/*OpenGL defaults to column major matrices, which means access is of the format mat[col][row].
		In the example, m[2][3] sets the 4th ROW (index 3) of the 3rd COLUMN (index 2) to 2.0. 
		In the example m[1]=vec4(2.0), it is setting an entire column at once (because m[1] refers to column #2, when only ONE index is used it means that COLUMN. 
		m[1] refers to the SECOND COLUMN VECTOR).*/
		typedef UGKALG_NUMERIC_TYPE m4[UGKALG_DIMENSIONS][UGKALG_DIMENSIONS];

	#elif defined UGKALG_API_EIGEN
		// Don't align or application will assert at the beggining. More info:
		// http://eigen.tuxfamily.org/dox-devel/group__TopicStructHavingEigenMembers.html
		typedef f4	Eigen::Matrix<UGKALG_NUMERIC_TYPE, UGKALG_DIMENSIONS, 1, Eigen::DontAlign>
	#elif defined UGKALG_API_GLM

		/*typedef glm::vec4 v4;
		typedef glm::mat4 m4;*/
	//Do not use v2 name because it matches a open gl type
#define V2 glm::vec2
#define v4 glm::vec4 
#define m4 glm::mat4 

	#endif

#ifdef UGKALG_API_DEFAULT
#elif defined UGKALG_API_EIGEN
#elif defined UGKALG_API_GLM
#endif

	class Matrix;
	
	/// A VERY simple vector struct
	class  UGK_API Vector
	{
	public:
		v4 v;

		//Methods
		void Reset(void);
		void Set(UGKALG_NUMERIC_TYPE X, UGKALG_NUMERIC_TYPE Y, UGKALG_NUMERIC_TYPE Z);

		Vector();
		Vector(UGKALG_NUMERIC_TYPE X, UGKALG_NUMERIC_TYPE Y, UGKALG_NUMERIC_TYPE Z);
		Vector(UGKALG_NUMERIC_TYPE X, UGKALG_NUMERIC_TYPE Y, UGKALG_NUMERIC_TYPE Z, UGKALG_NUMERIC_TYPE W);

		void	operator += ( const Vector&);
		void	operator -= ( const Vector&);
		Vector	operator +  ( const Vector&) const;
		Vector	operator -  ( const Vector&) const;
		Vector	operator -	(void) const;
		Vector	operator *	(UGKALG_NUMERIC_TYPE V) const;
		inline void	operator *=	(UGKALG_NUMERIC_TYPE V) { v = v*V; }
		Vector	operator *	(const Vector&) const;
		Vector	operator /	(const float) const;
		

#ifdef UGKALG_API_DEFAULT
		inline float Distance(Vector p2)
		{
			double sum = 0.0,
				   aux;
			for (int i = 0; i < UGKALG_DIMENSIONS; i++)
			{
				aux = v[i] - p2.v[i];
				sum += aux*aux;
			}
			return sqrt(sum);
		};

		inline void Normalize()
		{
			double Module = sqrt(v[XDIM]* v[XDIM]+ v[YDIM]* v[YDIM]+ v[ZDIM]* v[ZDIM]);

			v[XDIM] /= Module;
			v[YDIM] /= Module;
			v[ZDIM] /= Module;
		}

#elif defined UGKALG_API_EIGEN
#elif defined UGKALG_API_GLM
		inline UGKALG_NUMERIC_TYPE * GLVector(){ return glm::value_ptr(v);};
		inline UGKALG_NUMERIC_TYPE Distance(Vector vc) {Vector temp = *this - vc; return glm::dot(temp.v, temp.v); };
		inline Vector Normalize() { Vector aux; aux.v = glm::normalize(v);  return aux; };
#endif
	};	//Class Vector

	/// A VERY simple matrix class
	class  UGK_API Matrix
	{
	public:
		m4 M;

	#ifdef UGKALG_API_DEFAULT
	#elif defined UGKALG_API_EIGEN
		// Don't align or application will assert at the beggining. More info:
		// http://eigen.tuxfamily.org/dox-devel/group__TopicStructHavingEigenMembers.html
		Eigen::M<UGKALG_NUMERIC_TYPE, UGKALG_MATRIX_SIZE, 1, Eigen::DontAlign> M;
	#elif defined UGKALG_API_GLM
		inline float * GLMatrix(){return glm::value_ptr(M);}
		m4  Translate(Vector V)	{ return glm::translate(M, (glm::vec3)V.v); }
		//inline void Lerp(float Init, float End, float Ratio) { lerp(Init, End, Ratio); }
	#endif
		//Methods
		void Reset(void);
		
		Matrix();
		void SetIdentity			();
		void RotScaleReset			();
		void SetGenericTransfMatrix	(TRANSFORMATION_TYPE transf_type, float angle, SpaceCoords axis,float x_value, float y_value, float z_value); ///< Gets a transform matrix depending os the values
		void SetTranslationMatrix	(float x_incr, float y_incr,float z_incr); ///< Gets translation matrix for translate in x, y , z
		void SetRotationMatrix		(float angle, SpaceCoords axis); ///< Gets rotation matrix for rotate "angle" degrees in "axis" axe
		void SetScaleMatrix			(float x_scale, float y_scale,float z_scale ); ///< Gets scale matrix for scale the axis x, y, z		

		void	operator += ( const Matrix&);
		void	operator -= ( const Matrix&);
		Matrix	operator +  ( const Matrix&) const;
		Matrix	operator -  ( const Matrix&) const;
		Matrix	operator -	(void) const;
		Matrix	operator *	(UGKALG_NUMERIC_TYPE V) const;
		
		inline Vector  Matrix::operator * (const v4 v) const
		{
			Vector P;
#ifdef UGKALG_API_DEFAULT
			//Not Implemented
#elif defined(UGKALG_API_EIGEN)
			//Not Implemented
#elif defined(UGKALG_API_GLM)
			P.v = M * v;
#endif
			return P;
		}

		inline Vector	operator *	(const Vector& V) const { return *this * V.v; }
		inline Vector	operator *	(const Vector* V) const { return *this * V->v; };
		Matrix	operator *	(const Matrix& V) const;

	};	//Class Matrix

	/// A VERY simple quaternion class
	class  UGK_API Quaternion: public Matrix
	{
	public:

#ifdef UGKALG_API_DEFAULT
#elif defined UGKALG_API_EIGEN
#elif defined UGKALG_API_GLM
#endif
		//Methods
		
	};	//Class Quaternion

// Vertex struct to make code easier to read in places
typedef Vector Vertex;

inline UGKALG_NUMERIC_TYPE UGKALG_Min(UGKALG_NUMERIC_TYPE a, UGKALG_NUMERIC_TYPE b, UGKALG_NUMERIC_TYPE c)	{ if (a<b){ if (a < c) return a; else return c; } else if (b < c) return b; else return c; }
inline UGKALG_NUMERIC_TYPE UGKALG_Min(Vector V)																{ if (V.v[XDIM] < V.v[YDIM]){ if (V.v[XDIM] < V.v[ZDIM]) return V.v[XDIM]; else return V.v[ZDIM]; } else if (V.v[YDIM] < V.v[ZDIM]) return V.v[YDIM]; else return V.v[ZDIM]; }
inline UGKALG_NUMERIC_TYPE UGKALG_Min(UGKALG_NUMERIC_TYPE a, UGKALG_NUMERIC_TYPE b)							{ if (a<b) return a; else return b; }

UGK_API Vector Bezier(Vector *p, int n,UGKALG_NUMERIC_TYPE mu);	///<BEZIER CURVE interpolator

union UGKALG_SimpleVector {
	struct {
		float x;
		float y;
		float z;
		float w;
	};
	v4 v;

	UGKALG_SimpleVector() { x = y = z = w = 0.0; }
	UGKALG_SimpleVector(v4 v1) { v = v1; }
	UGKALG_SimpleVector(UGKALG_NUMERIC_TYPE x1, UGKALG_NUMERIC_TYPE y1, UGKALG_NUMERIC_TYPE z1) { x = x1; y = y1; z = z1; }
	UGKALG_SimpleVector operator * (UGKALG_NUMERIC_TYPE a) { return UGKALG_SimpleVector(v*a); }
	void operator *= (UGKALG_NUMERIC_TYPE a) { v*=a; }
	void operator *= (UGKALG_SimpleVector a) { v *= a.v; }
	void operator -= (UGKALG_SimpleVector a) { v -= a.v; }
	void operator += (UGKALG_SimpleVector a) { v += a.v; }
};

} //namespace UGK

#define NeutralModelView() SetIdentity()

#endif