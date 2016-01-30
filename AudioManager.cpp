#include "AudioManager.h"

using namespace std;

AudioManager * AudioManager::instance = 0;

AudioManager::AudioManager()
{
	int err = Mix_OpenAudio(44100, AUDIO_S16SYS, 4, 4096);
	if (err != 0)
	{
		cout << Mix_GetError() << endl;
	}
	Mix_VolumeMusic(32);
}

AudioManager::~AudioManager()
{
	Mix_CloseAudio();
}

void AudioManager::LoadSound(string soundFile)
{
	string finalPath = string(path + soundFile + ".wav");
	Mix_Chunk * sound = Mix_LoadWAV(finalPath.c_str());
	sounds[soundFile] = sound;
}

void AudioManager::LoadMusic(string musicFile)
{
	string finalPath = string(path + musicFile + ".wav");
	Mix_Music * music = Mix_LoadMUS(finalPath.c_str());
	musics[musicFile] = music;
}

void AudioManager::PlaySound(string sound)
{
	Mix_PlayChannel(-1, sounds.at(sound), 0);
}

void AudioManager::PlayMusic(string music)
{
	if (current == music)
		return;
	StopMusic();
	Mix_PlayMusic(musics.at(music), -1);
	current = music;
}

void AudioManager::StopMusic()
{
	Mix_HaltMusic();
}