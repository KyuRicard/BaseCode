#pragma once

#include <iostream>
#include <map>
#include "SDL_mixer.h"
#define Audio AudioManager::GetInstance()

class AudioManager
{
public:
	static AudioManager * GetInstance()
	{
		if (instance == 0)
		{
			instance = new AudioManager();
		}
		return instance;
	}
	~AudioManager();
	void LoadSound(std::string);
	void LoadMusic(std::string);
	void PlaySound(std::string);
	void PlayMusic(std::string);
	void StopMusic();
	void StopAudio();
	void SetVolume(int);
private:
	AudioManager();
	std::map<std::string, Mix_Chunk *> sounds;
	std::map<std::string, Mix_Music *> musics;
	std::string path = "assets/sound/";
	static AudioManager * instance;
	std::string current;
};