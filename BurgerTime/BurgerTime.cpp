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
#include "IngredientComponent.h"
#include "IngredientPartComponent.h"
#include "ContainerComponent.h"
#include "ValuesComponent.h"
#include "ScoreObserver.h"
#include "HealthObserver.h"
#include <SDL.h>

#include "Commands.h"
#include "Locator.h"
#include <fstream>

#include "LevelManager.h"


using namespace std;
using namespace dae;


class BurgerTime final : public dae::Minigin
{
public:
	 virtual void LoadGame() const override
	{

#pragma region StartScreen
		 auto& startScreen = dae::SceneManager::GetInstance().CreateScene("start");
		

		 auto titel = new GameObject;
		 TextureComponent* burgertimeTitel = new TextureComponent("BurgerTimeTitel.jpg");
		 titel->AddComponent(burgertimeTitel);
		 titel->SetPosition(200, 50);
		 titel->SetScale(1.5, 1.5);
		 startScreen.Add(titel);

		 auto normalMode = new GameObject;
		 TextComponent* normalModeText = new TextComponent("Lingua.otf", 20, SDL_Color{ 255,255,255 });
		 normalModeText->SetText("1 Player");
		 normalMode->AddComponent(normalModeText);
		 normalMode->SetPosition(250, 200);
		 startScreen.Add(normalMode);


		 auto coopMode = new GameObject;
		 TextComponent* coopModeText = new TextComponent("Lingua.otf", 20, SDL_Color{ 255,255,255 });
		 coopModeText->SetText("2 Player");
		 coopMode->AddComponent(coopModeText);
		 coopMode->SetPosition(250, 240);
		 startScreen.Add(coopMode);

		 auto pvpMode = new GameObject;
		 TextComponent* pvpModeText = new TextComponent("Lingua.otf", 20, SDL_Color{ 255,255,255 });
		 pvpModeText->SetText("Player vs Player");
		 pvpMode->AddComponent(pvpModeText);
		 pvpMode->SetPosition(250, 280);
		 startScreen.Add(pvpMode);

		 auto indicator = new GameObject;
		 indicator->AddComponent<TextureComponent>(new TextureComponent("indicator.jpg"));
		 indicator->AddComponent<SelectorComponent>(new SelectorComponent);
		 indicator->SetPosition(210, 200);
		 startScreen.Add(indicator);

		
	 	Input::GetInstance().BindKey({ ButtonStates::buttonUp,SDLK_s,1 }, std::make_unique<Selector>(indicator->GetComponent<SelectorComponent>(), true, 3));
	 	Input::GetInstance().BindKey({ ButtonStates::buttonUp,SDLK_w,1 }, std::make_unique<Selector>(indicator->GetComponent<SelectorComponent>(), false, 3));
		Input::GetInstance().BindKey({ ButtonStates::buttonUp,SDLK_SPACE,1 }, std::make_unique<Continue>(indicator->GetComponent<SelectorComponent>()));
		
#pragma endregion StartScreen

#pragma region HighscoreScene
		 auto& highscoreScene = dae::SceneManager::GetInstance().CreateScene("highscore");
		 auto highscoretitel = new GameObject;
		 //titel->AddComponent<TextComponent>(new TextComponent("Lingua.otf", 30));
		 TextComponent* titelText = new TextComponent("Lingua.otf", 46,SDL_Color{255,255,0});
		 titelText->SetText("Highscores");
		 highscoretitel->AddComponent(titelText);
		 highscoretitel->SetPosition(210, 20);
		 highscoreScene.Add(highscoretitel);
#pragma endregion HighscoreScene

#pragma region GameScene
		 auto& scene = dae::SceneManager::GetInstance().CreateScene("game");

		 std::vector<GameObject*> players;
		 MakeGameBackground(scene);

		 auto manager = new GameObject;
		 manager->AddComponent<LevelManager>(new LevelManager(&scene));
		 scene.Add(manager);

#pragma endregion GameScene
		
		 
#pragma region level1
		/* auto go = new GameObject;
		 go->AddComponent<dae::TextureComponent>(new dae::TextureComponent("Level1.png"));
		 go->SetPosition(100, 100);
		 go->SetScale(1.8f, 1.8f);
		 scene.Add(go);



		 glm::vec3 LadderSize = glm::vec3(9, 28, 1);
		 glm::vec3 PlatformSize = glm::vec3(91, 10, 1);


		 go = new GameObject;
		 go->SetSize(glm::vec3(LadderSize.x, LadderSize.y * 2, LadderSize.z));
		 go->SetPosition(111, 120);
		 go->SetDebugDraw(true);
		 go->SetTag("Ladder");
		 scene.Add(go);

		 go = new GameObject;
		 go->SetSize(glm::vec3(LadderSize.x, LadderSize.y * 5, LadderSize.z));
		 go->SetPosition(111, 245);
		 go->SetDebugDraw(true);
		 go->SetTag("Ladder");
		 scene.Add(go);

		 go = new GameObject;
		 go->SetSize(glm::vec3(LadderSize.x, LadderSize.y * 5, LadderSize.z));
		 go->SetPosition(153, 185);
		 go->SetDebugDraw(true);
		 go->SetTag("Ladder");
		 scene.Add(go);

		 go = new GameObject;
		 go->SetSize(glm::vec3(LadderSize.x,LadderSize.y * 10,LadderSize.z));
		 go->SetPosition(196, 120);
		 go->SetDebugDraw(true);
		 go->SetTag("Ladder");
		 scene.Add(go);

		 go = new GameObject;
		 go->SetSize(glm::vec3(LadderSize.x, LadderSize.y * 3, LadderSize.z));
		 go->SetPosition(241, 120);
		 go->SetDebugDraw(true);
		 go->SetTag("Ladder");
		 scene.Add(go);


		 go = new GameObject;
		 go->SetSize(glm::vec3(LadderSize.x, LadderSize.y * 10, LadderSize.z));
		 go->SetPosition(283, 120);
		 go->SetDebugDraw(true);
		 go->SetTag("Ladder");
		 scene.Add(go);

		 go = new GameObject;
		 go->SetSize(glm::vec3(LadderSize.x, LadderSize.y * 3, LadderSize.z));
		 go->SetPosition(326, 185);
		 go->SetDebugDraw(true);
		 go->SetTag("Ladder");
		 scene.Add(go);

		 go = new GameObject;
		 go->SetSize(glm::vec3(LadderSize.x, LadderSize.y * 10, LadderSize.z));
		 go->SetPosition(369, 120);
		 go->SetDebugDraw(true);
		 go->SetTag("Ladder");
		 scene.Add(go);

		 go = new GameObject;
		 go->SetSize(glm::vec3(LadderSize.x, LadderSize.y * 5, LadderSize.z));
		 go->SetPosition(412, 242);
		 go->SetDebugDraw(true);
		 go->SetTag("Ladder");
		 scene.Add(go);


		 go = new GameObject;
		 go->SetSize(glm::vec3(LadderSize.x, LadderSize.y * 4, LadderSize.z));
		 go->SetPosition(456, 120);
		 go->SetDebugDraw(true);
		 go->SetTag("Ladder");
		 scene.Add(go);

		 go = new GameObject;
		 go->SetSize(glm::vec3(LadderSize.x, LadderSize.y * 3, LadderSize.z));
		 go->SetPosition(456, 300);
		 go->SetDebugDraw(true);
		 go->SetTag("Ladder");
		 scene.Add(go);



	 	go = new GameObject;
		 go->SetSize(glm::vec3(PlatformSize.x *4, PlatformSize.y, PlatformSize.z));
		 go->SetPosition(111, 120);
		 go->SetDebugDraw(true);
		 go->SetTag("Platform");
		 scene.Add(go);

		 go = new GameObject;
		 go->SetSize(glm::vec3(PlatformSize.x, PlatformSize.y, PlatformSize.z));
		 go->SetPosition(111, 165);
		 go->SetDebugDraw(true);
		 go->SetTag("Platform");
		 scene.Add(go);


		 go = new GameObject;
		 go->SetSize(glm::vec3(PlatformSize.x *2, PlatformSize.y, PlatformSize.z));
		 go->SetPosition(283, 165);
		 go->SetDebugDraw(true);
		 go->SetTag("Platform");
		 scene.Add(go);

		 go = new GameObject;
		 go->SetSize(glm::vec3(PlatformSize.x, PlatformSize.y, PlatformSize.z));
		 go->SetPosition(196, 195);
		 go->SetDebugDraw(true);
		 go->SetTag("Platform");
		 scene.Add(go);

		 go = new GameObject;
		 go->SetSize(glm::vec3(PlatformSize.x, PlatformSize.y, PlatformSize.z));
		 go->SetPosition(111, 220);
		 go->SetDebugDraw(true);
		 go->SetTag("Platform");
		 scene.Add(go);

		 go = new GameObject;
		 go->SetSize(glm::vec3(PlatformSize.x, PlatformSize.y, PlatformSize.z));
		 go->SetPosition(369, 220);
		 go->SetDebugDraw(true);
		 go->SetTag("Platform");
		 scene.Add(go);




		 go = new GameObject;
		 go->SetSize(glm::vec3(PlatformSize.x * 2, PlatformSize.y, PlatformSize.z));
		 go->SetPosition(196, 250);
		 go->SetDebugDraw(true);
		 go->SetTag("Platform");
		 scene.Add(go);

		 go = new GameObject;
		 go->SetSize(glm::vec3(PlatformSize.x, PlatformSize.y, PlatformSize.z));
		 go->SetPosition(369, 280);
		 go->SetDebugDraw(true);
		 go->SetTag("Platform");
		 scene.Add(go);

		 go = new GameObject;
		 go->SetSize(glm::vec3(PlatformSize.x * 3, PlatformSize.y, PlatformSize.z));
		 go->SetPosition(111, 310);
		 go->SetDebugDraw(true);
		 go->SetTag("Platform");
		 scene.Add(go);

		 go = new GameObject;
		 go->SetSize(glm::vec3(PlatformSize.x * 4, PlatformSize.y, PlatformSize.z));
		 go->SetPosition(111, 365);
		 go->SetDebugDraw(true);
		 go->SetTag("Platform");
		 scene.Add(go);*/

#pragma endregion level1


#pragma region IngredientContainer
	/*glm::vec3 LadderSize = glm::vec3(9, 28, 1);
	glm::vec3 PlatformSize = glm::vec3(91, 10, 1);

		 float containerWidth{ 65 };
		 float containerHeight{ 70 };
	 	auto go = new GameObject;
		 go->SetSize(glm::vec3(containerWidth, PlatformSize.y, PlatformSize.z));
		 go->SetPosition(125, 455);
		 go->SetDebugDraw(true);
		 go->SetTag("Platform");
		 scene.Add(go);

		 go = new GameObject;
		 go->SetSize(glm::vec3(containerWidth, containerHeight, PlatformSize.z));
		 go->SetPosition(125, 395);
		 go->SetDebugDraw(true);
		 go->SetTag("Container");
		 go->AddComponent<ContainerComponent>(new ContainerComponent());
		 scene.Add(go);


		 go = new GameObject;
		 go->SetSize(glm::vec3(containerWidth, PlatformSize.y, PlatformSize.z));
		 go->SetPosition(212, 455);
		 go->SetDebugDraw(true);
		 go->SetTag("Platform");
		 scene.Add(go);

		 go = new GameObject;
		 go->SetSize(glm::vec3(containerWidth, containerHeight, PlatformSize.z));
		 go->SetPosition(212, 395);
		 go->SetDebugDraw(true);
		 go->SetTag("Container");
		 go->AddComponent<ContainerComponent>(new ContainerComponent());
		 scene.Add(go);


		 go = new GameObject;
		 go->SetSize(glm::vec3(containerWidth, PlatformSize.y, PlatformSize.z));
		 go->SetPosition(298, 455);
		 go->SetDebugDraw(true);
		 go->SetTag("Platform");
		 scene.Add(go);

		 go = new GameObject;
		 go->SetSize(glm::vec3(containerWidth, containerHeight, PlatformSize.z));
		 go->SetPosition(298, 395);
		 go->SetDebugDraw(true);
		 go->SetTag("Container");
		 go->AddComponent<ContainerComponent>(new ContainerComponent());
		 scene.Add(go);

		 go = new GameObject;
		 go->SetSize(glm::vec3(containerWidth, PlatformSize.y, PlatformSize.z));
		 go->SetPosition(384, 455);
		 go->SetDebugDraw(true);
		 go->SetTag("Platform");
		 scene.Add(go);

		 go = new GameObject;
		 go->SetSize(glm::vec3(containerWidth, containerHeight, PlatformSize.z));
		 go->SetPosition(384, 395);
		 go->SetDebugDraw(true);
		 go->SetTag("Container");
		 go->AddComponent<ContainerComponent>(new ContainerComponent());
		 scene.Add(go);*/
#pragma endregion IngredientContainer

#pragma region player1
		 //PeterPepper Player1
		 auto peterPepperP1 = new GameObject;
		 peterPepperP1->AddComponent<PeterPepperComponent>(new PeterPepperComponent());
		 peterPepperP1->AddComponent<TextureComponent>(new TextureComponent("PeterPepperCrop.png"));
		 peterPepperP1->AddComponent<ValuesComponent>(new ValuesComponent());
		 peterPepperP1->SetPosition(190, 250);
	 	 peterPepperP1->SetTag("Player");
		 //commands
		
		 Input::GetInstance().BindKey({ ButtonStates::buttonPressed,SDLK_a,1 }, std::make_unique<Move>(peterPepperP1->GetComponent<PeterPepperComponent>(), glm::vec3(-80.0f, 0.0f, 0.0f)));
		 Input::GetInstance().BindKey({ ButtonStates::buttonPressed,SDLK_d,1 }, std::make_unique<Move>(peterPepperP1->GetComponent<PeterPepperComponent>(), glm::vec3(80.0f, 0.0f, 0.0f)));
		 Input::GetInstance().BindKey({ ButtonStates::buttonPressed,SDLK_w,1 }, std::make_unique<Move>(peterPepperP1->GetComponent<PeterPepperComponent>(), glm::vec3(0.0f, -80.0f, 0.0f)));
		 Input::GetInstance().BindKey({ ButtonStates::buttonPressed,SDLK_s,1 }, std::make_unique<Move>(peterPepperP1->GetComponent<PeterPepperComponent>(), glm::vec3(0.0f,80.0f,0.0f)));

		 players.push_back(peterPepperP1);
#pragma endregion player1



#pragma region displays
		 //HealthDisplayObject
		 auto go = new GameObject;
		 TextComponent* healthDisplayComp = new TextComponent("Lingua.otf", 20);
		 go->AddComponent(healthDisplayComp);
		 healthDisplayComp->SetText("Lives");
		 go->SetPosition(10, 225);
		 scene.Add(go);
		 //ScoreDisplayObject
		 go = new GameObject;
		 TextComponent* ScoreDisplayComp = new TextComponent("Lingua.otf", 20);
		 go->AddComponent(ScoreDisplayComp);
		 ScoreDisplayComp->SetText("Scores");
		 go->SetPosition(10, 200);
		 scene.Add(go);

		 Subject* ValuesSubject = new Subject;
		 ValuesSubject->AddObserver(new HealthObserver(healthDisplayComp));
		 ValuesSubject->AddObserver(new ScoreObserver(ScoreDisplayComp));
		 peterPepperP1->GetComponent<ValuesComponent>()->SetSubject(ValuesSubject);

		
		 scene.Add(peterPepperP1);
#pragma endregion displays


#pragma region ingredients

		 MakeIngredient(glm::vec3(130, 165, 0), IngredientType::Bun, scene, false,players);
		 MakeIngredient(glm::vec3(130, 220, 0), IngredientType::Lettuce, scene, false, players);
		 MakeIngredient(glm::vec3(130, 305, 0), IngredientType::Patty, scene, false, players);
		 MakeIngredient(glm::vec3(130, 360, 0), IngredientType::BunBottom, scene, false, players);


		MakeIngredient(glm::vec3(215, 115, 0), IngredientType::Bun, scene, false, players);
		MakeIngredient(glm::vec3(215, 250, 0), IngredientType::Lettuce, scene, false, players);
		MakeIngredient(glm::vec3(215, 305, 0), IngredientType::Patty, scene, false, players);
		MakeIngredient(glm::vec3(215, 360, 0), IngredientType::BunBottom, scene, false, players);

		MakeIngredient(glm::vec3(300, 115, 0), IngredientType::Bun, scene, false, players);
		MakeIngredient(glm::vec3(300, 165, 0), IngredientType::Lettuce, scene, false, players);
		MakeIngredient(glm::vec3(300, 250, 0), IngredientType::Patty, scene, false, players);
		MakeIngredient(glm::vec3(300, 360, 0), IngredientType::BunBottom, scene, false, players);

		MakeIngredient(glm::vec3(387, 115, 0), IngredientType::Bun, scene, false, players);
		MakeIngredient(glm::vec3(387, 165, 0), IngredientType::Lettuce, scene, false, players);
		MakeIngredient(glm::vec3(387, 220, 0), IngredientType::Patty, scene, false, players);
		MakeIngredient(glm::vec3(387, 280, 0), IngredientType::BunBottom, scene, false, players);

		

#pragma endregion ingedients

#pragma region enemy
		auto HotDog = new GameObject;
		 HotDog->AddComponent<BasicEnemyComponent>(new BasicEnemyComponent(EnemyType::Hotdog));
		 HotDog->AddComponent<TextureComponent>(new TextureComponent("HotDog.png"));
		 HotDog->SetPosition(283, 250);
		 HotDog->GetComponent<BasicEnemyComponent>()->SetTarget(peterPepperP1);
		 HotDog->SetTag("Enemy");
		 scene.Add(HotDog);

	 	HotDog = new GameObject;
		 HotDog->AddComponent<BasicEnemyComponent>(new BasicEnemyComponent(EnemyType::Hotdog));
		 HotDog->AddComponent<TextureComponent>(new TextureComponent("HotDog.png"));
		 HotDog->SetPosition(300, 250);
		 HotDog->GetComponent<BasicEnemyComponent>()->SetTarget(peterPepperP1);
		 HotDog->SetTag("Enemy");
		 scene.Add(HotDog);

		 HotDog = new GameObject;
		 HotDog->AddComponent<BasicEnemyComponent>(new BasicEnemyComponent(EnemyType::Hotdog));
		 HotDog->AddComponent<TextureComponent>(new TextureComponent("HotDog.png"));
		 HotDog->SetPosition(320, 250);
		 HotDog->GetComponent<BasicEnemyComponent>()->SetTarget(peterPepperP1);
		 HotDog->SetTag("Enemy");
		 scene.Add(HotDog);

		  HotDog = new GameObject;
		 HotDog->AddComponent<BasicEnemyComponent>(new BasicEnemyComponent(EnemyType::Hotdog));
		 HotDog->AddComponent<TextureComponent>(new TextureComponent("HotDog.png"));
		 HotDog->SetPosition(340, 250);
		 HotDog->GetComponent<BasicEnemyComponent>()->SetTarget(peterPepperP1);
		 HotDog->SetTag("Enemy");
		 scene.Add(HotDog);

		  HotDog = new GameObject;
		 HotDog->AddComponent<BasicEnemyComponent>(new BasicEnemyComponent(EnemyType::Hotdog));
		 HotDog->AddComponent<TextureComponent>(new TextureComponent("HotDog.png"));
		 HotDog->SetPosition(360, 250);
		 HotDog->GetComponent<BasicEnemyComponent>()->SetTarget(peterPepperP1);
		 HotDog->SetTag("Enemy");
		 scene.Add(HotDog);

		  HotDog = new GameObject;
		 HotDog->AddComponent<BasicEnemyComponent>(new BasicEnemyComponent(EnemyType::Hotdog));
		 HotDog->AddComponent<TextureComponent>(new TextureComponent("HotDog.png"));
		 HotDog->SetPosition(380, 250);
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
		// Audio* audioService = Locator::getAudio();
		////Music
		// audioService->LoadMusic("../Data/Sounds/Electric_Light_Orchestra_-_Mr_Blue_Sky.mp3");
		// audioService->SetMusicVolume(5);
		// audioService->PlayMusic();
		////Sound
		// audioService->SetEffectVolume(10);
		// int soundId;
		// soundId =audioService->LoadSound("../Data/Sounds/power_up1.wav");
		// audioService->playSound(soundId);
		// soundId = audioService->LoadSound("../Data/Sounds/book_page_turn.wav");
		// audioService->playSound(soundId);

#pragma endregion audio

		 SceneManager::GetInstance().SetCurrentScene("start");
		 
	}

private:
	


