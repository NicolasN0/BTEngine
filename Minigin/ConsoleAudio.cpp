#include "MiniginPCH.h"
#include "ConsoleAudio.h"


ConsoleAudio::ConsoleAudio()
	: m_Running( true )
{
	Initialize();

}

void ConsoleAudio::Update()
{
	while(m_Running)
	{
		//m_Mutex.lock();
		std::unique_lock<std::mutex> lock(m_Mutex);
		m_ConditionVariable.wait(lock);

		while (!m_Queue.empty() && m_Running)
		{
			int id = m_Queue.front();
			m_Queue.pop();
			Mix_PlayChannel(-1, m_Sounds.at(id), 0);
		}
		
	}

	std::cout << "Exiting console audio update" << std::endl;
}

void ConsoleAudio::playSound(int soundID)
{
	//Mix_PlayChannel(-1, m_Sounds.at(soundID), 0);
	std::lock_guard<std::mutex> lock(m_Mutex);
	m_Queue.push(soundID);
	m_ConditionVariable.notify_one();
}

void ConsoleAudio::stopSound(int)
{
}

void ConsoleAudio::stopAllSounds()
{
	//Dont use mix functions after this, else call openAudio first
	/*for(auto sound : m_Sounds)
	{
		Mix_FreeChunk(sound);
		sound = nullptr;
	}
	m_Sounds.clear();*/
	
	Mix_CloseAudio();
	//while (Mix_Init(0))
	//	Mix_Quit();
	//stop threading

	//Quit later
	m_Running = false;
	m_ConditionVariable.notify_one();
}

void ConsoleAudio::PlayMusic()
{
	Mix_PlayMusic(m_Music, -1);
}

void ConsoleAudio::PauseMusic()
{
	Mix_PauseMusic();
}

void ConsoleAudio::ResumeMusic()
{
	Mix_ResumeMusic();
}

//void Audio::StopMusic()
//{
//}

int ConsoleAudio::LoadSound(const char* file)
{

	m_Sounds.push_back(Mix_LoadWAV(file));
	return int(m_Sounds.size()) - 1;

}

void ConsoleAudio::LoadMusic(const char* file)
{
	m_Music = Mix_LoadMUS(file);
	if (m_Music == nullptr)
	{
		std::string errorMsg = "SoundStream: Failed to load " + std::string{file} + ",\nSDL_mixer Error: " + Mix_GetError();
		std::cerr << errorMsg;
	}
}

void ConsoleAudio::SetEffectVolume(int volume)
{
	Mix_Volume(-1, volume);
}

void ConsoleAudio::SetMusicVolume(int volume)
{
	Mix_VolumeMusic(volume);
}


void ConsoleAudio::Initialize()
{
	int flags = MIX_INIT_MP3;
	int result = Mix_Init(flags);
	if ((result & flags) != flags) {
		printf("Mix_Init: Failed to init required ogg and mod support!\n");
		printf("Mix_Init: %s\n", Mix_GetError());
	}


	// start SDL with audio support
	if (SDL_Init(SDL_INIT_AUDIO) == -1) {
		printf("SDL_Init: %s\n", SDL_GetError());
		exit(1);
	}
	// open 44.1KHz, signed 16bit, system byte order,
	//      stereo audio, using 1024 byte chunks
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
		printf("Mix_OpenAudio: %s\n", Mix_GetError());
		exit(2);
	}
	// 8 mixing channels get created
	MIX_CHANNELS;
}
