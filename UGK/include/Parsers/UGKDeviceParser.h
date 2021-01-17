
/*	Class that loads the values of devices of game 

	Prefix CDevP_: Class Devices Parser

	@author Sonia Cardenas
	@author David Peris
	@version 2015-05-06
	@Refactored by Ramón Mollá ot change to Unicode
*/

#include <UGKHTMLParser.h>
#include <UGKDeviceManager.h>

#ifndef FSTREAM_INITIALIZED //Se borra la macro inicializacion
#define FSTREAM_INITIALIZED //Se define la macro inicializacion
#include <fstream>
#endif

#define CDevP_MAXSTACK	  16	//Maximun deepness of the stack

/**   
   It defines the types of labels that can match the scanner during the scan that exist in the game
   @param enum CDevP_TagType which lists the types of labels to be analyzed
*/
typedef enum {
	 BUTTONS_D = MAXTAGS_D,
	 CONFIG_D,
	 DEVICE_D,
	 ID_D,
	 NAME_D,
	 RESOLUTION_D,
	 SENSITIVITY_D,
	 VIBRATION_D,
	 X_D,
	 Y_D,
	 MAXTAGS_DEV		//This tag is for management purpouses only. There is no correspondence to any string label in the HTML file
} CDevP_TagType;

/* Class that loads the values the device using game
*/
/**   
   Reading class is defined with derivation Level or class inheritance ILiteHTMLReaderEvents    
   Where is the constructor and destructor in addition to starting the analysis file
   @param CE_EXPLOSION_TYPE subType predefined variable for the types of explosion
*/
namespace UGK
{	
	class UGK_API CDeviceParser : public CHTMLParser
	{
		void BeginParse	(DWORD dwAppData, bool &bAbort); //Parsing begining
		void StartTag	(CLiteHTMLTag *pTag, DWORD dwAppData, bool &bAbort); //Initial Token
		void EndTag		(CLiteHTMLTag *pTag, DWORD dwAppData, bool &bAbort); //Ending tag
		void Characters	(const UGKS_String &rText, DWORD dwAppData, bool &bAbort); //Text containing information
		void Comment	(const UGKS_String &rComment, DWORD dwAppData, bool &bAbort); //Comments
		void EndParse	(DWORD dwAppData, bool bIsAborted); //Fin de  analisis

		CDeviceManager	*DeviceManager;
		CHardware		*HW;
		CHW_HARDWARE_TYPE	ActiveHw;	///<The Hardware wich is active in the list of devices.

	public:

		//Constructor and destructor
		CDeviceParser();

		inline void SetDeviceManager(CDeviceManager *DM) { DeviceManager = DM; }
	};
}
