/**	Definition of the sound engine

*	Prefix: UGKSNDENG_

*	@author Leopoldo Pla 
*	@version 2015-01
*   @NewVersion Carlos Pérez 2016-01-27 - Added errors and fx modes
*/

#ifndef UGKSNDENG_SOUNDENGINE
#define UGKSNDENG_SOUNDENGINE

// Be careful, use only one API every time
// The value in the definition is used to correctly identify the definition, if you
// remove the value VS generates error c1017
//#define UGKSND_FMOD375 1 // bugs, set to SDL to avoid compilation problems (sjimenez)
//#define UGKSND_FMODEx 2
//#define UGKSND_FMODStudio 3
//#define UGKSND_OAL 4
#define UGKSND_SDL 5

//Different sampling frequencies
#define UGKSNDENG_FREQ_CD4	11025
#define UGKSNDENG_FREQ_CD2	22050
#define UGKSNDENG_FREQ_CD	44100
#define UGKSNDENG_FREQ_DV	48000
#define UGKSNDENG_FREQ_DV	48000
#define UGKSNDENG_FREQ_2CD	88200
#define UGKSNDENG_FREQ_DVD	96000
#define UGKSNDENG_FREQ_BR	192000
#define UGKSNDENG_FREQ_DXD	352800

//Different output channel configurations
typedef enum
{
	UGKSNDENG_MONNO,
	UGKSNDENG_STEREO,
	UGKSNDENG_QUADRAPHONIC,
	UGKSNDENG_SURROUND51,
	UGKSNDENG_SURROUND71,
	UGKSNDENG_MAX_OUTPUT_CHANNELS
} UGKSNDENG_OUTPUT_CHANNELS;

//Stencil to replicate where ever needed
#ifdef UGKSND_FMOD375
#elif defined(UGKSND_FMODEx)
#elif defined(UGKSND_FMODStudio)
#elif defined(UGKSND_OAL)
#elif defined(UGKSND_SDL)
#endif

#ifdef UGKSND_FMOD375
	#include <fmod.h>
	enum SND_ERRORS 
	{
		//Matching UGK errors to fmod errors
		SND_ERR_NONE,             /* No errors */
		SND_ERR_BUSY,             /* Cannot call this command after FSOUND_Init.  Call FSOUND_Close first. */
		SND_ERR_UNINITIALIZED,    /* This command failed because FSOUND_Init or FSOUND_SetOutput was not called */
		SND_ERR_INIT,             /* Error initializing output device. */
		SND_ERR_ALLOCATED,        /* Error initializing output device, but more specifically, the output device is already in use and cannot be reused. */
		SND_ERR_PLAY,             /* Playing the sound failed. */
		SND_ERR_OUTPUT_FORMAT,    /* Soundcard does not support the features needed for this soundsystem (16bit stereo output) */
		SND_ERR_COOPERATIVELEVEL, /* Error setting cooperative level for hardware. */
		SND_ERR_CREATEBUFFER,     /* Error creating hardware sound buffer. */
		SND_ERR_FILE_NOTFOUND,    /* File not found */
		SND_ERR_FILE_FORMAT,      /* Unknown file format */
		SND_ERR_FILE_BAD,         /* Error loading file */
		SND_ERR_MEMORY,           /* Not enough memory or resources */
		SND_ERR_VERSION,          /* The version number of this file format is not supported */
		SND_ERR_INVALID_PARAM,    /* An invalid parameter was passed to this function */
		SND_ERR_NO_EAX,           /* Tried to use an EAX command on a non EAX enabled channel or output. */
		SND_ERR_CHANNEL_ALLOC,    /* Failed to allocate a new channel */
		SND_ERR_RECORD,           /* Recording is not supported on this machine */
		SND_ERR_MEDIAPLAYER,      /* Windows Media Player not installed so cannot play wma or use internet streaming. */
		SND_ERR_CDDEVICE,         /* An error occured trying to open the specified CD device */

		//UGK API Errors
		SND_ERR_UNKNOWN,          /* Error unknown */
		SND_ERR_MAX				  /* For accounting purpouses only. This error has to be always the last one*/
	};

	enum SND_FX_MODES
	{
		SND_FX_CHORUS,
		SND_FX_COMPRESSOR,
		SND_FX_DISTORTION,
		SND_FX_ECHO,
		SND_FX_FLANGER,
		SND_FX_GARGLE,
		SND_FX_I3DL2REVERB,
		SND_FX_PARAMEQ,
		SND_FX_WAVES_REVERB,

		SND_FX_MAX
	};

#elif defined(UGKSND_FMODEx)
#elif defined(UGKSND_FMODStudio)
#elif defined(UGKSND_OAL)
	#include <OpenAL/AL/al.h>
	#include <OpenAL/AL/alc.h>
	#include "OpenAL/vorbis/vorbisfile.h"
#elif defined(UGKSND_SDL)
	#include <SDL.h>
	#include <SDL_mixer.h>
	
enum SND_ERRORS
{
	SND_ERR_NONE,             /* No errors */
	SND_ERR_MEMORY,
	SND_EFREAD,
	SND_EFWRITE,
	SND_EFSEEK,
	SND_UNSUPPORTED,

	//UGK API Errors
	SND_ERR_UNKNOWN,          /* Error unknown */
	SND_ERR_MAX
};

#endif

#endif
