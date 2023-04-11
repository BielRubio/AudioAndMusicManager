#ifndef __AUDIO_H__
#define __AUDIO_H__

#include "Module.h"
#include "EntityManager.h"

#define DEFAULT_MUSIC_FADE_TIME 2.0f

struct _Mix_Music;
struct Mix_Chunk;

struct Track {

	const char* path;
	int position;
};

class Audio : public Module
{
public:

	Audio();

	// Destructor
	virtual ~Audio();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before quitting
	bool CleanUp();

	// Play a music file
	bool PlayMusic(const char* path, float fadeTime = DEFAULT_MUSIC_FADE_TIME);

	// Load a WAV in memory
	unsigned int LoadFx(const char* path);

	// Play a previously loaded WAV
	bool PlayFx(unsigned int fx, int repeat = 0);
	// Modified PlayFx with volume adjustments
	bool PlayFxWithVolume(unsigned int fx, int repeat = 0, int volume = 30);

	bool PlaySpatialFx(unsigned int fx, int repeat, Entity* entity1, Entity* entity2, uint minDistance, uint maxDistance);

	bool AddTrack(Track* newTrack);

	bool CleanUpPlaylist();

	//Plays the first track of the playlist
	bool PlayPlaylist();

	bool ChangeTrack(int newItem);

	int volume, fxvolume;
private:
	_Mix_Music* music;
	List<Mix_Chunk *> fx;

	List<Track *> playList;
};

#endif // __AUDIO_H__