#include "MiniginPCH.h"
#include "Minigin.h"
#include <thread>


#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"

#include <future>

#include "Locator.h"
#include "Audio.h"
#include "ConsoleAudio.h"
using namespace std;

void PrintSDLVersion()
{
	SDL_version compiled{};
	SDL_version linked{};

	SDL_VERSION(&compiled);
	SDL_GetVersion(&linked);
	printf("We compiled against SDL version %d.%d.%d ...\n",
		compiled.major, compiled.minor, compiled.patch);
	printf("We are linking against SDL version %d.%d.%d.\n",
		linked.major, linked.minor, linked.patch);
}

void dae::Minigin::Initialize()
{
	PrintSDLVersion();
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);

	auto locator = Locator();
	locator.initialize();

	//default input to quit
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{

}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	Locator::Quit();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	Audio* audioService = new ConsoleAudio();
	Locator::provide(audioService);

	ResourceManager::GetInstance().Init("../Data/");
	std::thread audioThread(&Audio::Update, audioService);
	LoadGame();

	{
		const auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto input = InputManager(std::make_unique<QuitGame>(this));
		
		m_Running = true;
		auto lastTime = std::chrono::high_resolution_clock::now();
		float lag = 0.0f;
		float fixedTimeStep = 0.02f;

		//DEBUGGING VARIABLES
		/*float soundStep = 2.f;
		float soundTime = 0.f;*/
		/*float stop = 5.f;
		float time = 0.f;*/

		//std::thread audioThread(&Audio::Update, audioService);

		while (m_Running)
		{
			auto currentTime = std::chrono::high_resolution_clock::now();
			float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();

			lastTime = currentTime;
			//soundTime += deltaTime;
			//time += deltaTime;

			input.ProcessInput();
			input.HandleInput(deltaTime);

			sceneManager.Update(deltaTime);
			lag += deltaTime;
			while (lag >= fixedTimeStep ) 
			{
				sceneManager.FixedUpdate(fixedTimeStep);
				lag -= fixedTimeStep;

			}
	

			renderer.Render();

		}

		audioThread.join();
	}

	Cleanup();
}



void dae::Minigin::StopRunning()
{
	m_Running = false;
	Locator::getAudio()->stopAllSounds();
}
