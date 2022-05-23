#pragma once

#include <map>
#include <memory>
#include <utility>
#include "Command.h"
#include <vector>
#include <SDL.h>
#include "Singleton.h"
#pragma comment(lib, "xinput.lib")
namespace dae
{

	enum class ControllerButton
	{
		DpadUp = 0x0001,
		DpadDown = 0x0002,
		DpadLeft = 0x0004,
		DpadRight = 0x0008,
		Start = 0x0010,
		Back = 0x0020,
		LeftThumb = 0x0040,
		RightThumb = 0x0080,
		LeftShoulder = 0x0100,
		RightShoulder = 0x0200,
		ButtonA = 0x1000,
		ButtonB = 0x2000,
		ButtonX = 0x4000,
		ButtonY = 0x8000,
		//todo: add the other buttons
	};

	enum class ButtonStates
	{
		buttonDown,
		buttonPressed,
		buttonUp
	};

	class Input : public Singleton<Input>
	{
			
		using ControllerKey = std::tuple<ButtonStates, ControllerButton,int>;
		using KeyboardKey = std::tuple<ButtonStates, SDL_KeyCode,int>;
		using ControllerCommandsMap = std::map<ControllerKey, std::unique_ptr<Command>>;
		//using KeyboardCommandsMap = std::map<SDL_KeyCode, std::unique_ptr<Command>>;
		using KeyboardCommandsMap = std::map<KeyboardKey, std::unique_ptr<Command>>;

		ControllerCommandsMap m_consoleCommands{};
		KeyboardCommandsMap m_KeyboardCommands{};

	public:
		void BindKey(ControllerKey key, std::unique_ptr<Command> c);
		void BindKey(KeyboardKey key, std::unique_ptr<Command> c);
		const ControllerCommandsMap& GetConsoleCommands() 
		{
			return m_consoleCommands;
		};
		const KeyboardCommandsMap& GetKeyboardCommands()
		{
			return m_KeyboardCommands;
		};
	};


	class InputManager
	{
		class InputManagerImpl;
		InputManagerImpl* pImpl;
	public:
		InputManager(std::unique_ptr<Command> quitCommand);
		~InputManager();
		InputManager(const InputManager& other) = delete;
		InputManager(InputManager&& other) = delete;
		InputManager& operator=(const InputManager& other) = delete;
		InputManager& operator=(InputManager&& other) = delete;
		void ProcessInput();
		bool IsPressed(ControllerButton button, int id) const;
		bool IsDownThisFrame(ControllerButton button, int id) const;
		bool IsUpThisFrame(ControllerButton button, int id) const;
		void HandleInput(float dt);
	private:

		std::unique_ptr<Command> m_QuitGame;
	};
}