/*	Class Quad Tree for collision detection support

*	Prefix: QT_

	@author Hector Martinez Cebrian
	@version 2013-05-08
*/

#ifndef QT_QUADTREE
#define QT_QUADTREE

#include <UGK.h>
#include <vector>

namespace UGK
{
	class CCharacter;
	typedef std::vector<CCharacter*> CharacterList;
	//typedef std::vector <CCharacter*>	CHAR_CHARACTER_VECTOR;

	typedef enum
	{
		QT_NE,
		QT_NW,
		QT_SE,
		QT_SW,
		QT_MAX_ORIENTATION
	}QT_ORIENTATION;

	class UGK_API Quadtree
	{
		//static int maxLevel; I comment this line and add a maxLevel in each quadtree node for more flexibility. 
	private:

		float			x;
		float			y;
		float			width;
		float			height;
		int				level;
		int				maxLevel;
		int				cantidad;
		CharacterList	characters;

		float	minX,minY,maxX,maxY;

		Quadtree* parent;

		Quadtree* QTSons[QT_MAX_ORIENTATION];

		bool				Contains(Quadtree *child, CCharacter *character);
		bool				ContainsBigCharacter(Quadtree *child, CCharacter *character);
		bool				BeforeContains(Quadtree *child, CCharacter *character);
		bool				Contains(Quadtree *child, float x, float y, float radius);

	public:
	
							Quadtree(float _x, float _y, float _width, float _height, int _level, int _maxLevel);
							~Quadtree();
		void				AddCharacter(CCharacter *character);
		bool				RemoveCharacter(CCharacter *character);
		void				AddBigCharacter(CCharacter *character);
		void				RemoveBigCharacter(CCharacter *character);
		bool				UpdateCharacter(CCharacter *character);
		CharacterList		GetNearestObjectsTo(float _x, float _y, float radius);
		void				Clear();
		void				Render();
		void				Purge();
	};
}//Name space UGK

#endif