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
#include "ValuesComponent.h"
#include "ScoreObserver.h"
#include "HealthObserver.h"
#include <SDL.h>

#include "Commands.h"
#include "Locator.h"
#include <fstream>

#include "LevelManager.h"
#include "SceneChanger.h"


using namespace std;
using namespace dae;


class BurgerTime final : public dae::Minigin
{
public:
	 virtual void LoadGame() const override
	{
		 std::vector<GameObject*> controlObjects;
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
		 indicator->SetTag("Indicator");
		 startScreen.Add(indicator);

		 controlObjects.push_back(indicator);
		
	/* 	Input::GetInstance().BindKey({ ButtonStates::buttonUp,SDLK_s,1 }, std::make_unique<Selector>(indicator->GetComponent<SelectorComponent>(), true, 3));
	 	Input::GetInstance().BindKey({ ButtonStates::buttonUp,SDLK_w,1 }, std::make_unique<Selector>(indicator->GetComponent<SelectorComponent>(), false, 3));
		Input::GetInstance().BindKey({ ButtonStates::buttonUp,SDLK_SPACE,1 }, std::make_unique<Continue>(indicator->GetComponent<SelectorComponent>()));*/
		
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
		 std::vector<GameObject*> levelBackgrounds;
		 std::vector<GameObject*> playerEnemy;
		 MakeGameBackground(scene);

		 //Add all the levelbackgrounds
		 auto lvl1 = new GameObject;
		 lvl1->AddComponent<dae::TextureComponent>(new dae::TextureComponent("Level1.png"));
		 lvl1->SetPosition(100, 100);
		 lvl1->SetScale(1.8f, 1.8f);
		 levelBackgrounds.push_back(lvl1);
		 scene.Add(lvl1);

		 auto lvl2 = new GameObject;
		 lvl2->AddComponent<dae::TextureComponent>(new dae::TextureComponent("Level2.png"));
		 lvl2->SetPosition(100, 100);
		 lvl2->SetScale(1.8f, 1.8f);
		 levelBackgrounds.push_back(lvl2);
		 scene.Add(lvl2);

		 auto lvl3 = new GameObject;
		 lvl3->AddComponent<dae::TextureComponent>(new dae::TextureComponent("Level3.png"));
		 lvl3->SetPosition(100, 100);
		 lvl3->SetScale(1.8f, 1.8f);
		 levelBackgrounds.push_back(lvl3);
		 scene.Add(lvl3);


		 //Make players for levelManager
		//Set sames valuesComponent for every player
		 auto peterPepperP1 = new GameObject;

		 peterPepperP1->AddComponent<SpriteComponent>(new SpriteComponent("PeterPepperSpriteTrans.png",15,11));
		 peterPepperP1->AddComponent<PeterPepperComponent>(new PeterPepperComponent());
		 peterPepperP1->GetComponent<PeterPepperComponent>()->SetSpriteComp(peterPepperP1->GetComponent<SpriteComponent>());
		 //peterPepperP1->AddComponent<TextureComponent>(new TextureComponent("PeterPepperCrop.png"));
		 peterPepperP1->AddComponent<ValuesComponent>(new ValuesComponent());
		 peterPepperP1->SetScale(1.5f, 1.5f);
		 //peterPepperP1->SetPosition(190, 250);
		 peterPepperP1->SetTag("Player");

		

		 players.push_back(peterPepperP1);
		 controlObjects.push_back(peterPepperP1);

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


		//Make LevelManager
		 auto manager = new GameObject;
		 manager->AddComponent<LevelManager>(new LevelManager(&scene,players, playerEnemy, levelBackgrounds));
		 scene.Add(manager);

		//Do after rest otherwise invis
		 scene.Add(peterPepperP1);
#pragma endregion GameScene
		

#pragma region CoopScene
		 auto& coopScene = dae::SceneManager::GetInstance().CreateScene("coop");

		 std::vector<GameObject*> playerEnemyCoop;
		 std::vector<GameObject*> playersCoop;
		 MakeGameBackground(coopScene);

		 std::vector<GameObject*> levelBackgroundsCoop;
		 auto lvl1coop = new GameObject;
		 lvl1coop->AddComponent<dae::TextureComponent>(new dae::TextureComponent("Level1.png"));
		 lvl1coop->SetPosition(100, 100);
		 lvl1coop->SetScale(1.8f, 1.8f);
		 levelBackgroundsCoop.push_back(lvl1coop);
		 coopScene.Add(lvl1coop);

		 auto lvl2coop = new GameObject;
		 lvl2coop->AddComponent<dae::TextureComponent>(new dae::TextureComponent("Level2.png"));
		 lvl2coop->SetPosition(100, 100);
		 lvl2coop->SetScale(1.8f, 1.8f);
		 levelBackgroundsCoop.push_back(lvl2coop);
		 coopScene.Add(lvl2coop);

		 auto lvl3coop = new GameObject;
		 lvl3coop->AddComponent<dae::TextureComponent>(new dae::TextureComponent("Level3.png"));
		 lvl3coop->SetPosition(100, 100);
		 lvl3coop->SetScale(1.8f, 1.8f);
		 levelBackgroundsCoop.push_back(lvl3coop);
		 coopScene.Add(lvl3coop);

		
		auto peterPepperPlayer1 = new GameObject;
		peterPepperPlayer1->AddComponent<SpriteComponent>(new SpriteComponent("PeterPepperSpriteTrans.png", 15, 11));
		peterPepperPlayer1->AddComponent<PeterPepperComponent>(new PeterPepperComponent());
		peterPepperPlayer1->GetComponent<PeterPepperComponent>()->SetSpriteComp(peterPepperPlayer1->GetComponent<SpriteComponent>());
		 peterPepperPlayer1->AddComponent<ValuesComponent>(new ValuesComponent);
		 peterPepperPlayer1->SetScale(1.5f, 1.5f);
		 peterPepperPlayer1->SetTag("Player");

		 auto peterPepperPlayer2 = new GameObject;
		 peterPepperPlayer2->AddComponent<SpriteComponent>(new SpriteComponent("PeterPepperSpriteTrans.png", 15, 11));
		 peterPepperPlayer2->AddComponent<PeterPepperComponent>(new PeterPepperComponent());
		 peterPepperPlayer2->GetComponent<PeterPepperComponent>()->SetSpriteComp(peterPepperPlayer2->GetComponent<SpriteComponent>());
		 peterPepperPlayer2->AddComponent<ValuesComponent>(new ValuesComponent);
		 //peterPepperPlayer2->AddComponent(valuesComp);
		 //peterPepperP1->SetPosition(190, 250);
		 peterPepperPlayer2->SetScale(1.5f, 1.5f);
		 peterPepperPlayer2->SetTag("Player");

		 playersCoop.push_back(peterPepperPlayer1);
		 controlObjects.push_back(peterPepperPlayer1);

		 playersCoop.push_back(peterPepperPlayer2);
		 controlObjects.push_back(peterPepperPlayer2);

		 //HealthDisplayObject
		 auto healthCoop = new GameObject;
		 TextComponent* healthDisplayCompCoop = new TextComponent("Lingua.otf", 20);
		 healthCoop->AddComponent(healthDisplayCompCoop);
		 healthDisplayCompCoop->SetText("Lives");
		 healthCoop->SetPosition(10, 225);
		 coopScene.Add(healthCoop);
		 //ScoreDisplayObject
		 auto scoreCoop = new GameObject;
		 TextComponent* ScoreDisplayCompCoop = new TextComponent("Lingua.otf", 20);
		 scoreCoop->AddComponent(ScoreDisplayCompCoop);
		 ScoreDisplayCompCoop->SetText("Scores");
		 scoreCoop->SetPosition(10, 200);
		 coopScene.Add(scoreCoop);


		 Subject* ValuesSubjectCoopP1 = new Subject;
		 Subject* ValuesSubjectCoopP2 = new Subject;
		 ValuesSubjectCoopP1->AddObserver(new HealthObserver(healthDisplayCompCoop));
		 ValuesSubjectCoopP1->AddObserver(new ScoreObserver(ScoreDisplayCompCoop));
		 ValuesSubjectCoopP2->AddObserver(new HealthObserver(healthDisplayCompCoop));
		 ValuesSubjectCoopP2->AddObserver(new ScoreObserver(ScoreDisplayCompCoop));
		 peterPepperPlayer1->GetComponent<ValuesComponent>()->SetSubject(ValuesSubjectCoopP1);
		 peterPepperPlayer2->GetComponent<ValuesComponent>()->SetSubject(ValuesSubjectCoopP2);

		 //Make LevelManager
		 auto managerCoop = new GameObject;
		 managerCoop->AddComponent<LevelManager>(new LevelManager(&coopScene, playersCoop, playerEnemyCoop, levelBackgroundsCoop));
		 coopScene.Add(managerCoop);

		 //Do after rest otherwise invis
		 coopScene.Add(peterPepperPlayer1);
		 coopScene.Add(peterPepperPlayer2);
#pragma endregion CoopScene


#pragma region PvpScene
		 auto& pvpScene = dae::SceneManager::GetInstance().CreateScene("pvp");

		 std::vector<GameObject*> playerEnemyPvp;
		 std::vector<GameObject*> playersPvp;
		/* std::vector<GameObject*> playerEnemyPvp;*/
		 MakeGameBackground(pvpScene);

		 std::vector<GameObject*> levelBackgroundsPvp;
		 auto lvl1Pvp = new GameObject;
		 lvl1Pvp->AddComponent<dae::TextureComponent>(new dae::TextureComponent("Level1.png"));
		 lvl1Pvp->SetPosition(100, 100);
		 lvl1Pvp->SetScale(1.8f, 1.8f);
		 levelBackgroundsPvp.push_back(lvl1Pvp);
		 pvpScene.Add(lvl1Pvp);

		 auto lvl2Pvp = new GameObject;
		 lvl2Pvp->AddComponent<dae::TextureComponent>(new dae::TextureComponent("Level2.png"));
		 lvl2Pvp->SetPosition(100, 100);
		 lvl2Pvp->SetScale(1.8f, 1.8f);
		 levelBackgroundsPvp.push_back(lvl2Pvp);
		 pvpScene.Add(lvl2Pvp);

		 auto lvl3Pvp = new GameObject;
		 lvl3Pvp->AddComponent<dae::TextureComponent>(new dae::TextureComponent("Level3.png"));
		 lvl3Pvp->SetPosition(100, 100);
		 lvl3Pvp->SetScale(1.8f, 1.8f);
		 levelBackgroundsPvp.push_back(lvl3Pvp);
		 pvpScene.Add(lvl3Pvp);

		 /*pvpScene.Add(lvl1coop);
		 pvpScene.Add(lvl2coop);
		 pvpScene.Add(lvl3coop);*/
		/* pvpScene.Add(lvl1);
		 pvpScene.Add(lvl2);
		 pvpScene.Add(lvl3);*/
		 //Make players for levelManager
		//Set sames valuesComponent for every player
		 ValuesComponent* valuesCompPvp = new ValuesComponent();
		 auto peterPepperPvp = new GameObject;
		 peterPepperPvp->AddComponent<SpriteComponent>(new SpriteComponent("PeterPepperSpriteTrans.png", 15, 11));
		 peterPepperPvp->AddComponent<PeterPepperComponent>(new PeterPepperComponent());
		 peterPepperPvp->GetComponent<PeterPepperComponent>()->SetSpriteComp(peterPepperPvp->GetComponent<SpriteComponent>());
		 peterPepperPvp->AddComponent(valuesCompPvp);
		 //peterPepperP1->SetPosition(190, 250);
		 peterPepperPvp->SetScale(1.5f, 1.5f);
		 peterPepperPvp->SetTag("Player");

		 auto hotdogPvp = new GameObject;
		 hotdogPvp->AddComponent<SpriteComponent>(new SpriteComponent("PeterPepperSpriteTrans.png", 15, 11));
		 hotdogPvp->AddComponent<BasicEnemyComponent>(new BasicEnemyComponent(EEnemyType::Hotdog,true));
		 //hotdogPvp->AddComponent<TextureComponent>(new TextureComponent("HotDog.png"));
		 hotdogPvp->GetComponent<BasicEnemyComponent>()->SetSpriteComp(hotdogPvp->GetComponent<SpriteComponent>());
		 hotdogPvp->SetTag("Enemy");

		 playersPvp.push_back(peterPepperPvp);
		 controlObjects.push_back(peterPepperPvp);

		 //playersPvp.push_back(hotdogPvp);
		 playerEnemyPvp.push_back(hotdogPvp);
		 controlObjects.push_back(hotdogPvp);

		 //HealthDisplayObject
		 auto healthPvp = new GameObject;
		 TextComponent* healthPvpComp = new TextComponent("Lingua.otf", 20);
		 healthPvp->AddComponent(healthPvpComp);
		 healthPvpComp->SetText("Lives");
		 healthPvp->SetPosition(10, 225);
		 pvpScene.Add(healthPvp);
		 //ScoreDisplayObject
		 auto scorePvp = new GameObject;
		 TextComponent* scorePvpComp = new TextComponent("Lingua.otf", 20);
		 scorePvp->AddComponent(scorePvpComp);
		 scorePvpComp->SetText("Scores");
		 scorePvp->SetPosition(10, 200);
		 pvpScene.Add(scorePvp);


		 Subject* ValuesSubjectPvp = new Subject;
		 ValuesSubjectPvp->AddObserver(new HealthObserver(healthPvpComp));
		 ValuesSubjectPvp->AddObserver(new ScoreObserver(scorePvpComp));
		 peterPepperPvp->GetComponent<ValuesComponent>()->SetSubject(ValuesSubjectPvp);

		 //Make LevelManager
		 auto managerPvp = new GameObject;
		 managerPvp->AddComponent<LevelManager>(new LevelManager(&pvpScene, playersPvp, playerEnemyPvp, levelBackgroundsPvp));
		 pvpScene.Add(managerPvp);

		 //Do after rest otherwise invis
		 pvpScene.Add(peterPepperPvp);
		 pvpScene.Add(hotdogPvp);
#pragma endregion PvpScene





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

		 SceneChanger::GetInstance().SetControlObjects(controlObjects);

		 SceneChanger::GetInstance().SetCurrentScene("start");
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

	void MakeIngredient(glm::vec3 pos, EIngredientType ingredientType, Scene& scene, bool debugDraw, std::vector<GameObject*>& players) const
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
			case EIngredientType::Bun:
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
			case EIngredientType::Cheese:
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
			case EIngredientType::Lettuce:
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
			case EIngredientType::Tomato:
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
			case EIngredientType::Patty:
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
			case EIngredientType::BunBottom:
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
