/** Cpp: Contains functions for work with Class ISO639
*	@file ISO639.cpp
*	@author Charco Aguirre, Jorge
*	@version 1.0.0
*	@date 2016-01-21
*/

#include <map>
#include <iostream>
#include <fstream>
#include <UGKLanguages_ISO639.h>

using namespace UGK;

/* -------------------------------------------------------
 Path of all code of language ISO639 and language for game 
--------------------------------------------------------*/
#define PATH_ISO639 ".\\Documentación\\ISO639.txt"	
#define PATH_LANGUAGE "\\languages\\*" 

/** Function LoadISO()
*	Load the all languaje code that is in the folder and save it in a variable- type MAP 
*	The function returns a boolean value that lets you know if the language file has been loaded
*	Not receives input parameters, returns a boolean value as output
*/

bool ISO639::loadISO()
{
	ifstream file;
	string c;
	file.open(PATH_ISO639);
	if (file.is_open())
	{	while (file)
		{	getline(file, c);
			int x=c.find("\t");							//Find tab for get position of code ISO639
			string code = c.substr(0, x);				//Get code unique ISO639-2
			string name = c.substr(x+1,c.size()-x);		//Get name associated with code unique
			ISO639::code_iso_tmp[code] = name;			//Create a MAP that contain all code unique + name language
		}		
		ISO639::Ready=true;
	}
	else
	{	cout << "Error: No file about ISO639 configuration" << endl;
		ISO639::Ready = false;
	}		
	file.close();	
	return ISO639::Ready;
}

/*-----------------------------
  Convert a string to lowercase
-----------------------------*/
string convertLower(string &cadena)
{
	for (int i = 0; cadena[i]; i++)
		cadena[i] =
		tolower(cadena[i]);
	return cadena;
}

/*-----------------------------
Convert a string to uppercase
-----------------------------*/
string convertUpper(string cadena)
{
	for (int i = 0; cadena[i]; i++)
		cadena[i] =
		toupper(cadena[i]);
	return cadena;
}

/** Function readDirectory()
*	Seeking the folder where all the files of language and then go around the folder for the file extension
*	The function returns a boolean value that lets you know if the language file has been loaded
*	Not receives input parameters, but saved in a private variable the name of the language found in the folder and ISO CODE
*/

/*----------------------------------------------
Read of Directory for obtains file of languages
----------------------------------------------*/
void ISO639::readDirectory()
{
	int code = -1;
	WIN32_FIND_DATA findFileData;
	HANDLE          hFind;
	char dir[MAX_PATH];
	char path[MAX_PATH] = PATH_LANGUAGE;
	DWORD cchCurDir = MAX_PATH;

	GetCurrentDirectoryA(cchCurDir, dir);
	strcat_s(dir, _countof(dir), path);				// Join path + folder that contain file of configuration

	/*---------------------------------------------------------
	Convert PATH of directory to LPCWSTR for read de folder
	--------------------------------------------------------*/
	int c = MultiByteToWideChar(0, 0, dir, -1, NULL, 0);
	wchar_t *tmp = new wchar_t[c];
	MultiByteToWideChar(0, 0, dir, -1, tmp, c);
	LPCWSTR dir1 = tmp;
	/*---------------------------------------
	  Get file of the folder language	
	-----------------------------------------*/
	hFind = FindFirstFile(dir1, &findFileData);		
	if (hFind == INVALID_HANDLE_VALUE)
		std::cout << "Ruta incorrecta";
	else
	{	// List all files of folder		
		while (FindNextFile(hFind, &findFileData) != 0)
		{
			/* ----------------------------------------
			Get name of file and convert a type string
			-----------------------------------------*/
			std::wstring tmp(findFileData.cFileName);
			UGKS_String file(tmp.begin(), tmp.end());
			//---------------------------------------			
			int pos = file.find(".");
			string extension = file.substr(pos + 1, file.size() - pos);	//Get of extension of language - default is html	
			
			/*!< Only for files with HTML extension, the name is obtained 
			 *   for comparison with the CODE ISO, stored in private variable within the class
			 */
			if (extension == "html")
			{
				string name = convertLower(file.substr(0, pos));		//Get name of language inside folder Languages - Code ISO639				
				auto search = ISO639::code_iso_tmp.find(name);			//Find ISO of file Language inside global variable
				if (search != ISO639::code_iso_tmp.end())
				{
					code = code + 1;									//Code of map for Languages obtains
					string item = "(" + convertUpper(search->first) + ") - " + convertUpper(search->second);
					ISO639::combo_language[code] = item;				//Create a MAP that contain all code unique + name language
				}
			}
		}
	}
}
