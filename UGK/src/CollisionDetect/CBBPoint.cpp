#include <CBBPoint.h>

using namespace UGK;

CBBPoint::CBBPoint(){

}

CBBPoint::CBBPoint(int Position, float Value, CCharacter *Character){
	this->Position= Position;
	this->Value= Value;
	this->Character= Character;
}