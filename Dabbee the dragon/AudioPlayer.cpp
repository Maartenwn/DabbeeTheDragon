#include "AudioPlayer.h"
#include "bass.h"
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

#pragma comment(lib, "bass.lib") // link with bass.dll

HSTREAM backgroundMusic; // Handle for open stream
AudioPlayer::AudioPlayer()
{
}


vector<HSTREAM> streams;

AudioPlayer::~AudioPlayer()
{
}

void InitAudioPlayer() {
	int device = -1; // Default Sounddevice
	int freq = 44100; // Sample rate (Hz)
	BASS_Init(device, freq, 0, 0, NULL);
}

void AudioPlayer_update() {
	for (auto it = streams.begin(); it != streams.end();) {
		if (BASS_ChannelIsActive(*it) != BASS_ACTIVE_PLAYING) {
			it = streams.erase(it);
		}else it++;
	}
}
		
void PlaySoundOnce(const std::string filename) {  
	boolean exists = false;
	for (HSTREAM stream : streams) {
		BASS_CHANNELINFO info;
		BASS_ChannelGetInfo(stream, &info);
		if (info.filename == filename) {
			exists = true;
		}
	}
	if (!exists) {
		HSTREAM singleSound = BASS_StreamCreateFile(FALSE, filename.c_str(), 0, 0, 0);
		//BASS_SetVolume(0.5);
		BASS_ChannelSetAttribute(singleSound, BASS_ATTRIB_VOL, 0.5f);
		BASS_ChannelPlay(singleSound, FALSE);
		streams.push_back(singleSound);
	}
}

void PlaySoundInloop(const std::string filename) {
	
	backgroundMusic = BASS_StreamCreateFile(FALSE, filename.c_str(), 0, 0, 0);
	BASS_ChannelSetAttribute(backgroundMusic, BASS_ATTRIB_VOL, 0.03f);
	BASS_ChannelPlay(backgroundMusic, TRUE);
}


