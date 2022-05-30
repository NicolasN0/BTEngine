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
	//auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	////Background
	//auto go = std::make_shared<dae::GameObject>();
	//go->AddComponent<dae::TextureComponent>(new dae::TextureComponent("background.jpg"));
	//scene.Add(go);

	////Header
	//go = std::make_shared<dae::GameObject>();
	//go->AddComponent<TextureComponent>(new TextureComponent("logo.png"));
	//go->SetPosition(216, 180);
	//scene.Add(go);

	////FPS COUNTER
	//go = std::make_shared<GameObject>();
	//go->AddComponent<TextComponent>(new TextComponent("Lingua.otf", 20, SDL_Color{ 255,255,0 }));
	//go->GetComponent<TextComponent>()->SetText("FPS");
	//go->AddComponent<FPSComponent>(new FPSComponent());
	//scene.Add(go);


	//go = std::make_shared<GameObject>();
	//go->AddComponent<TextComponent>(new TextComponent("Lingua.otf", 36));
	//go->GetComponent<TextComponent>()->SetText("Programming 4 Assignment");
	//go->SetPosition(80, 20);

	//scene.Add(go);

	////PeterPepper Player1
	//auto peterPepperP1 = std::make_shared<GameObject>();
	//peterPepperP1->AddComponent<PeterPepperComponent>(new PeterPepperComponent());
	//peterPepperP1->SetPosition(10, 400);
	////commands
	//Input::GetInstance().BindKey({ ButtonStates::buttonDown,ControllerButton::ButtonA,0 }, std::make_unique<DamagePlayer>(peterPepperP1->GetComponent<PeterPepperComponent>()));

	////HealthDisplayObject
	//go = std::make_shared<GameObject>();
	//TextComponent* healthDisplayComp = new TextComponent("Lingua.otf", 20);
	//go->AddComponent(healthDisplayComp);
	//healthDisplayComp->SetText("Lives");
	//go->SetPosition(10, 225);
	//scene.Add(go);
	////ScoreDisplayObject
	//go = std::make_shared<GameObject>();
	//TextComponent* ScoreDisplayComp = new TextComponent("Lingua.otf", 20);
	//go->AddComponent(ScoreDisplayComp);
	//ScoreDisplayComp->SetText("Scores");
	//go->SetPosition(10, 200);
	//scene.Add(go);

	//Subject* peterPepperSubject = new Subject;
	//peterPepperSubject->AddObserver(new HealthObserver(healthDisplayComp));
	//peterPepperSubject->AddObserver(new ScoreObserver(ScoreDisplayComp));
	//peterPepperP1->SetSubject(peterPepperSubject);
	//scene.Add(peterPepperP1);

	////PETERPEPPERPLAYER2

	//auto peterPepperP2 = std::make_shared<GameObject>();
	//peterPepperP2->AddComponent<PeterPepperComponent>(new PeterPepperComponent());
	//peterPepperP2->SetPosition(10, 400);
	////commands
	//Input::GetInstance().BindKey({ ButtonStates::buttonDown,SDLK_k,1 }, std::make_unique<DamagePlayer>(peterPepperP2->GetComponent<PeterPepperComponent>()));

	////HealthDisplayObject
	//go = std::make_shared<GameObject>();
	//TextComponent* healthDisplayCompP2 = new TextComponent("Lingua.otf", 20);
	//go->AddComponent(healthDisplayCompP2);
	//healthDisplayCompP2->SetText("Lives");
	//go->SetPosition(10, 375);
	//scene.Add(go);
	////ScoreDisplayObject
	//go = std::make_shared<GameObject>();
	//TextComponent* ScoreDisplayCompP2 = new TextComponent("Lingua.otf", 20);
	//go->AddComponent(ScoreDisplayCompP2);
	//ScoreDisplayCompP2->SetText("Scores");
	//go->SetPosition(10, 350);
	//scene.Add(go);

	//Subject* peterPepperSubjectP2 = new Subject;
	//peterPepperSubjectP2->AddObserver(new HealthObserver(healthDisplayCompP2));
	//peterPepperSubjectP2->AddObserver(new ScoreObserver(ScoreDisplayCompP2));
	//peterPepperP2->SetSubject(peterPepperSubjectP2);
	//scene.Add(peterPepperP2);

	//Audio* audioService = Locator::getAudio();
	////Music
	//audioService->LoadMusic("../Data/Sounds/Electric_Light_Orchestra_-_Mr_Blue_Sky.mp3");
	//audioService->SetMusicVolume(5);
	//audioService->PlayMusic();
	////Sound
	//audioService->SetEffectVolume(10);
	//int soundId;
	//soundId = audioService->LoadSound("../Data/Sounds/power_up1.wav");
	//audioService->playSound(soundId);
	//soundId = audioService->LoadSound("../Data/Sounds/book_page_turn.wav");
	//audioService->playSound(soundId);
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
