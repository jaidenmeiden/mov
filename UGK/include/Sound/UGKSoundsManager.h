/** Definition of the class Music Manager for the UPV Game Kernel
*  General class to manage all the sounds
*  Prefix: UGKCSM_

*	@author Ramon Molla, Carlos Martinez Perez
*	@NewVersion Ramón Mollá 2014-05 - API conversion and refactoring

*/

#ifndef UGKCSM_SOUND
#define UGKCSM_SOUND

#include <UGKSound.h>
#include <UGKMusic.h>
#include <vector>
#include <map>

//For the error msg displayed
#define UGKCSM_ERR_MAX_LONG 128
#define UGKCSM_FADING_STEP_DURATION 30	//Time lasting every step up or down while Fading up or down a music/sound
#define UGKCSM_FADING_STEP 5			//Amount of power a sound/music can be increased/decreased in power while Fading it up or down
#define UGKCSM_NO_INDEX -1			//Amount of power a sound/music can be increased/decreased in power while Fading it up or down
#define UGKSND_MAX_NAME_LENGTH 30

//Sampling Rates in Hz
#define CSM_CD_SAMPLING_RATE UGKSNDENG_FREQ_CD ///< CD Sampling rate 

//Number of final audio channels (loudspeakers) listened by humans
#define CSM_STEREO 2	///< For earphones, stereo devices,...

//Amount of bytes used to allocate temporaly any sound or part of sound
#define CSM_DEFAULT_SOUND_BUFFER 4096	///< 4KB
#ifdef UGKSND_FMOD375
extern UGKS_String CSM_ErrorString[SND_ERR_MAX];
#endif

#define CSM_SOUND_NAME	UGKS_String
#define CSM_FILE_ID		int
#define CSM_NO_ID -1

namespace UGK
{
	// *.PLS (WINAMP PLAYLIST) PARSER FOR STREAMS
	typedef struct
	{
		int    count;
		void **name;
		void **displayname;
	} Playlist;

	typedef enum
	{
		CSM_MUSIC,	///<Music
		CSM_SOUNDS,	///<Sound
		CSM_VOCAL,	///<Vocals
		CSM_MAX_SOUND_TRACKS	///<For accounting purpouses only
	}CSM_SOUND_TRACKS;

#ifdef UGKSND_FMOD375
#elif defined(UGKSND_FMODEx)
#elif defined(UGKSND_OAL)
#elif defined(UGKSND_SDL)
	//Sound files format supported
	#define CSM_ASK_SOUND_FILES 0						///< For asking which sound files are supported
	#define CSM_FLAC_SOUND_FILES MIX_INIT_FLAC			///< Support FLAC sound files
	#define CSM_MOD_SOUND_FILES MIX_INIT_MOD			///< Support MOD sound files
	#define CSM_MP3_SOUND_FILES MIX_INIT_MP3			///< Support MP3 sound files
	#define CSM_OGG_SOUND_FILES MIX_INIT_OGG			///< Support OGG sound files
	#define CSM_SYNTH_SOUND_FILES MIX_INIT_FLUIDSYNTH	///< Support SYNTH sound files
#endif

	typedef std::vector<CSound>						SoundVector;
	typedef std::map<CSM_SOUND_NAME, CSM_FILE_ID>	SoundsDictionaryType;

	class UGK_API CSoundsManager
	{
	//Attributes
	protected:

		UGKS_String TrackPath,	///< Default path of the sound
					MusicPath;	///< Default path of the music
		SoundsDictionaryType	SoundDictionary;	///< Translator from the name of a sound to the position in the vector sound 
		SoundVector				Sound;	///<An array where the sounds of the game are
		UGKAudioHardware*		SoundCard;
	
		bool			PlayingMusic;		// MUSIC ON/OFF
		CM_MUSIC_TYPE	music_type;			// music type

		int				currentMusicIndex,
						FileTypeSupported;	///< Different types of sound files supported by the API

	
	public:
	
		#ifdef UGKSND_FMOD375

			FMUSIC_MODULE * FadingModule;			// Music fading in or out

			
		
			UGKSND_SoundType StreamChannel;			// Streaming channel
			FMUSIC_MODULE * MODModule;				// Module for MOD sounds

