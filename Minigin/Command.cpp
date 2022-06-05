#include "MiniginPCH.h"
#include "Command.h"

#include "Minigin.h"

dae::QuitGame::QuitGame(dae::Minigin* pEngine)
	: m_pEngine(pEngine)
{
}

void dae::QuitGame::Execute(float )
{
	m_pEngine->StopRunning();
}
