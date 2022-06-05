#include "MiniginPCH.h"
#include "InputManager.h"
//#include <windows.h>
#include "iostream"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Xinput.h>

#define MAX_PLAYERS 4

class dae::InputManager::InputManagerImpl
{
	XINPUT_STATE m_CurrentState[MAX_PLAYERS];
	XINPUT_STATE m_PreviousState[MAX_PLAYERS];
	unsigned int m_ButtonsPressedThisFrame[MAX_PLAYERS];
	unsigned int m_ButtonsReleasedThisFrame[MAX_PLAYERS];

public:
	InputManagerImpl() = default;
	void ProcessInput(int id)
	{
		int controllerIndex{id};
		CopyMemory(&m_PreviousState[id], &m_CurrentState[id], sizeof(XINPUT_STATE));
		ZeroMemory(&m_CurrentState[id], sizeof(XINPUT_STATE));
		XInputGetState(controllerIndex, &m_CurrentState[id]);


		auto buttonChanges = m_CurrentState[id].Gamepad.wButtons ^ m_PreviousState[id].Gamepad.wButtons;
		m_ButtonsPressedThisFrame[id] = buttonChanges & m_CurrentState[id].Gamepad.wButtons;
		m_ButtonsReleasedThisFrame[id] = buttonChanges & (~m_CurrentState[id].Gamepad.wButtons);
	}
	bool IsPressed(ControllerButton button,int id) const
	{
		return m_CurrentState[id].Gamepad.wButtons & int(button);

	}
	bool IsDownThisFrame(ControllerButton button, int id) const
	{
		return m_ButtonsPressedThisFrame[id] & int(button);

	}
	bool IsUpThisFrame(ControllerButton button, int id) const
	{
		return m_ButtonsReleasedThisFrame[id] & int(button);

	}

};

void dae::Input::ClearKeys()
{
	m_consoleCommands.clear();
	m_KeyboardCommands.clear();
	m_Clear = true;
	
}

bool dae::Input::GetClear() const
{
	return m_Clear;
}

void dae::Input::SetClear(bool clear)
{
	m_Clear = clear;
}

void dae::Input::BindKey(ControllerKey key, std::unique_ptr<Command> c)
{
	m_consoleCommands[key] = std::move(c);
}

void dae::Input::BindKey(KeyboardKey key, std::unique_ptr<Command> c)
{
	m_KeyboardCommands[key] = std::move(c);
}

dae::InputManager::InputManager(std::unique_ptr<Command> quitCommand)
	: m_QuitGame( std::move(quitCommand) )
{
	pImpl = new InputManagerImpl;
}

dae::InputManager::~InputManager()
{
	delete pImpl;
	pImpl = nullptr;
}

void dae::InputManager::ProcessInput()
{
	for (int i = 0; i < MAX_PLAYERS; i++)
	{
		pImpl->ProcessInput(i);
	}
}

bool dae::InputManager::IsPressed(ControllerButton button, int id) const
{
	return pImpl->IsPressed(button,id);
}


bool dae::InputManager::IsDownThisFrame(ControllerButton button, int id) const
{

	return pImpl->IsDownThisFrame(button, id);
}

bool dae::InputManager::IsUpThisFrame(ControllerButton button, int id) const
{

	return pImpl->IsUpThisFrame(button, id);
}

void dae::InputManager::HandleInput(float dt)
{
#pragma region Controller
	for (const auto& [controllerKey, action] : Input::GetInstance().GetConsoleCommands())
	{
		
		auto [state, button, id] = controllerKey;

		switch(state)
		{
		case ButtonStates::buttonDown:
			if(IsDownThisFrame(button,id))
			{
				action->Execute(dt);
			}
			break;
		case ButtonStates::buttonPressed:
			if (IsPressed(button,id))
			{
				action->Execute(dt);
			}
			break;
		case ButtonStates::buttonUp:
			if (IsUpThisFrame(button,id))
			{
				action->Execute(dt);
			}
			break;
		}

		if (Input::GetInstance().GetClear() == true)
		{
			Input::GetInstance().SetClear(false);
			break;
		}

	}
#pragma endregion Controller


#pragma region Keyboard
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT)
		{
			m_QuitGame->Execute(dt);
		}
		for (const auto& [key, action] : Input::GetInstance().GetKeyboardCommands())
		{
		

			auto [state, button, id] = key;
			switch(state)
			{
			case ButtonStates::buttonDown:
				if (e.key.type == SDL_KEYDOWN)
				{
					if(e.key.repeat == 0)
					{
						if (button == e.key.keysym.sym)
						{
							action->Execute(dt);
						}
					}
				}
				break;
			case ButtonStates::buttonPressed:
				if (e.key.type == SDL_KEYDOWN)
				{
					if (button == e.key.keysym.sym)
					{
						action->Execute(dt);
					}
				}
				break;
			case ButtonStates::buttonUp:
				if (e.key.type == SDL_KEYUP)
				{
					if (button == e.key.keysym.sym)
					{
						action->Execute(dt);
					}
				}
				break;
			}
			if (Input::GetInstance().GetClear() == true)
			{
				Input::GetInstance().SetClear(false);
				break;
			}
		}
	}
#pragma endregion Keyboard

	
}
