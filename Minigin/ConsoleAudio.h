#pragma once
#include <mutex>
#include <queue>

#include "Audio.h"

class ConsoleAudio final: public Audio
{
public:
    ConsoleAudio();

    virtual void Update() override;

    virtual void playSound(int soundID) override;

    virtual void stopSound(int soundID) override;

    virtual void stopAllSounds() override;

    virtual void PlayMusic() override;

    virtual void PauseMusic() override;

    virtual void ResumeMusic() override;

    virtual int LoadSound(const char* file) override;

    virtual void LoadMusic(const char* file) override;

    virtual void SetEffectVolume(int volume) override;

    virtual void SetMusicVolume(int volume) override;
private:
    void Initialize();

    bool m_Running;
    Mix_Music* m_pMusic;
	std::mutex m_Mutex;
    std::condition_variable m_ConditionVariable;
    std::queue<int> m_Queue;
    std::vector<Mix_Chunk*> m_pSounds;

};