			// FMOD CALLBACKS
			signed short	*OscBuffer;
			int				 OscBlock ;

			FSOUND_DSPUNIT* dspUnitSounds;			///<DSP used for the sounds not seen at the spectrum
			FSOUND_DSPUNIT* dspUnitSpectrum;		///<DSP SPECTRUM (UNIT)
			CSound			*music;

		#elif defined (UGKSND_FMODEx)
		#elif defined (UGKSND_OAL)
			CSound			*music;
		#elif defined (UGKSND_SDL)
			UGKSND_MusicType	music;
		#endif

		int Volume;		///<The intensity of the sound BY DEFAULT 0 no sound, 255 maximun power (in SDL the max vol is 128).

		int NSounds; ///<Number of sounds
	
		//Methods
		CSoundsManager	(){};
		~CSoundsManager	();

		///Translates from a string to the token that the string represents
		CSM_FILE_ID		Name2Id	(CSM_SOUND_NAME Lexeme);

		///Given a token, this method converts it into its lexeme (string) associated to it
		CSM_SOUND_NAME	Id2Name(CSM_FILE_ID Id){ return Sound[Id].GetName(); };

		inline void SetSoundNames(CSM_SOUND_NAME Files[], unsigned int FilesAmount)
		{
			CSM_FILE_ID i;

			SoundDictionary.clear();

			for (i = 0; i<FilesAmount; i++) SoundDictionary[Files[i]] = i;
		}

		void				Init();
		inline void			Init(UGKAudioHardware*		SC)				{ SetAudioHardware(SC); Init(); }

		//Setter and Getter
		inline void			SetAudioHardware	(UGKAudioHardware* sc)	{SoundCard = sc;}
		UGKAudioHardware	*GetAudioHardware	()						{return SoundCard;}

		//Setters
		/**
		*	\fn void CSound::SetTrackPath (UGKS_String name)
		*	Specifies the name of a TrackPath. It does not include directories slash separator
		*	\param[in] name The name of the TrackPath
		*/
		inline void SetTrackPath	(UGKS_String name)	{TrackPath = name;}

		/**
		*	\fn void CSound::SetMusicPath (UGKS_String name)
		*	Specifies the name of a MusicPath. It does not include directories slash separator
		*	\param[in] name The name of the MusicPath
		*/
		inline void SetMusicPath	(UGKS_String name)	{MusicPath = name;}

		//Getters
		inline UGKS_String GetTrackPath	() { return TrackPath; }
		inline UGKS_String GetMusicPath	() { return MusicPath; }

		void		LoadMusic		(const UGKS_String file); ///<Loads a music file in memory

		void		StopMusic		(void);
		void		NextMusicTrack	(void);

		//Playlist *ParsePlaylist			(UGKS_String name);

		void LoadSounds					(int Size, UGKS_String SoundsFiles[]); ///<Loads all the different sounds that can be performed at any time during the playing of the game
		/**
		*	\fn void ClearSound(int SoundIndex)
		*	Deletes the sound specified
		*	\param[in] Index of the sounds to be deleted
		*/
		inline void ClearSound		(int SoundIndex){Sound.erase(Sound.begin()+SoundIndex);};
		inline void ClearAllSounds	()				{Sound.clear();};

		UGKS_String ErrorMsg		(const int);

		#ifdef UGKSND_FMOD375
			void MusicFadingOut			(void);
			void MusicFadingIn			(void);
			void fmodExtract			(void);

			inline void Play			(const unsigned char s, int vol){Sound[s].Play(vol);} ///<Plays the sound s
			inline UGKS_String GetErrorMsg	()								{return CSM_ErrorString[FSOUND_GetError()];}
			inline void Close			()								{SoundCard->CloseAudio();}
		#elif defined (UGKCSND_OAL)
			void MusicFadingIn			(void);		
			void MusicFadingOut			(void);

