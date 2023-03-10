#include "Music.h"
#include "../Defines.h"
#include <iostream>


Music::Music() {
	volume = DEFAULT_MUSIC_VOLUME;

	stream = 0;
	music = 0;

	loop = false;

	fileType = OGG_MP3;
}


bool Music::LoadFile( const std::string fileName, bool _loop ) {
	this->loop = _loop;

	if ( fileName.size() < 4 ) {
		exit( 1 );
	}

	musicFileName = DIR_RES_MUSIC + fileName;
	int flag = 0;
	if ( this->loop ) {
		flag = BASS_SAMPLE_LOOP;
	}

	fileType = fileIsModXmS3m() ? MOD_XM : OGG_MP3;

	printf( "MUSIC: Loading file '%s', fileType: %s\n", musicFileName.c_str(), fileType == OGG_MP3 ? "ogg/mp3" : "mod/xm" );

	if ( fileType == MOD_XM ) {
		music = BASS_MusicLoad( FALSE, musicFileName.c_str(), 0, 0, flag, 0);
		if ( BASS_ErrorGetCode() != 0 ) {
			printf( "BASS_MusicLoad() - file: '%s', error code: %i\n", musicFileName.c_str(), BASS_ErrorGetCode() );
			exit( 1 );
		}
		return true;
	}

	stream = BASS_StreamCreateFile( FALSE, musicFileName.c_str(), 0, 0, 0 );
	if ( stream == 0 ) {
		printf( "BASS_StreamCreateFile() - Failed to load stream '%s'! BASS_StreamCreateFile Error code = %i\n", musicFileName.c_str(), BASS_ErrorGetCode() );
		exit( 1 );
	}
	return true;
}


Music::~Music() {
	BASS_StreamFree( stream );
	BASS_MusicFree( music );
	printf("INFO: Music memory released\n");
}


bool Music::Init() {
	return BASS_Init( -1, 44100, 0, 0, NULL );
}


bool Music::PlayMusic() {
	if ( fileType == OGG_MP3 ) {
		return BASS_ChannelPlay( stream, this->loop );
	}
	// playing XM/MOD file
	return BASS_ChannelPlay( music, this->loop );
}

bool Music::StopMusic() {
	if ( !BASS_Stop() ) {
		printf( "BASS_Stop() - Failed to stop playing stream '%s'! Error code = %i\n", musicFileName.c_str(), BASS_ErrorGetCode() );
		return false;
	}
	return true;
}

bool Music::PauseMusic() {
	if ( !BASS_Pause() ) {
		printf( "BASS_Pause() - Failed to play stream '%s'! Error code = %i\n", musicFileName.c_str(), BASS_ErrorGetCode() );
		return false;
	}
	return true;
}

void Music::SetVolume( float _volume ) {
	this->volume = _volume;
	if ( !BASS_ChannelSetAttribute( fileType == OGG_MP3 ? stream : music, BASS_ATTRIB_VOL, this->volume ) ) {
		printf( "BASS_ChannelSetAttribute() - Failed to change channel volume on %s, file '%s'! BASS_ChannelSetAttribute Error code = %i\n", fileType == OGG_MP3 ? "HSTREAM" : "HMUSIC", musicFileName.c_str(), BASS_ErrorGetCode());
		exit( 1 );
	}
}

void Music::SetLoop( bool _loop ) {
	this->loop = _loop;
}

bool Music::fileIsModXmS3m() {
	const char* formats[ 3 ] = { "mod", ".xm", "s3m" };
	for ( unsigned int i = 0; i < 3; i++ ) {
		if ( strcmp( formats[i], musicFileName.substr( musicFileName.size() - 3, 3 ).c_str() ) == 0 ) {
			return true;
		}
	}
	return false;
}