	void MakeGameBackground(Scene& scene) const
	{
		//Background
		auto go = new GameObject;
		go->AddComponent<dae::TextureComponent>(new dae::TextureComponent("backgroundBlack.png"));
		scene.Add(go);


		////FPS COUNTER
		go = new GameObject;
		go->AddComponent<TextComponent>(new TextComponent("Lingua.otf", 20, SDL_Color{ 255,255,0 }));
		go->GetComponent<TextComponent>()->SetText("FPS");
		go->AddComponent<FPSComponent>(new FPSComponent());
		scene.Add(go);

		////SCORES
		go = new GameObject;
		go->AddComponent<TextComponent>(new TextComponent("Lingua.otf", 30, SDL_Color{ 255,0,0 }));
		go->GetComponent<TextComponent>()->SetText("1UP");
		go->SetPosition(80, 0);
		scene.Add(go);

		go = new GameObject;
		go->AddComponent<TextComponent>(new TextComponent("Lingua.otf", 30, SDL_Color{ 255,0,0 }));
		go->GetComponent<TextComponent>()->SetText("HI-SCORE");
		go->SetPosition(180, 0);
		scene.Add(go);


		go = new GameObject;
		go->AddComponent<TextComponent>(new TextComponent("Lingua.otf", 18, SDL_Color{ 0,255,0 }));
		go->GetComponent<TextComponent>()->SetText("PEPPER");
		go->SetPosition(500, 0);
		scene.Add(go);


		go = new GameObject;
		go->AddComponent<TextComponent>(new TextComponent("Lingua.otf", 26));
		go->GetComponent<TextComponent>()->SetText("0000");
		go->SetPosition(80, 30);
		scene.Add(go);

		go = new GameObject;
		go->AddComponent<TextComponent>(new TextComponent("Lingua.otf", 26));
		go->GetComponent<TextComponent>()->SetText("0000");
		go->SetPosition(180, 30);
		scene.Add(go);


		go = new GameObject;
		go->AddComponent<TextComponent>(new TextComponent("Lingua.otf", 26));
		go->GetComponent<TextComponent>()->SetText("0");
		go->SetPosition(500, 30);
		scene.Add(go);
	}

