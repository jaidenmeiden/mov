/**	Definitions of the default labels for all parsers
*	These are the default tags that are always present for any parser 

*	Prefix DHTML_: Default HTML Labels for all Parsers

*	@file UGKDefaultHTMLLabels.h
*	@author Ramón Mollá
*	@version 2014-10
*/

#ifndef DHTML_INITIALIZED //Se borra la macro inicializacion
#define DHTML_INITIALIZED //Se define la macro inicializacion

/**   
   It defines the default types of labels that can match the scanner during the scan that exist in the game
*/
typedef enum {
	NIL_D,		//This tag is for management purpouses only. There is no correspondence to any string label in the HTML file
	BODY_D,		//HTML tag
	HEAD_D,		//HTML tag
	HTML_D,		//HTML tag
	TITLE_D,	//HTML tag
	TYPE_D,
	VERSION_D,
	MAXTAGS_D		//This tag is for management purpouses only. There is no correspondence to any string label in the HTML file
} DHTML_TagType;

typedef char *DHTML_TagsArrayType [MAXTAGS_D];

extern	DHTML_TagsArrayType DHTML_TagsArray;

#endif