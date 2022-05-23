#include "MiniginPCH.h"
#include "Audio.h"

//Audio::Audio()
//{
//	Initialize();
//}
//
//void Audio::Update()
//{
//	m_Mutex.lock();
//	while (!m_Queue.empty())
//	{
//		int id = m_Queue.front();
//		m_Queue.pop();
//		Mix_PlayChannel(-1, m_Sounds.at(id), 0);
//	}
//	m_Mutex.unlock();
//}
//
//void Audio::playSound(int soundID)
//{
//	m_Queue.push(soundID);
//	//Mix_PlayChannel(-1, m_Sounds.at(soundID), 0);
//}
//
//void Audio::stopSound(int )
//{
//}
//
//void Audio::stopAllSounds()
//{
//	//Dont use mix functions after this, else call openAudio first
//	Mix_CloseAudio();
//}
//
//void Audio::PlayMusic()
//{
//	Mix_PlayMusic(m_Music, -1);
//}
//
//void Audio::PauseMusic()
//{
//	Mix_PauseMusic();
//}
//
//void Audio::ResumeMusic()
//{
//	Mix_ResumeMusic();
//}
//
////void Audio::StopMusic()
////{
////}
//
//int Audio::LoadSound(char* file)
//{
//	m_Sounds.push_back(Mix_LoadWAV(file));
//	return int(m_Sounds.size()) - 1;
//	
//}
//
//void Audio::LoadMusic(const char* file)
//{
//	m_Music = Mix_LoadMUS(file);
//}
//
//void Audio::SetEffectVolume(int volume)
//{
//	Mix_Volume(-1, volume);
//}
//
//void Audio::SetMusicVolume(int volume)
//{
//	Mix_VolumeMusic(volume);
//}
//
//
//void Audio::Initialize()
//{
//	int flags = MIX_INIT_MP3;
//	int result = Mix_Init(flags);
//	if ((result & flags) != flags) {
//		printf("Mix_Init: Failed to init required ogg and mod support!\n");
//		printf("Mix_Init: %s\n", Mix_GetError());
//	}
//
//
//	// start SDL with audio support
//	if (SDL_Init(SDL_INIT_AUDIO) == -1) {
//		printf("SDL_Init: %s\n", SDL_GetError());
//		exit(1);
//	}
//	// open 44.1KHz, signed 16bit, system byte order,
//	//      stereo audio, using 1024 byte chunks
//	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
//		printf("Mix_OpenAudio: %s\n", Mix_GetError());
//		exit(2);
//	}
//	// 8 mixing channels get created
//	MIX_CHANNELS;
//}