	void MakeIngredient(glm::vec3 pos, IngredientType ingredientType, Scene& scene, bool debugDraw, std::vector<GameObject*>& players) const
	{
		auto totalIngredient = new GameObject;
		auto part1 = new GameObject;
		auto part2 = new GameObject;
		auto part3 = new GameObject;
		auto part4 = new GameObject;

		totalIngredient->AddChild(part1);
		totalIngredient->AddChild(part2);
		totalIngredient->AddChild(part3);
		totalIngredient->AddChild(part4);

		for (int i{}; i < totalIngredient->GetChildCount(); i++)
		{
			switch (ingredientType)
			{
			case IngredientType::Bun:
				if (i == 0)
				{
					totalIngredient->GetChildAt(i)->AddComponent<dae::TextureComponent>(new dae::TextureComponent("Ingredients/BunL.png"));

				}
				else if (i == totalIngredient->GetChildCount() - 1)
				{
					totalIngredient->GetChildAt(i)->AddComponent<dae::TextureComponent>(new dae::TextureComponent("Ingredients/BunR.png"));
				}
				else
				{
					totalIngredient->GetChildAt(i)->AddComponent<dae::TextureComponent>(new dae::TextureComponent("Ingredients/Bun.png"));
				}
				break;
			case IngredientType::Cheese:
				if (i == 0)
				{
					totalIngredient->GetChildAt(i)->AddComponent<dae::TextureComponent>(new dae::TextureComponent("Ingredients/CheeseL.png"));

				}
				else if (i == totalIngredient->GetChildCount() - 1)
				{
					totalIngredient->GetChildAt(i)->AddComponent<dae::TextureComponent>(new dae::TextureComponent("Ingredients/CheeseR.png"));
				}
				else
				{
					totalIngredient->GetChildAt(i)->AddComponent<dae::TextureComponent>(new dae::TextureComponent("Ingredients/Cheese.png"));
				}
				break;
			case IngredientType::Lettuce:
				if (i == 0)
				{
					totalIngredient->GetChildAt(i)->AddComponent<dae::TextureComponent>(new dae::TextureComponent("Ingredients/LettuceL.png"));

				}
				else if (i == totalIngredient->GetChildCount() - 1)
				{
					totalIngredient->GetChildAt(i)->AddComponent<dae::TextureComponent>(new dae::TextureComponent("Ingredients/LettuceR.png"));
				}
				else
				{
					totalIngredient->GetChildAt(i)->AddComponent<dae::TextureComponent>(new dae::TextureComponent("Ingredients/Lettuce.png"));
				}
				break;
			case IngredientType::Tomato:
				if (i == 0)
				{
					totalIngredient->GetChildAt(i)->AddComponent<dae::TextureComponent>(new dae::TextureComponent("Ingredients/TomatoL.png"));

				}
				else if (i == totalIngredient->GetChildCount() - 1)
				{
					totalIngredient->GetChildAt(i)->AddComponent<dae::TextureComponent>(new dae::TextureComponent("Ingredients/TomatoR.png"));
				}
				else
				{
					totalIngredient->GetChildAt(i)->AddComponent<dae::TextureComponent>(new dae::TextureComponent("Ingredients/Tomato.png"));
				}
				break;
			case IngredientType::Patty:
				if (i == 0)
				{
					totalIngredient->GetChildAt(i)->AddComponent<dae::TextureComponent>(new dae::TextureComponent("Ingredients/PattyL.png"));

				}
				else if (i == totalIngredient->GetChildCount() - 1)
				{
					totalIngredient->GetChildAt(i)->AddComponent<dae::TextureComponent>(new dae::TextureComponent("Ingredients/PattyR.png"));
				}
				else
				{
					totalIngredient->GetChildAt(i)->AddComponent<dae::TextureComponent>(new dae::TextureComponent("Ingredients/Patty.png"));
				}
				break;
			case IngredientType::BunBottom:
				if (i == 0)
				{
					totalIngredient->GetChildAt(i)->AddComponent<dae::TextureComponent>(new dae::TextureComponent("Ingredients/BunBotL.png"));

				}
				else if (i == totalIngredient->GetChildCount() - 1)
				{
					totalIngredient->GetChildAt(i)->AddComponent<dae::TextureComponent>(new dae::TextureComponent("Ingredients/BunBotR.png"));
				}
				else
				{
					totalIngredient->GetChildAt(i)->AddComponent<dae::TextureComponent>(new dae::TextureComponent("Ingredients/BunBot.png"));
				}
				break;
			default:
				std::cout << "noType";
				break;
			}

			totalIngredient->GetChildAt(i)->AddComponent<dae::IngredientPartComponent>(new dae::IngredientPartComponent());

		}



		part1->SetPosition(0, 0);
		part2->SetPosition(part1->GetSize().x, 0);
		part3->SetPosition(part1->GetSize().x * 2, 0);
		part4->SetPosition(part1->GetSize().x * 3, 0);


		totalIngredient->SetDebugDraw(debugDraw);
		part1->SetDebugDraw(debugDraw);
		part2->SetDebugDraw(debugDraw);
		part3->SetDebugDraw(debugDraw);
		part4->SetDebugDraw(debugDraw);

		totalIngredient->SetScale(1.8f, 1.8f);
		totalIngredient->SetSize(glm::vec3(part1->GetSize().x * 4, part1->GetSize().y, 0));
		totalIngredient->SetTag("Ingredient");

		totalIngredient->SetPosition(pos.x, pos.y);
		totalIngredient->AddComponent<IngredientComponent>(new IngredientComponent);
		totalIngredient->GetComponent<IngredientComponent>()->SetPlayers(players);
		scene.Add(totalIngredient);
	}

};

