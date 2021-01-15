/**
*	Defines the class of a boometer control that draws a level of some magnitude

*	@author 
*	@version 2014-01
*/

#ifndef BOOMETER_H
#define BOOMETER_H
#include <UGKCharacter.h>
#include <TexturesManager.h>

using namespace UGK;

class CBoometer: public CCharacter
 {
 public:
	 ///Constructor of the class
	 CBoometer(UGK::Vector, float, float, CHAR_TEXTUREID, CTexturesManager * TextureMngr);

	 ///Destructor of the class
	 ~CBoometer() {};

	 ///Renders the boometer with the level indicated, should be Radius level/maxLevel
	 void Render(float);


 };
#endif