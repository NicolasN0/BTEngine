#pragma once


class Audio
{
public:
    Audio() = default;
	virtual ~Audio(){};

    Audio(const Audio&) = delete;
    Audio(Audio&&) noexcept = delete;

    Audio& operator=(const Audio&) = delete;
    Audio& operator=(Audio&&) noexcept = delete;
    virtual void Update() = 0;
   

    virtual void playSound(int soundID) = 0;

    virtual void stopSound(int soundID) = 0;

    virtual void stopAllSounds() = 0;

    virtual void PlayMusic() = 0;

    virtual void PauseMusic() = 0;

    virtual void ResumeMusic() = 0;

    virtual int LoadSound(const char* file) = 0;

    virtual void LoadMusic(const char* file) = 0;

    virtual void SetEffectVolume(int volume) = 0;

    virtual void SetMusicVolume(int volume) = 0;

};