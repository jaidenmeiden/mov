#ifndef CBBPOINT
#define CBBPOINT

#include <UGK.h>

namespace UGK
{
	class CCharacter;

	class UGK_API CBBPoint
	{
	public:
		CBBPoint();
		CBBPoint(int Position, float Value, CCharacter *Character);
		/// Position index inside the dimension array. For management purpouses
		int			Position;
		/// Axis Aligned Bounding Box in absolute coordinates. It may be minimun or maximun values for the AABB at that dimension
		float		Value;
		/// Character that has this limit
		CCharacter	*Character;
	};

}

#endif