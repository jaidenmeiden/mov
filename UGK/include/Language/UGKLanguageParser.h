/*	Class that loads the values of a given level of game 

	Prefix CLaP_: Class Level Parser

	@author Ramon Molla
	@version 2007-09-11
*/

#include <UGKHTMLParser.h>
#include <UGKLanguage.h>

typedef enum {
	LOG_LANGUAGE_PARSER_ERROR_RESOURCE,
	LOG_LANGUAGE_LANGUAGE,
	LOG_LANGUAGE_MAX_LOGMSG
} CLaP_LogMsg;

/**   
	* It defines the types of labels for the analysis
    * @param enum CLaP_TagType which lists the type of tags that the parser will match during the analysis
*/
typedef enum {
	L_CONTENT = MAXTAGS_D,
	L_ID,
	L_LANGUAGE,
	L_RESOURCE,
	L_MAXTAGS
} CLaP_Lan_TagType;

/**   
	* CLanguageReader class is defined with derivation or inheritance of the class ILiteHTMLReaderEvents
    * Where is loaded default values ??at the beginning of each level in the game
*/
namespace UGK
{
	class UGK_API  CLanguageReader : public CHTMLParser
	{

	private:
		void BeginParse	(DWORD dwAppData, bool &bAbort); //Inicio del analisador
		void StartTag	(CLiteHTMLTag *pTag, DWORD dwAppData, bool &bAbort); //Comienzo de las etiquetas
		void EndTag		(CLiteHTMLTag *pTag, DWORD dwAppData, bool &bAbort); //terminacion de las etiquetas
		void Characters	(const CP_StringType &rText, DWORD dwAppData, bool &bAbort); //Caracteres
		void Comment	(const CP_StringType &rComment, DWORD dwAppData, bool &bAbort); //Comentarios de las etiquetas
		void EndParse	(DWORD dwAppData, bool bIsAborted); //Fin del Analisador

		void SaveResource();

		CLanguage *Language;

	public:

		//CLanguageReader	();
		CLanguageReader(CP_StringType Version, CP_StringType Titulo);

		inline void SetLanguage	(CLanguage *CurrentLanguage)	{ Language = CurrentLanguage; };
	};
}