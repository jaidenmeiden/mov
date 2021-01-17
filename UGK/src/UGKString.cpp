/**	Definition of the UGKS_String class

*	Prefix: UGKS_

*	@author Ramon Molla
*	@version 2016-02
*/

#include <UGKString.h>
#include <atlbase.h>
#include <atlconv.h>

/**
* @fn UGKS_String UGKS_GenerateFullPathName(UGKS_String  &Result, UGKS_String  Path, UGKS_String  Name)
* Gets the absolute path to the filename.
* @param[in] Name Name of the file in the path.
* @param[in] Path Path where the file to load exists
* @param[out] Result The string containing the whole path from the root of the disk
* @return Absolute path to the filename
*/
UGKS_String UGKS_GenerateFullPathName(UGKS_String  &Result, UGKS_String  Path, UGKS_String  Name)
{
	if (Name.empty())
		Result.clear();
	else if (Path.empty())
			Result = Name;
		 else
		 {
			#ifdef	UGKOS_WINDOWS
			 TCHAR buffer[512];
			 GetCurrentDirectory(512, buffer);
			 Result = CT2A(buffer);
			#elif	defined(UGKOS_LINUX)
			#elif	defined(UGKOS_OSX)
			#elif	defined(UGKOS_ANDROID)
			#endif

			Result += UGKOS_DIRECTORY_SEPARATOR;
			Result += Path;
			Result += UGKOS_DIRECTORY_SEPARATOR;
			Result += Name;
		 }
	return Result;
}

/**
* @fn UGKS_String UGKS_RelativeFullPathName(UGKS_String  &Result, UGKS_String  Path, UGKS_String  Name)
* Gets the relative path to the filename.
* @param[in] Name Name of the file in the path.
* @param[in] Path Path where the file to load exists
* @param[out] Result The string containing the whole path from the root of the disk
* @return Relative path to the filename
*/
UGKS_String UGKS_RelativeFullPathName(UGKS_String  &Result, UGKS_String  Path, UGKS_String  Name)
{
	if (Name.empty())
		return Name;

	Result = UGKOS_THIS_DIRECTORY;

	if (!Path.empty())
	{
		Result += Path;
		Result += UGKOS_DIRECTORY_SEPARATOR;
	}
	Result += Name;
	return Result;
}