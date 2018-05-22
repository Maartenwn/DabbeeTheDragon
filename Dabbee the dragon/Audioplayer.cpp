#include "Audioplayer.h"
#include <iostream>
using namespace std;
#include <Windows.h>
#include <MMsystem.h>



Audioplayer::Audioplayer()
{
}




Audioplayer::~Audioplayer()
{
}

void PlayAudioInLoop(string filename)
{
	std::cout << "playing file" << std::endl;
	PlaySound(filename.c_str, NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
}

void PlayAudioOnce(string filename)
{
	std::cout << "playing file" << std::endl;
	PlaySound(filename.c_str, NULL, SND_FILENAME | NULL | SND_ASYNC);
}

