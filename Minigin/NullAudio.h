#pragma once
//#include "Audio.h"

class NullAudio : public Audio
{
public:
    virtual void Update() override{/* Do nothing. */ };
	virtual void playSound(int /*soundID*/) override { /* Do nothing. */ }
	virtual void stopSound(int /*soundID*/) override { /* Do nothing. */ }
	virtual void stopAllSounds() override { /* Do nothing. */ }
    virtual void PlayMusic() override { /* Do nothing. */ }
    virtual void PauseMusic() override { /* Do nothing. */ }
    virtual void ResumeMusic() override { /* Do nothing. */ }
    virtual int LoadSound(const char* /*file*/) override { return 0;/* Do nothing. */ };
    virtual void LoadMusic(const char* /*file*/) override { /* Do nothing. */ }
    virtual void SetEffectVolume(int /*volume*/) override { /* Do nothing. */ }
    virtual void SetMusicVolume(int /*volume*/) override { /* Do nothing. */ }
};
