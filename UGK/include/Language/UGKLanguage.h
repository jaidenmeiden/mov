/*	Definition of the class Language

	Prephix = LANG_

	@author Ramon Molla
	@version 2011-11
*/

#ifndef LANG_LANGUAGE ///if macro LANG_LANGUAGE is not defined before in the game...
#define LANG_LANGUAGE ///macro LANG_LANGUAGE is defined

#ifndef VECTOR_LOADED
#define VECTOR_LOADED
#include <vector>
#endif

#include <UGKString.h>

/**   
	* It defines the types of errors for the language skills
    * @param enum lang_errors which: lists the types of errors of language skills
*/
typedef enum {
	LANG_NO_ERROR,		///No error has happened
	LANG_REPEATED,		///There is just an available language with the same name as the given one
	LANG_INEXISTENT,	///There is no langugae with the given name
	LANG_NO_LANGUAGE,	///There are no languages at all in the list of languages
	LANG_MAX_ERRORS		///For error management only
} LANG_ERRORS;

/**   
	* Language class is defined
    * Where you define the language file loaded from the language directory
    * The same containing text for the labels in the game depending on which option is chosen
    * In addition to the errors generated when loading
*/

namespace UGK
{
	class UGK_API CLanguage
	{
	protected:
		UGKS_String File,	///<File name where the language information resides. Typically "ISO 639-2 code"+".html". e.g. spa.html or eng.html
					Folder,	///<Folder where the language information file resides
					Name,	///<Name of the language in english
					ISO639,	///<ISO 639-2 three chars code identifying the languge used. e.g. "spa", "eng"
					Version,///<Version of the program to match inside the file
					Title;	///<Title of the program to match inside the file
	
		bool	Ready;
		std::vector<UGKS_String>	TextResource;	///<Array that holds all possible messages available for the log files, msg boxes and HCI in general for this given language.

	public:

		//Methods
		CLanguage() {
			Ready = false; File.clear(); Name.clear(); ISO639.clear(); SetSize(1);}
		
		//Setters
		inline void SetFile(UGKS_String f)		{ File = f; }	///<Sets the language file f to load
		inline void SetFolder(UGKS_String f)	{ Folder = f; }	///<Sets the folder f where the language files are
		inline void SetName(UGKS_String n)		{ Name = n; }	///<Sets the name n of the language
		inline void SetCode(UGKS_String c)		{ ISO639 = c; }	///<Sets the code c of the language
		inline void SetVersion(UGKS_String v)	{ Version = v; }///<Sets the version v of the language
		inline void SetTitle(UGKS_String t)		{ Title = t; }	///<Sets the title t of the language
		inline void	SetText(int id, UGKS_String text)	{ TextResource[id] = text; }
		inline void SetSize(unsigned int S)		{ TextResource.resize(S); }

		//Getters
		inline UGKS_String	GetFile() { return File; }
		inline UGKS_String	GetName() { return Name; }
		inline UGKS_String	GetCode() { return ISO639; }
		inline UGKS_String	GetText(const unsigned int TR)	{return TextResource[TR];}
		inline int			GetSize() { return TextResource.size(); }

		bool				Load(UGKS_String File, UGKS_String Folder, UGKS_String title, UGKS_String version);
		inline bool			IsReady () {return Ready;};

		inline std::vector<UGKS_String> getTextResource(){return TextResource;}
	};
}
#endif
