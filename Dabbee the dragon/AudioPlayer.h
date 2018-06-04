#pragma once
#include <string>
class AudioPlayer
{
public:
	AudioPlayer();
	~AudioPlayer();
};

void InitAudioPlayer();
void AudioPlayer_update();
void PlaySoundOnce(const std::string filename);
void PlaySoundInloop(const std::string filename);