int main(int, char* []) {
	
	BurgerTime game;
	game.Run();
	
	return 0;

}

//void MakeLevel(std::string levelName, Scene& scene)
//{
//	std::ifstream file("data/" + levelName + ".json");
//	 
//}
//
//void MakeGameBackground(Scene& scene)
//{
//	//Background
//	auto go = new GameObject;
//	go->AddComponent<dae::TextureComponent>(new dae::TextureComponent("backgroundBlack.png"));
//	scene.Add(go);
//
//
//	////FPS COUNTER
//	go = new GameObject;
//	go->AddComponent<TextComponent>(new TextComponent("Lingua.otf", 20, SDL_Color{ 255,255,0 }));
//	go->GetComponent<TextComponent>()->SetText("FPS");
//	go->AddComponent<FPSComponent>(new FPSComponent());
//	scene.Add(go);
//
//	////SCORES
//	go = new GameObject;
//	go->AddComponent<TextComponent>(new TextComponent("Lingua.otf", 30, SDL_Color{ 255,0,0 }));
//	go->GetComponent<TextComponent>()->SetText("1UP");
//	go->SetPosition(80, 0);
//	scene.Add(go);
//
//	go = new GameObject;
//	go->AddComponent<TextComponent>(new TextComponent("Lingua.otf", 30, SDL_Color{ 255,0,0 }));
//	go->GetComponent<TextComponent>()->SetText("HI-SCORE");
//	go->SetPosition(180, 0);
//	scene.Add(go);
//
//
//	go = new GameObject;
//	go->AddComponent<TextComponent>(new TextComponent("Lingua.otf", 18, SDL_Color{ 0,255,0 }));
//	go->GetComponent<TextComponent>()->SetText("PEPPER");
//	go->SetPosition(500, 0);
//	scene.Add(go);
//
//
//	go = new GameObject;
//	go->AddComponent<TextComponent>(new TextComponent("Lingua.otf", 26));
//	go->GetComponent<TextComponent>()->SetText("0000");
//	go->SetPosition(80, 30);
//	scene.Add(go);
//
//	go = new GameObject;
//	go->AddComponent<TextComponent>(new TextComponent("Lingua.otf", 26));
//	go->GetComponent<TextComponent>()->SetText("0000");
//	go->SetPosition(180, 30);
//	scene.Add(go);
//
//
//	go = new GameObject;
//	go->AddComponent<TextComponent>(new TextComponent("Lingua.otf", 26));
//	go->GetComponent<TextComponent>()->SetText("0");
//	go->SetPosition(500, 30);
//	scene.Add(go);
//}
//
//void MakeIngredient(glm::vec3 pos, IngredientType ingredientType,Scene& scene,bool debugDraw,std::vector<GameObject*>& players)
//{
//	auto totalIngredient = new GameObject;
//	auto part1 = new GameObject;
//	auto part2 = new GameObject;
//	auto part3 = new GameObject;
//	auto part4 = new GameObject;
//
//	totalIngredient->AddChild(part1);
//	totalIngredient->AddChild(part2);
//	totalIngredient->AddChild(part3);
//	totalIngredient->AddChild(part4);
//
//	for(int i{}; i < totalIngredient->GetChildCount();i++)
//	{
//		switch (ingredientType)
//		{
//		case IngredientType::Bun:
//			if(i == 0)
//			{
//				totalIngredient->GetChildAt(i)->AddComponent<dae::TextureComponent>(new dae::TextureComponent("Ingredients/BunL.png"));
//
//			} else if(i == totalIngredient->GetChildCount() -1)
//			{
//				totalIngredient->GetChildAt(i)->AddComponent<dae::TextureComponent>(new dae::TextureComponent("Ingredients/BunR.png"));
//			} else
//			{
//				totalIngredient->GetChildAt(i)->AddComponent<dae::TextureComponent>(new dae::TextureComponent("Ingredients/Bun.png"));
//			}
//			break;
//		case IngredientType::Cheese:
//			if (i == 0)
//			{
//				totalIngredient->GetChildAt(i)->AddComponent<dae::TextureComponent>(new dae::TextureComponent("Ingredients/CheeseL.png"));
//
//			}
//			else if (i == totalIngredient->GetChildCount() - 1)
//			{
//				totalIngredient->GetChildAt(i)->AddComponent<dae::TextureComponent>(new dae::TextureComponent("Ingredients/CheeseR.png"));
//			}
//			else
//			{
//				totalIngredient->GetChildAt(i)->AddComponent<dae::TextureComponent>(new dae::TextureComponent("Ingredients/Cheese.png"));
//			}
//			break;
//		case IngredientType::Lettuce:
//			if (i == 0)
//			{
//				totalIngredient->GetChildAt(i)->AddComponent<dae::TextureComponent>(new dae::TextureComponent("Ingredients/LettuceL.png"));
//
//			}
//			else if (i == totalIngredient->GetChildCount() - 1)
//			{
//				totalIngredient->GetChildAt(i)->AddComponent<dae::TextureComponent>(new dae::TextureComponent("Ingredients/LettuceR.png"));
//			}
//			else
//			{
//				totalIngredient->GetChildAt(i)->AddComponent<dae::TextureComponent>(new dae::TextureComponent("Ingredients/Lettuce.png"));
//			}
//			break;
//		case IngredientType::Tomato:
//			if (i == 0)
//			{
//				totalIngredient->GetChildAt(i)->AddComponent<dae::TextureComponent>(new dae::TextureComponent("Ingredients/TomatoL.png"));
//
//			}
//			else if (i == totalIngredient->GetChildCount() - 1)
//			{
//				totalIngredient->GetChildAt(i)->AddComponent<dae::TextureComponent>(new dae::TextureComponent("Ingredients/TomatoR.png"));
//			}
//			else
//			{
//				totalIngredient->GetChildAt(i)->AddComponent<dae::TextureComponent>(new dae::TextureComponent("Ingredients/Tomato.png"));
//			}
//			break;
//		case IngredientType::Patty:
//			if (i == 0)
//			{
//				totalIngredient->GetChildAt(i)->AddComponent<dae::TextureComponent>(new dae::TextureComponent("Ingredients/PattyL.png"));
//
//			}
//			else if (i == totalIngredient->GetChildCount() - 1)
//			{
//				totalIngredient->GetChildAt(i)->AddComponent<dae::TextureComponent>(new dae::TextureComponent("Ingredients/PattyR.png"));
//			}
//			else
//			{
//				totalIngredient->GetChildAt(i)->AddComponent<dae::TextureComponent>(new dae::TextureComponent("Ingredients/Patty.png"));
//			}
//			break;
//		case IngredientType::BunBottom:
//			if (i == 0)
//			{
//				totalIngredient->GetChildAt(i)->AddComponent<dae::TextureComponent>(new dae::TextureComponent("Ingredients/BunBotL.png"));
//
//			}
//			else if (i == totalIngredient->GetChildCount() - 1)
//			{
//				totalIngredient->GetChildAt(i)->AddComponent<dae::TextureComponent>(new dae::TextureComponent("Ingredients/BunBotR.png"));
//			}
//			else
//			{
//				totalIngredient->GetChildAt(i)->AddComponent<dae::TextureComponent>(new dae::TextureComponent("Ingredients/BunBot.png"));
//			}
//			break;
//		default:
//			std::cout << "noType";
//			break;
//		}
//
//		totalIngredient->GetChildAt(i)->AddComponent<dae::IngredientPartComponent>(new dae::IngredientPartComponent());
//
//	}
//
//
//
//	part1->SetPosition(0, 0);
//	part2->SetPosition(part1->GetSize().x, 0);
//	part3->SetPosition(part1->GetSize().x * 2, 0);
//	part4->SetPosition(part1->GetSize().x * 3, 0);
//
//
//	totalIngredient->SetDebugDraw(debugDraw);
//	part1->SetDebugDraw(debugDraw);
//	part2->SetDebugDraw(debugDraw);
//	part3->SetDebugDraw(debugDraw);
//	part4->SetDebugDraw(debugDraw);
//
//	totalIngredient->SetScale(1.8f, 1.8f);
//	totalIngredient->SetSize(glm::vec3(part1->GetSize().x * 4, part1->GetSize().y, 0));
//	totalIngredient->SetTag("Ingredient");
//
//	totalIngredient->SetPosition(pos.x, pos.y);
//	totalIngredient->AddComponent<IngredientComponent>(new IngredientComponent);
//	totalIngredient->GetComponent<IngredientComponent>()->SetPlayers(players);
//	scene.Add(totalIngredient);
//}
