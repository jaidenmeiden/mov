/** Header that contain load ISO of all language for game
*	@file Class ISO639 	
*	@author Charco Aguirre, Jorge
*	@version 1.0.0
*	@date 2016-01-21
*/

#ifndef Languages_ISO639_H
#define Languages_ISO639_H
#include <map>
#include <UGKString.h>

using namespace std;

//space for storing an ISO 639 language identifier or the html file associated for it
#define LANG_LONG_STRING 16		

/**
* Language class is defined and load of file of ISO639 
* This file contain all language and you can read directory for obtain respective code of language
*/

namespace UGK
{
	class UGK_API ISO639
	{
	private:
		/*-------------------------------------------------------
		Private Variable that contain all language of file ISO639
		-------------------------------------------------------*/
		bool	Ready;					
		map<UGKS_String, UGKS_String> code_iso_tmp;
		/*--------------------------------------------
		Variable local, contain language for combo-box
		-------------------------------------------*/
		map<int, UGKS_String> combo_language;		

	public:
		/*---------------------------------------------
		Function for load, read of ISO639 and Languages
		---------------------------------------------*/
		ISO639(){ Ready = false; }
		bool loadISO();		
		void readDirectory();
		map<UGKS_String, UGKS_String> getISO639(){ return code_iso_tmp; }
		map<int, UGKS_String> getLANGUAGECOMBO(){ return combo_language; }		
	};
}
#endif;