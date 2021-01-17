/*	Definition of the class Laguage
  General class to manage the current language

	Prefix: LANG_
	@author Ramon Molla
	@version 2014-05
*/

#include <UGKLanguageParser.h>
#include <UGKHTMLReader.h>

bool UGK::CLanguage::Load(UGKS_String File, UGKS_String Folder, UGKS_String title, UGKS_String version)
{
	//HTML Reader
	CLanguageReader	LanguageReader(version, title);//The parser used to understand the contents of the language file
	CHTMLReader		HTMLReader;		//The real HTML reader

	//Starting language load

	LanguageReader.SetLanguage	(this);
	HTMLReader.ParseFile(File, Folder, title, version, &LanguageReader);
	return true;
}