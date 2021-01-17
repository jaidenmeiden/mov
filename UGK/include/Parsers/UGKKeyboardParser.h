/*	Class that loads the values of a given level of game

Prefix CKbP_: Class Keyboard Parser


@version 2016
*/

#include <UGKHTMLParser.h>
#include <UGKKeyboard.h>

typedef enum {
	LOG_KEYBOARD_PARSER_ERROR_RESOURCE,
	LOG_KEYBOARD_KEYBOARD,
	LOG_KEYBOARD_PARSER_TAG,	
	LOG_KEYBOARD_MAX_LOGMSG
} CKyP_LogMsg;

/**
* It defines the types of labels for the analysis
* @param enum CLaP_TagType which lists the type of tags that the parser will match during the analysis
*/
typedef enum {
	K_ACTION = MAXTAGS_D,
	K_KEY,
	K_LANGUAGE,
	K_NEXUS,
	K_PERIOD,
	K_MAXTAGS
} CKyP_Key_TagType;

/**
* CKeyboardParser class is defined with derivation or inheritance of the class ILiteHTMLReaderEvents
* Where is loaded default values at the beginning of the game
*/
namespace UGK
{
	class UGK_API  CKeyboardParser : public CHTMLParser
	{

	private:
		void BeginParse(DWORD dwAppData, bool &bAbort); //Inicio del analizador
		void StartTag(CLiteHTMLTag *pTag, DWORD dwAppData, bool &bAbort); //Comienzo de las etiquetas
		void EndTag(CLiteHTMLTag *pTag, DWORD dwAppData, bool &bAbort); //Terminacion de las etiquetas
		void Characters(const CP_StringType &rText, DWORD dwAppData, bool &bAbort); //Caracteres
		void Comment(const CP_StringType &rComment, DWORD dwAppData, bool &bAbort); //Comentarios de las etiquetas
		void EndParse(DWORD dwAppData, bool bIsAborted); //Fin del Analizador

		/// This method save the nexus associated to one key
		void SaveNexus(CP_StringType, CP_StringType, int);

		CKeyboard	*Keyboard;
		UGKS_String ISO639;	///< Code representing the language used by default by the keyboeard if neccesary. Use ISO 639 format

	public:

		CKeyboardParser();
		CKeyboardParser(CP_StringType Version, CP_StringType Titulo);

		inline void SetKeyboard(CKeyboard *CurrentKeyboard)	{ Keyboard = CurrentKeyboard; };
	};
}