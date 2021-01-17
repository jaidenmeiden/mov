/**	Definition of the class Sound for the UPV Game Kernel

*	Prefix: UGKSND_

*	@author Ramon Molla, Carlos Martinez Perez
*	@version 2011-07
*	@version Alfonso Pérez 2013-03
	@version Ramón Mollá 2014-05 - 1st API conversion and refactoring
	@NewVersion Ramón Mollá 2017-12 - 2nd API conversion and refactoring
*/

#ifndef UGKSND_SOUND
#define UGKSND_SOUND

#include <stdlib.h>
#include <UGKAudioHardware.h>
#include <UGKString.h>
#include <HRTimer.h>

/**
*	Predefined sound volumes
*	In SDL the max vol level is half the max vol level in FMOD so the volumes need to be redefined
*/
#ifdef UGKSND_FMOD375
	#define UGKSND_DEFAULT_VOLUME		 -1		///< Default volume of the sound.
	#define UGKSND_MUTE					  0		///< Volume muted
	#define UGKSND_VOLUME_INCREMENT		  5		///< Increment of volume for ramp fading in or out
	#define UGKSND_ULTRA_LOW_VOLUME	     16		///< A VERY low value of volume
	#define UGKSND_LOW_VOLUME			 32		///< The low value of volume
	#define UGKSND_LOW_MED_VOLUME		 90		///< Low to medium value of volume
	#define UGKSND_MEDIUM_VOLUME		128     ///< The medium value of volume
	#define UGKSND_VOLUME_60			153     ///< 60% of the maximun volume
	#define UGKSND_VOLUME_80			204     ///< 80% of the maximun volume
	#define UGKSND_MAX_VOLUME			255		///< The maximun value a sound can reach at the top of its power
#elif defined(UGKSND_FMODEx)
#elif defined(UGKSND_OAL)
	// The volume values will later be converted to a 0.0 - 1.0 scale
	#define UGKCSND_DEFAULT_VOLUME		 255	///< Default volume of the sound.
	#define UGKCSND_MUTE				  0		///< Volume muted
	#define UGKCSND_VOLUME_INCREMENT	  5		///< Increment of volume for ramp fading in or out
	#define UGKCSND_ULTRA_LOW_VOLUME	 16		///< A VERY low value of volume
	#define UGKCSND_LOW_VOLUME			 32		///< The low value of volume
	#define UGKCSND_LOW_MED_VOLUME		 90		///< Low to medium value of volume
	#define UGKCSND_MEDIUM_VOLUME		128     ///< The medium value of volume
	#define UGKCSND_VOLUME_60			153     ///< 60% of the maximun volume
	#define UGKCSND_VOLUME_80			204     ///< 80% of the maximun volume
	#define UGKCSND_MAX_VOLUME			255		///< The maximun value a sound can reach at the top of its power
	#define UGKCSND_MAX_VOLUMEf			255.0f	///< The maximun value a sound can reach at the top of its power
#elif defined(UGKSND_SDL)
	#define UGKSND_DEFAULT_VOLUME		 -1		///< Default volume of the sound.
	#define UGKSND_MUTE					  0		///< Volume muted
	#define UGKSND_VOLUME_INCREMENT		  3		///< Increment of volume for ramp fading in or out
	#define UGKSND_ULTRA_LOW_VOLUME	      8		///< A VERY low value of volume
	#define UGKSND_LOW_VOLUME			 16		///< The low value of volume
	#define UGKSND_LOW_MED_VOLUME		 45		///< Low to medium value of volume
	#define UGKSND_MEDIUM_VOLUME		 64     ///< The medium value of volume
	#define UGKSND_VOLUME_60			 77     ///< 60% of the maximun volume
	#define UGKSND_VOLUME_80			102     ///< 80% of the maximun volume

	#define UGKSND_Sound_Length Uint32
	#define UGKSND_Sound_Buffer Uint8*

	class UGKSND_SoundType2
	{
	public:
		UGKSND_Sound_Buffer	Buffer;
		UGKSND_Sound_Length	Length;
		SDL_AudioSpec		Specs;

		UGKSND_SoundType2()
		{
			Buffer = NULL;
			Length = 0;
			Specs.callback = NULL;
			SDL_memset(&Specs, 0, sizeof(Specs));
		}
	}; 

