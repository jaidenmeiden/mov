/**	Definition of the class Score

*Prefix: UGKCSC_

*	@author Ramon Molla
*	@author Nuria Martinez
*	@version 2012-06
*/

#ifndef CSC_SCORE
#define CSC_SCORE

#include <UGKString.h>

namespace UGK
{
	class UGK_API CScore
	{
	protected:
		//Atributes
		UGKS_String name; ///Player name
		int points;	///Player score points
	
	public:

		//Methods
		void Init();
    
		///Constructor of the class
		CScore	(){Init();};

		///Destructor of the class
		~CScore	();

		///Returns the name of player
		inline UGKS_String GetName() { return name; }

		///Returns the points of score
		inline int GetPoints() {  return points; }

		///Returns the name of the player score
		inline void SetName(UGKS_String n) { name = n; }

		///Sets the points of score
		inline void SetPoints(int p) { points = p; }	
	};
}	//Namespace

#endif