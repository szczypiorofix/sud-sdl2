#pragma once

#include <BASS/bass.h>
#include <string>


enum MUSIC_FILE_TYPE {
	OGG_MP3,
	MOD_XM
};


class Music {

public:
	constexpr static float DEFAULT_MUSIC_VOLUME = 1.0f;

	Music();
	~Music();

	bool Init();
	bool LoadFile( const std::string musicFile, bool loop );

	bool PlayMusic();
	bool StopMusic();
	bool PauseMusic();

	void SetVolume( float volume );
	void SetLoop( bool loop );

private:

	std::string musicFileName;

	HSTREAM stream;
	HMUSIC music;

	float volume;
	bool loop;

	MUSIC_FILE_TYPE fileType;

	bool fileIsModXmS3m();

};