#define UGKSND_MAX_VOLUME				SDL_MIX_MAXVOLUME		///< The maximun value a sound can reach at the top of its power
#endif

	#define UGKSND_HAL	F_POSITION 1000
	#define UGKSND_STRD_POSITION 2000

namespace UGK
{
	/**
	*	\class CSound
	*	Manages a single sound: loads it, unloads, plays, change intensity,...
	*/

	class UGK_API CSound
	{
		bool SetVolume2(int V);	///< Internal volume change function specific for every kind of sound management API
		bool SetVolume2();		///< Internal volume change function specific for every kind of sound management API

		void PlayChannel(int channel, int loops);

	protected:

		UGKS_String Path,	///<Path to the sound.
					Name;	///<Name of the sound file.

	public:

		//Atributes
		#ifdef UGKSND_FMOD375
			FSOUND_DSPUNIT* dspUnit;
			#define UGKSND_SoundType FSOUND_SAMPLE*
			int Channel;	///< Sound channel on which the sound will be phisically played
		#elif defined(UGKSND_FMODEx)
		#elif defined(UGKSND_OAL)
			ALuint bufferID;            // The OpenAL sound buffer ID
			ALuint sourceID;            // The OpenAL sound source
			ALenum format;              // The sound data format
			ALsizei freq;               // The frequency of the sound data
			#define UGKSND_SoundType vector<char>
		#elif defined(UGKSND_SDL)
			SDL_AudioSpec		Specs;
		#endif

		UGKSND_SoundType Sound;			///<The sound to be played in fmod type.
		int Volume,						///<The intensity of the sound. 0 no sound, 255 maximun power (in SDL the maximun is 128)
			Position,					///<The position of the sound.
			Channel;					///< HW audio channel where is being played this sound

		//Methods
		/**
		*	\fn void CSound::Init()
		*	Basic constructor
		*/
		inline void Init() { Path.clear(); Name.clear(); Position = 0; Volume = UGKSND_MAX_VOLUME;}
		bool		Init(UGKS_String name, int vol, UGKS_String path);///< Initializes a new sound
	
		CSound(){Init();}						///< Constructor of the class
		CSound(UGKS_String name, int vol, UGKS_String path);	///< Constructor of the class
		~CSound();

		//Setters and Getters
		/**
		*	\fn void CSound::SetName (CString name)
		*	Specifies the name of a sound
		*	\param[in] name The name of the sound
		*/
		inline void SetName(UGKS_String name) { Name = name; }
		
		/**
		*	\fn void CSound::SetPath (CString path)
		*	Specifies the name of a sound
		*	\param[in] path The name of the path of the sound
		*/
		inline void SetPath(UGKS_String path){ Path = path; }
		
		inline UGKS_String GetName() { return Name; }
		inline UGKS_String GetPath() { return Path; }
		
		void Load();
		inline void Load(UGKS_String File, UGKS_String P) { Name = File;  Path = P; Load(); }
		void Play(int vol);							///< Plays this sound with a determined volume (v can be NULL) 
		void Play();

		UGKSND_SoundType getStream(); ///< Get the stream of the sound

		bool Stop();
		#ifdef UGKSND_FMOD375
		#elif defined(UGKSND_FMODEx)
		#elif defined(UGKSND_OAL)
			bool LoadOgg(CString fileName, UGKSND_SoundType &buffer, ALenum &format, ALsizei &freq);
		#elif defined(UGKSND_SDL)
		#endif

		void SetVolume(int vol); ///< Set new volume
		/**
		*	\fn UGKSND_SoundType CSound::getStream()
		*	gets the stream of the sound
		*/
		inline UGKSND_SoundType GetSound(){return Sound;}


		/**
		*	\fn void CSound::SetPosition(int position)
		*	Sets a new Position to the sound
		*	\param[in] position New position to the sound
		*/
		inline void SetPosition(int position) { if(0 > position) Position = 0; else Position=position;}

		bool Pause();
		bool Resume();
		void Expire(int ticks);
		void Close(); ///<Close the stream of the sound
	
	};
}

#ifdef UGKSND_FMOD375
	void * F_CALLBACKAPI dspCallbackSounds(void *originalbuffer, void *newbuffer, int length, int param);
	signed char F_CALLBACKAPI metacallback(char *name, char *value, int userdata);
#elif defined(UGKSND_FMODEx)
#elif defined(UGKSND_OAL)
#elif defined(UGKSND_SDL)
#endif

#endif
