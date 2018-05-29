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

static void onStreamDone(HSYNC handle, DWORD channel, DWORD data, void* pTarget) {
	HSTREAM stream = channel;//(HSTREAM)data;
	std::vector<HSTREAM>::iterator position = find(streams.begin(), streams.end(), stream);
 	if (position != streams.end()) // == myVector.end() means the element was not found
		streams.erase(position);
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
		BASS_ChannelSetSync(singleSound, 0, BASS_SYNC_END, onStreamDone, 0);
		streams.push_back(singleSound);
	}
}

void PlaySoundInloop(const std::string filename) {
	
	backgroundMusic = BASS_StreamCreateFile(FALSE, filename.c_str(), 0, 0, 0);
	BASS_ChannelSetAttribute(backgroundMusic, BASS_ATTRIB_VOL, 0.03f);
	BASS_ChannelPlay(backgroundMusic, TRUE);
}


