/*	Definition of the class Sound System

	Prefix: UGKCSNDS_

	@author Ramon Molla
	@version 2014-05

*/

#include <UGKSoundSystem.h>

#ifdef UGKSND_FMOD375
	#include <stdio.h> //Required because of the NULL definition
#endif

#ifdef UGKSND_FMOD375
#elif defined(UGKSND_FMODEx)
#elif defined(UGKSND_OAL)
#elif defined(UGKSND_SDL)
#endif

using namespace UGK;

void CSoundSystem::Init (void)
{
	#ifdef UGKSND_FMOD375
		OscBuffer	= NULL;
		OscBlock	= 0;
	#elif defined(UGKSND_FMODEx)
	#elif defined(UGKSND_OAL)
	#elif defined(UGKSND_SDL)
	// Initialize SDL audio
    if (SDL_Init(SDL_INIT_AUDIO))
	{
        fprintf(stderr,
                "\nUnable to initialize SDL:  %s\n",
                SDL_GetError()
               );
        return ;
    }

	int i = Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096);

	// load support for the OGG and MOD sample/music formats
	int flags = MIX_INIT_OGG | MIX_INIT_MP3;
	int initted = Mix_Init(flags);
	if (initted != flags)
		const char * Error = SDL_GetError();
	#endif
}


UGKS_String CSoundSystem::ErrorMsg(unsigned int errcode)
{
#ifdef UGKSND_FMOD375
	if (SND_ERR_MAX <= errcode || errcode < 0)
		return "Unknown error";
#elif defined(UGKSND_FMODEx)
#elif defined(UGKSND_OAL)
	switch (errcode){
		case AL_INVALID_NAME:
			return "Invalid name.";
		case AL_INVALID_ENUM:
			return "Invalid enumeration.";
		case AL_INVALID_VALUE:
			return "Invalid value.";
		case AL_INVALID_OPERATION:
			return "Invalid operation.";
		case AL_OUT_OF_MEMORY:
			return "Out of memory!";
		default:
			return "Unknown OpenAL error.";
	}
#elif defined(UGKSND_SDL)
	return SDL_GetError();
#endif
}