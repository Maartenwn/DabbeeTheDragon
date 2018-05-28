#include "AudioPlayer.h"
#include "bass.h"
#include <string>
#include <fstream>
#pragma comment(lib, "bass.lib") // link with bass.dll

HSTREAM backgroundMusic; // Handle for open stream
AudioPlayer::AudioPlayer()
{
}


AudioPlayer::~AudioPlayer()
{
}

void InitAudioPlayer() {
	int device = -1; // Default Sounddevice
	int freq = 44100; // Sample rate (Hz)
	BASS_Init(device, freq, 0, 0, NULL);
}

void PlaySoundOnce(const std::string filename) {  
	
	HSTREAM singleSound = BASS_StreamCreateFile(FALSE, filename.c_str(), 0, 0, 0);
	//BASS_SetVolume(0.5);
	BASS_ChannelSetAttribute(singleSound, BASS_ATTRIB_VOL, 0.5f);
	BASS_ChannelPlay(singleSound, FALSE);
}

void PlaySoundInloop(const std::string filename) {
	
	backgroundMusic = BASS_StreamCreateFile(FALSE, filename.c_str(), 0, 0, 0);
	BASS_ChannelSetAttribute(backgroundMusic, BASS_ATTRIB_VOL, 0.03f);
	BASS_ChannelPlay(backgroundMusic, TRUE);
}


