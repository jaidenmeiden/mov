/**	General HTML Reader class that manages general functions for starting and verifying the parsing done by the UGKHTMLParser

*	Prefix CR_: Class Reader

*	@author Ramon Molla
*	@version 2014-11
*/

#ifndef CR_READER
#define CR_READER

#include <UGKHTMLParser.h>

using namespace std;

#ifndef FSTREAM_INITIALIZED
#define FSTREAM_INITIALIZED
#include <fstream>
#endif

/**	
*	CHTMLReader

*	@author Ramon Molla
*	@version 2014-11
*/

namespace UGK
{
	class UGK_API CHTMLReader : public CLiteHTMLReader
	{
	protected:

		CFile		HTMLFile;		//File to parser
		UGKS_String	HTMLFileName;

		//Head of the file general attributes
		UGKS_String		Title;		///< Program TITLE
		UGKS_String		Version;	///< Program VERSION

		void ParseFile();

	public:

		CHTMLReader		(){};
		~CHTMLReader	(){};

		inline void	SetFileName(UGKS_String FileName) { HTMLFileName = FileName; }

		/**
		*	\fn void ParseFile (char * FileName)
		*	Opens a file and parses it depending on the parser loaded before invoking this method
		*	\param[in]  FileName The name of the file to parse
		*/
		inline void ParseFile(UGKS_String FileName)
		{
			SetFileName(FileName);
			ParseFile();
		}

		/**
		*	\fn	void ParseFile(UGKS_String FileName, UGKS_String Folder, UGKS_String Title, UGKS_String Version, CHTMLParser *Parser)
		*	Opens a file and parses it depending on the parser. Title and Version are implicit
		*	\param[in]  FileName The name of the file to parse
		*	\param[in]  Folder The name of the folder where resides file to parse
		*	\param[in]  Parser The interpreter of the content of the file
		*/
		void ParseFile(UGKS_String FileName, UGKS_String Folder, CHTMLParser *Parser);

		/**
		*	\fn	void ParseFile(UGKS_String FileName, UGKS_String Folder, UGKS_String Title, UGKS_String Version, CHTMLParser *Parser)
		*	Opens a file and parses it depending on the parser
		*	\param[in]  FileName The name of the file to parse
		*	\param[in]  Folder The name of the folder where resides file to parse
		*	\param[in]  Title The name of the program file to parse refers to
		*	\param[in]  Version The version number of program the file to parse refers to
		*	\param[in]  Parser The interpreter of the content of the file
		*/
		inline void ParseFile(UGKS_String FileName, UGKS_String Folder, UGKS_String Tit, UGKS_String Vers, CHTMLParser *Parser)
		{
			SetVersion	(Vers);
			SetTitle	(Tit);
			ParseFile	(FileName, Folder, Parser);
		}

		/**
		*	\fn inline void SetVersion (CP_StringType V)
		*	Sets the name of the version to find inside of the parsed file
		*	\param[in] Text Version of the program to parse
		*/
		inline void SetVersion(UGKS_String V) { Version = V; }///< Updates the protected attribute "Version". The version number of the videogame that appears inside the HTML file

		/**
		*	\fn inline void SetTitle(CP_StringType T)
		*	Sets the name of the title to find inside of the parsed file
		*	\param[in] Text Version of the program to parse
		*/
		inline void SetTitle(UGKS_String  T)	{ Title = T; } ///< Updates protected attribute "Title". The name of the videogame that appears inside the HTML file

		/**
		*	\fn inline CP_StringType GetVersion()
		*	Gets the name of the version of the file to parse
		*	Retrieves the protected attribute "Version".The version number of the videogame that appears inside the HTML file
		*/

		inline UGKS_String GetVersion(){ return Version; }

		/**
		*	\fn CP_StringType GetTitle();
		*	Gets the name of the title of the file to parse
		*	Retrieves the protected attribute "Title". The name of the videogame that appears inside the HTML file
		*/
		inline UGKS_String GetTitle(){ return Title; }
	};
}
#endif
