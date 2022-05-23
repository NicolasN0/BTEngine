#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include <SDL_pixels.h>
//#include "MiniginPCH.h"
#include "GameObject.h"
#include "Minigin.h"
#include "SceneManager.h"


#include <thread>
#include "InputManager.h"

#include "Scene.h"

#include "FPSComponent.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include "PeterPepperComponent.h"
#include "BasicEnemyComponent.h"

#include "ScoreObserver.h"
#include "HealthObserver.h"
#include <SDL.h>

#include "Commands.h"
#include "Locator.h"
#include <fstream>


using namespace std;
using namespace dae;

void MakeLevel(std::string levelName,Scene& scene);

class BurgerTime final : public dae::Minigin
{
public:
	 virtual void LoadGame() const override
	{
		
		 auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");


#pragma region background
		 //Background
		 auto go = std::make_shared<dae::GameObject>();
		 go->AddComponent<dae::TextureComponent>(new dae::TextureComponent("backgroundBlack.png"));
		 scene.Add(go);


		 //FPS COUNTER
		 go = std::make_shared<GameObject>();
		 go->AddComponent<TextComponent>(new TextComponent("Lingua.otf", 20, SDL_Color{ 255,255,0 }));
		 go->GetComponent<TextComponent>()->SetText("FPS");
		 go->AddComponent<FPSComponent>(new FPSComponent());
		 scene.Add(go);

		 //SCORES
		 go = std::make_shared<GameObject>();
		 go->AddComponent<TextComponent>(new TextComponent("Lingua.otf", 30,SDL_Color{255,0,0}));
		 go->GetComponent<TextComponent>()->SetText("1UP");
		 go->SetPosition(80, 0);
		 scene.Add(go);

		 go = std::make_shared<GameObject>();
		 go->AddComponent<TextComponent>(new TextComponent("Lingua.otf", 30, SDL_Color{ 255,0,0 }));
		 go->GetComponent<TextComponent>()->SetText("HI-SCORE");
		 go->SetPosition(180, 0);
		 scene.Add(go);


		 go = std::make_shared<GameObject>();
		 go->AddComponent<TextComponent>(new TextComponent("Lingua.otf", 18, SDL_Color{ 0,255,0 }));
		 go->GetComponent<TextComponent>()->SetText("PEPPER");
		 go->SetPosition(500, 0);
		 scene.Add(go);


		 go = std::make_shared<GameObject>();
		 go->AddComponent<TextComponent>(new TextComponent("Lingua.otf", 26));
		 go->GetComponent<TextComponent>()->SetText("0000");
		 go->SetPosition(80, 30);
		 scene.Add(go);

		 go = std::make_shared<GameObject>();
		 go->AddComponent<TextComponent>(new TextComponent("Lingua.otf", 26));
		 go->GetComponent<TextComponent>()->SetText("0000");
		 go->SetPosition(180, 30);
		 scene.Add(go);


		 go = std::make_shared<GameObject>();
		 go->AddComponent<TextComponent>(new TextComponent("Lingua.otf", 26));
		 go->GetComponent<TextComponent>()->SetText("0");
		 go->SetPosition(500, 30);
		 scene.Add(go);

#pragma endregion background


		 go = std::make_shared<dae::GameObject>();
		 go->AddComponent<dae::TextureComponent>(new dae::TextureComponent("Level1.png"));
		 go->SetPosition(100, 100);
		 go->SetScale(2, 2);
		 scene.Add(go);


		 go = std::make_shared<dae::GameObject>();
		 go->SetSize(glm::vec3(25, 60, 1));
		 go->SetPosition(295, 225);
		 go->SetDebugDraw(true);
		 go->SetTag("Ladder");
		 scene.Add(go);


		 go = std::make_shared<dae::GameObject>();
		 go->SetSize(glm::vec3(120, 25, 1));
		 go->SetPosition(200, 260);
		 go->SetDebugDraw(true);
		 go->SetTag("Platform");
		 scene.Add(go);


#pragma region player1
		 //PeterPepper Player1
		 auto peterPepperP1 = std::make_shared<GameObject>();
		 peterPepperP1->AddComponent<PeterPepperComponent>(new PeterPepperComponent());
		 peterPepperP1->AddComponent<TextureComponent>(new TextureComponent("PeterPepperCrop.png"));
		 peterPepperP1->SetPosition(250, 265);
	 	peterPepperP1->SetTag("Player");
		 //commands
		 Input::GetInstance().BindKey({ ButtonStates::buttonDown,ControllerButton::ButtonA,0 }, std::make_unique<DamagePlayer>(peterPepperP1->GetComponent<PeterPepperComponent>()));
		 /*Input::GetInstance().BindKey({ ButtonStates::buttonPressed,SDLK_a,1 }, std::make_unique<MoveLeft>(peterPepperP1, 50));
		 Input::GetInstance().BindKey({ ButtonStates::buttonPressed,SDLK_d,1 }, std::make_unique<MoveRight>(peterPepperP1, 50));
		 Input::GetInstance().BindKey({ ButtonStates::buttonPressed,SDLK_w,1 }, std::make_unique<MoveUp>(peterPepperP1, 50));
		 Input::GetInstance().BindKey({ ButtonStates::buttonPressed,SDLK_s,1 }, std::make_unique<MoveDown>(peterPepperP1, 50));*/

		/* Input::GetInstance().BindKey({ ButtonStates::buttonPressed,SDLK_a,1 }, std::make_unique<Move>(peterPepperP1, glm::vec3(-50.0f, 0.0f, 0.0f)));
		 Input::GetInstance().BindKey({ ButtonStates::buttonPressed,SDLK_d,1 }, std::make_unique<Move>(peterPepperP1, glm::vec3(50.0f, 0.0f, 0.0f)));
	 	Input::GetInstance().BindKey({ ButtonStates::buttonPressed,SDLK_w,1 }, std::make_unique<Move>(peterPepperP1, glm::vec3(0.0f, -50.0f, 0.0f)));
	 	Input::GetInstance().BindKey({ ButtonStates::buttonPressed,SDLK_s,1 }, std::make_unique<Move>(peterPepperP1, glm::vec3(0.0f,50.0f,0.0f)));*/
		 Input::GetInstance().BindKey({ ButtonStates::buttonPressed,SDLK_a,1 }, std::make_unique<Move>(peterPepperP1->GetComponent<PeterPepperComponent>(), glm::vec3(-50.0f, 0.0f, 0.0f)));
		 Input::GetInstance().BindKey({ ButtonStates::buttonPressed,SDLK_d,1 }, std::make_unique<Move>(peterPepperP1->GetComponent<PeterPepperComponent>(), glm::vec3(50.0f, 0.0f, 0.0f)));
		Input::GetInstance().BindKey({ ButtonStates::buttonPressed,SDLK_w,1 }, std::make_unique<Move>(peterPepperP1->GetComponent<PeterPepperComponent>(), glm::vec3(0.0f, -50.0f, 0.0f)));
		Input::GetInstance().BindKey({ ButtonStates::buttonPressed,SDLK_s,1 }, std::make_unique<Move>(peterPepperP1->GetComponent<PeterPepperComponent>(), glm::vec3(0.0f,50.0f,0.0f)));
#pragma endregion player1




		 //HealthDisplayObject
		 go = std::make_shared<GameObject>();
		 TextComponent* healthDisplayComp = new TextComponent("Lingua.otf", 20);
		 go->AddComponent(healthDisplayComp);
		 healthDisplayComp->SetText("Lives");
		 go->SetPosition(10, 225);
		 scene.Add(go);
		 //ScoreDisplayObject
		 go = std::make_shared<GameObject>();
		 TextComponent* ScoreDisplayComp = new TextComponent("Lingua.otf", 20);
		 go->AddComponent(ScoreDisplayComp);
		 ScoreDisplayComp->SetText("Scores");
		 go->SetPosition(10, 200);
		 scene.Add(go);

		 Subject* peterPepperSubject = new Subject;
		 peterPepperSubject->AddObserver(new HealthObserver(healthDisplayComp));
		 peterPepperSubject->AddObserver(new ScoreObserver(ScoreDisplayComp));
		 peterPepperP1->SetSubject(peterPepperSubject);
		 scene.Add(peterPepperP1);


#pragma region enemy
		 auto HotDog = std::make_shared<GameObject>();
		 HotDog->AddComponent<BasicEnemyComponent>(new BasicEnemyComponent());
		 HotDog->AddComponent<TextureComponent>(new TextureComponent("HotDog.png"));
		 HotDog->SetPosition(300, 265);
		 HotDog->GetComponent<BasicEnemyComponent>()->SetTarget(peterPepperP1);
		 HotDog->SetTag("Enemy");
		 scene.Add(HotDog);

#pragma endregion enemy


#pragma region player2
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
#pragma endregion player2


#pragma region audio
		 Audio* audioService = Locator::getAudio();
		//Music
		 audioService->LoadMusic("../Data/Sounds/Electric_Light_Orchestra_-_Mr_Blue_Sky.mp3");
		 audioService->SetMusicVolume(5);
		 audioService->PlayMusic();
		//Sound
		 audioService->SetEffectVolume(10);
		 int soundId;
		 soundId =audioService->LoadSound("../Data/Sounds/power_up1.wav");
		 audioService->playSound(soundId);
		 soundId = audioService->LoadSound("../Data/Sounds/book_page_turn.wav");
		 audioService->playSound(soundId);

#pragma endregion audio
		 //std::vector<std::shared_ptr<GameObject>> testo = scene.GetObjectsInWorldWithTag("Ladder");
	}
	
};

int main(int, char* []) {
	//dae::Minigin engine;
	//engine.Run();
	BurgerTime game;
	game.Run();
	
	return 0;

}

void MakeLevel(std::string levelName, Scene& scene)
{
	std::ifstream file("data/" + levelName + ".json");
	 
}