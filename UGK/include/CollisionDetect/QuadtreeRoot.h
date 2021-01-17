/*	Class that creates a quadtree root

	@file QuadTreeRoot.h
	@author Hector Martinez Cebrian
	@version 2013-05-08
	Refactored by Ramón Mollá
	@version 2016-06-08
*/
#ifndef QTR_QUADTREEROOT
#define QTR_QUADTREEROOT
#include <Quadtree.h>

/**

*/
namespace UGK
{
	class UGK_API QuadtreeRoot
	{
	protected:

		std::vector<int>	 CharacterAmount;
		Quadtree* quadtree;

	public:

		QuadtreeRoot() { QuadtreeRoot(0); }
		QuadtreeRoot(unsigned int CharacterTypes){ Init(CharacterTypes); };

		inline void Init(unsigned int CharacterTypes)
		{
			CharacterAmount.resize(CharacterTypes);
			for (unsigned int i = 0; i < CharacterTypes; i++) CharacterAmount[i] = 0;
			quadtree = NULL;
		}

		inline void setQuadtree(float x, float y, float width, float height, int maxLevel)
		{
			if (NULL != quadtree)
				delete quadtree;
			quadtree = new Quadtree(x, y, width, height, 1, maxLevel);
		}
		inline bool RemoveCharacter	(CCharacter *C) { return quadtree->RemoveCharacter(C); }
		inline bool	UpdateCharacter	(CCharacter *C) { return quadtree->UpdateCharacter(C); }
		inline void AddCharacter	(CCharacter *C) { quadtree->AddCharacter(C); }

		inline CharacterList		GetNearestObjectsTo(float x, float y, float radius)
		{return quadtree->GetNearestObjectsTo(x, y, radius);}

		inline void	AddBigCharacter(CCharacter *C) { quadtree->AddBigCharacter(C); };	

		inline void Render(){ quadtree->Render(); }
		inline void Clear(){ quadtree->Clear(); }

		inline void IncCharAmount(int Type){ CharacterAmount[Type]++; }
		inline void DecCharAmount(int Type){ CharacterAmount[Type]--; }
	};
}
#endif