			inline void Play			(const unsigned char s, int vol){Sound[s].Play(vol);}; ///<Plays the sound s
			inline void PauseMusic		(void){ if(PlayingMusic)		{ music->Pause(); PlayingMusic=false;}}
			inline void ResumeMusic		(void){ if(!PlayingMusic)		{ music->Play(); PlayingMusic=true;}}
			inline UGKS_String GetErrorMsg	();
		#elif defined (UGKSND_SDL)
			inline void MusicFadingIn	(void){ if(!PlayingMusic)		{ SoundCard->FadeInMusic(music, 0, 2000); PlayingMusic = true; }}	///<Fades in the current music
			inline void MusicFadingOut	(void)							{ SoundCard->FadeOutMusic(2000); StopMusic(); }	///<Fades out the current music

			inline void Play			(const unsigned char s, int vol){Sound[s].Play(vol);}; ///<Plays the sound s
			inline void PauseMusic(void)								{ if (PlayingMusic)	{ SoundCard->PauseMusic(music); PlayingMusic = false; } }	///<Pauses the current music
			void ResumeMusic(void); ///<Resumes the current music
			inline int	FilesSupported(void)							{ if (CSM_ASK_SOUND_FILES == FileTypeSupported) return Mix_Init(CSM_ASK_SOUND_FILES); else return FileTypeSupported; }
			inline UGKS_String GetErrorMsg	()							{ return SDL_GetError(); }
			inline void Close()	{for (unsigned int i = 0; i < Sound.size(); i++) { Mix_FreeChunk(Sound[i].Sound); Sound[i].Sound = NULL; } PlayingMusic = false;}

		#endif
			inline CSound* GetSound(const unsigned char s){ return &Sound[s]; }
		/**
		*	\fn void SetVolume	(const unsigned char s, int vol)
		*	Set a new Volume
		*	\param[in] s Token of the sound to modify
		*	\param[in] s vol Volume of the sound
		*/
		inline void SetVolume	(const unsigned char s, int vol){Sound[s].SetVolume(vol);}
	
		/**
		*	\fn void SetVolumeAll	(int vol)
		*	Set a new Volume in all the Sounds
		*	\param[in] s vol Volume of the sound
		*/

		void SetVolumeAll	(int vol) {for(unsigned int i=0;i<(int)Sound.size();i++) Sound[i].SetVolume(vol);}

		/**
		*	\fn void SetPosition	(const unsigned char s,int pos)
		*	Sets a new Position
		*	\param[in] s Token of the sound to modify
		*	\param[in] s pos Position of the sound
		*/
		inline void SetPosition	(const unsigned char s, int pos){Sound[s].SetPosition(pos);}

		/**
		*	\fn void setTrackPath(UGKS_String path)
		*	Set the Path of the Sound to the path that indicates the parameter
		*	\param[in] Track, Type of the track [UGKCSM_SOUND_TRACKS].
		*	\param[in] path, String of characters with the path to the track.
		*/
		inline void		SetTrackPath(unsigned int Track, UGKS_String path) { Sound[Track].SetPath(path); }

		/**
		*	\fn void setTrackName(unsigned int Track, UGKS_String name)
		*	Set the Path of the Sound to the path that indicates the parameter
		*	\param[in] Track, Type of the track [UGKCSM_SOUND_TRACKS].
		*	\param[in] name, String of characters with the name to the track.
		*/
		inline void		SetTrackName(unsigned int Track, UGKS_String name) { Sound[Track].SetName(name); }

		/**
		*	\fn const UGKS_String CSoundsManager::getTrackPath(unsigned int Track)
		*	Get the Path where the sounds are
		*	\param[in] Track, Type of the track [UGKCSM_SOUND_TRACKS].
		*/
		inline UGKS_String GetTrackPath(unsigned int Track) { return Sound[Track].GetPath(); }

		/**
		*	\fn const UGKS_String CSoundsManager::getTrackName(unsigned int Track)
		*	Get the Path where the sounds are
		*	\param[in] Track, Id of the track
		*/
		inline UGKS_String GetTrackName		(unsigned int Track) { return Sound[Track].GetName(); }


		void		MusicStart				(void);
		int			Check4SupportedFiles	(int Request);
		inline int	Check4SupportedFiles	() {return Check4SupportedFiles(CSM_FLAC_SOUND_FILES || CSM_MOD_SOUND_FILES || CSM_MP3_SOUND_FILES || CSM_OGG_SOUND_FILES || CSM_SYNTH_SOUND_FILES); }
		int			SupportFiles			(int FilesMask);
	};
}

#endif