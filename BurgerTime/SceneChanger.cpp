#include "SceneChanger.h"

#include "Commands.h"
#include "HighscoreManager.h"
#include "InputManager.h"
#include "LevelManager.h"
#include "Locator.h"
#include "PeterPepperComponent.h"
#include "ValuesComponent.h"

#include "GameObject.h"

namespace dae
{
	
void SceneChanger::SetCurrentScene(const std::string& name)
{
	Audio* audioService = Locator::getAudio();

	size_t size = m_pControlObjects.size();
	

	dae::Input::GetInstance().ClearKeys();

	if(name == "start")
	{
		audioService->LoadMusic("../Data/Sounds/Start.mp3");
		audioService->SetMusicVolume(5);
		audioService->PlayMusic();
		for (auto o : m_pControlObjects)
		{
			if (o->GetTag() == "Indicator")
			{

				Input::GetInstance().BindKey({ ButtonStates::buttonUp,SDLK_s,1 }, std::make_unique<Selector>(o->GetComponent<SelectorComponent>(), true, 3));
				Input::GetInstance().BindKey({ ButtonStates::buttonUp,SDLK_w,1 }, std::make_unique<Selector>(o->GetComponent<SelectorComponent>(), false, 3));
				Input::GetInstance().BindKey({ ButtonStates::buttonUp,SDLK_SPACE,1 }, std::make_unique<Continue>(o->GetComponent<SelectorComponent>()));
			}
		}
		SceneManager::GetInstance().SetCurrentScene(name);
		
	}
	else if(name == "game")
	{

		//Reset scores and text components
		HighscoreManager::GetInstance().UpdateHighScore();
		ValuesComponent::Reset();
		for (size_t i{}; i < size; i++)
		{
			if (m_pControlObjects.at(i)->GetTag() == "Player")
			{
				m_pControlObjects.at(i)->GetComponent<ValuesComponent>()->ResetObserver();
			}
		}

		//Reset level
		LevelManager* manager = m_pLevelManagers.at(0)->GetComponent<LevelManager>();
		manager->ClearLevel();
		manager->MakeLevel(1);

		//Set music
		audioService->LoadMusic("../Data/Sounds/GameLoop.mp3");
		audioService->SetMusicVolume(5);
		audioService->PlayMusic();
		for(auto o : m_pControlObjects)
		{
			if(o->GetTag() == "Player")
			{
				
				dae::Input::GetInstance().BindKey({ ButtonStates::buttonPressed,SDLK_a,1 }, std::make_unique<Move>(o->GetComponent<PeterPepperComponent>(), glm::vec3(-80.0f, 0.0f, 0.0f)));
				dae::Input::GetInstance().BindKey({ ButtonStates::buttonPressed,SDLK_d,1 }, std::make_unique<Move>(o->GetComponent<PeterPepperComponent>(), glm::vec3(80.0f, 0.0f, 0.0f)));
				Input::GetInstance().BindKey({ ButtonStates::buttonPressed,SDLK_w,1 }, std::make_unique<Move>(o->GetComponent<PeterPepperComponent>(), glm::vec3(0.0f, -80.0f, 0.0f)));
				Input::GetInstance().BindKey({ ButtonStates::buttonPressed,SDLK_s,1 }, std::make_unique<Move>(o->GetComponent<PeterPepperComponent>(), glm::vec3(0.0f, 80.0f, 0.0f)));

				Input::GetInstance().BindKey({ ButtonStates::buttonUp,SDLK_a,1 }, std::make_unique<StopMove>(o->GetComponent<PeterPepperComponent>()));
				Input::GetInstance().BindKey({ ButtonStates::buttonUp,SDLK_d,1 }, std::make_unique<StopMove>(o->GetComponent<PeterPepperComponent>()));
				Input::GetInstance().BindKey({ ButtonStates::buttonUp,SDLK_w,1 }, std::make_unique<StopMove>(o->GetComponent<PeterPepperComponent>()));
				Input::GetInstance().BindKey({ ButtonStates::buttonUp,SDLK_s,1 }, std::make_unique<StopMove>(o->GetComponent<PeterPepperComponent>()));

				Input::GetInstance().BindKey({ ButtonStates::buttonUp,SDLK_f,1 }, std::make_unique<Throw>(o->GetComponent<PeterPepperComponent>()));
				//Next Level Test
				Input::GetInstance().BindKey({ButtonStates::buttonUp,SDLK_k,1 }, std::make_unique<NextLevel>(o->GetComponent<PeterPepperComponent>()));
				break;
			}
		}
		SceneManager::GetInstance().SetCurrentScene(name);
	}
	else if(name == "highscore")
	{
		
		Input::GetInstance().BindKey({ ButtonStates::buttonUp,SDLK_SPACE,1 }, std::make_unique<Replay>());

		//Update Highscore screen

		std::vector<TextComponent*> compVec = HighscoreManager::GetInstance().GetTextComponents();
		std::vector<int> highscores = HighscoreManager::GetInstance().GetHighscores(static_cast<int>(compVec.size()));
		for(size_t i{}; i < compVec.size() && i < highscores.size();i++)
		{
			compVec.at(i)->SetText(std::to_string(highscores.at(i)));
		}

		SceneManager::GetInstance().SetCurrentScene(name);
	}
	else if(name == "coop")
	{
		//Reset values and text comp
		HighscoreManager::GetInstance().UpdateHighScore();
		ValuesComponent::Reset();
		for (size_t i{}; i < size; i++)
		{
			if (m_pControlObjects.at(i)->GetTag() == "Player")
			{
				m_pControlObjects.at(i)->GetComponent<ValuesComponent>()->ResetObserver();
			}
		}

		
		//Reset level
		LevelManager* manager = m_pLevelManagers.at(1)->GetComponent<LevelManager>();
		manager->ClearLevel();
		manager->MakeLevel(1);

		//Sound
		audioService->LoadMusic("../Data/Sounds/GameLoop.mp3");
		audioService->SetMusicVolume(5);
		audioService->PlayMusic();
		int count{};
		for (auto o : m_pControlObjects)
		{
			if (o->GetTag() == "Player")
			{
				if(count == 2)
				{
					dae::Input::GetInstance().BindKey({ ButtonStates::buttonPressed,ControllerButton::DpadLeft,0 }, std::make_unique<Move>(o->GetComponent<PeterPepperComponent>(), glm::vec3(-80.0f, 0.0f, 0.0f)));
					dae::Input::GetInstance().BindKey({ ButtonStates::buttonPressed,ControllerButton::DpadRight,0 }, std::make_unique<Move>(o->GetComponent<PeterPepperComponent>(), glm::vec3(80.0f, 0.0f, 0.0f)));
					Input::GetInstance().BindKey({ ButtonStates::buttonPressed,ControllerButton::DpadUp,0 }, std::make_unique<Move>(o->GetComponent<PeterPepperComponent>(), glm::vec3(0.0f, -80.0f, 0.0f)));
					Input::GetInstance().BindKey({ ButtonStates::buttonPressed,ControllerButton::DpadDown,0 }, std::make_unique<Move>(o->GetComponent<PeterPepperComponent>(), glm::vec3(0.0f, 80.0f, 0.0f)));

					Input::GetInstance().BindKey({ ButtonStates::buttonUp,ControllerButton::DpadLeft,0 }, std::make_unique<StopMove>(o->GetComponent<PeterPepperComponent>()));
					Input::GetInstance().BindKey({ ButtonStates::buttonUp,ControllerButton::DpadRight,0 }, std::make_unique<StopMove>(o->GetComponent<PeterPepperComponent>()));
					Input::GetInstance().BindKey({ ButtonStates::buttonUp,ControllerButton::DpadUp,0 }, std::make_unique<StopMove>(o->GetComponent<PeterPepperComponent>()));
					Input::GetInstance().BindKey({ ButtonStates::buttonUp,ControllerButton::DpadDown,0 }, std::make_unique<StopMove>(o->GetComponent<PeterPepperComponent>()));

					Input::GetInstance().BindKey({ ButtonStates::buttonUp,ControllerButton::ButtonA,0 }, std::make_unique<Throw>(o->GetComponent<PeterPepperComponent>()));

					//Next Level Test
					Input::GetInstance().BindKey({ ButtonStates::buttonDown,ControllerButton::ButtonX,0 }, std::make_unique<NextLevel>(o->GetComponent<PeterPepperComponent>()));
					
				} else if(count == 1)
				{
					
					dae::Input::GetInstance().BindKey({ ButtonStates::buttonPressed,SDLK_a,1 }, std::make_unique<Move>(o->GetComponent<PeterPepperComponent>(), glm::vec3(-80.0f, 0.0f, 0.0f)));
					dae::Input::GetInstance().BindKey({ ButtonStates::buttonPressed,SDLK_d,1 }, std::make_unique<Move>(o->GetComponent<PeterPepperComponent>(), glm::vec3(80.0f, 0.0f, 0.0f)));
					Input::GetInstance().BindKey({ ButtonStates::buttonPressed,SDLK_w,1 }, std::make_unique<Move>(o->GetComponent<PeterPepperComponent>(), glm::vec3(0.0f, -80.0f, 0.0f)));
					Input::GetInstance().BindKey({ ButtonStates::buttonPressed,SDLK_s,1 }, std::make_unique<Move>(o->GetComponent<PeterPepperComponent>(), glm::vec3(0.0f, 80.0f, 0.0f)));

					Input::GetInstance().BindKey({ ButtonStates::buttonUp,SDLK_a,1 }, std::make_unique<StopMove>(o->GetComponent<PeterPepperComponent>()));
					Input::GetInstance().BindKey({ ButtonStates::buttonUp,SDLK_d,1 }, std::make_unique<StopMove>(o->GetComponent<PeterPepperComponent>()));
					Input::GetInstance().BindKey({ ButtonStates::buttonUp,SDLK_w,1 }, std::make_unique<StopMove>(o->GetComponent<PeterPepperComponent>()));
					Input::GetInstance().BindKey({ ButtonStates::buttonUp,SDLK_s,1 }, std::make_unique<StopMove>(o->GetComponent<PeterPepperComponent>()));

					Input::GetInstance().BindKey({ ButtonStates::buttonUp,SDLK_f,1 }, std::make_unique<Throw>(o->GetComponent<PeterPepperComponent>()));

					//Next Level Test
					Input::GetInstance().BindKey({ ButtonStates::buttonUp,SDLK_k,1 }, std::make_unique<NextLevel>(o->GetComponent<PeterPepperComponent>()));
				}
				count++;

			}
		}
		SceneManager::GetInstance().SetCurrentScene(name);
	}
	else if(name == "pvp")
	{

		HighscoreManager::GetInstance().UpdateHighScore();
		//Reset values and text
		ValuesComponent::Reset();
		for (size_t i{}; i < size; i++)
		{
			if (m_pControlObjects.at(i)->GetTag() == "Player")
			{
				m_pControlObjects.at(i)->GetComponent<ValuesComponent>()->ResetObserver();
			}
		}

		//Reset level
		LevelManager* manager = m_pLevelManagers.at(2)->GetComponent<LevelManager>();
		manager->ClearLevel();
		manager->MakeLevel(1);


		//Sound
		audioService->LoadMusic("../Data/Sounds/GameLoop.mp3");
		audioService->SetMusicVolume(5);
		audioService->PlayMusic();
		int count{};
		for (auto o : m_pControlObjects)
		{
			if (o->GetTag() == "Player")
			{
				if (count == 3)
				{
					dae::Input::GetInstance().BindKey({ ButtonStates::buttonPressed,ControllerButton::DpadLeft,0 }, std::make_unique<Move>(o->GetComponent<PeterPepperComponent>(), glm::vec3(-80.0f, 0.0f, 0.0f)));
					dae::Input::GetInstance().BindKey({ ButtonStates::buttonPressed,ControllerButton::DpadRight,0 }, std::make_unique<Move>(o->GetComponent<PeterPepperComponent>(), glm::vec3(80.0f, 0.0f, 0.0f)));
					Input::GetInstance().BindKey({ ButtonStates::buttonPressed,ControllerButton::DpadUp,0 }, std::make_unique<Move>(o->GetComponent<PeterPepperComponent>(), glm::vec3(0.0f, -80.0f, 0.0f)));
					Input::GetInstance().BindKey({ ButtonStates::buttonPressed,ControllerButton::DpadDown,0 }, std::make_unique<Move>(o->GetComponent<PeterPepperComponent>(), glm::vec3(0.0f, 80.0f, 0.0f)));

					Input::GetInstance().BindKey({ ButtonStates::buttonUp,ControllerButton::DpadLeft,0 }, std::make_unique<StopMove>(o->GetComponent<PeterPepperComponent>()));
					Input::GetInstance().BindKey({ ButtonStates::buttonUp,ControllerButton::DpadRight,0 }, std::make_unique<StopMove>(o->GetComponent<PeterPepperComponent>()));
					Input::GetInstance().BindKey({ ButtonStates::buttonUp,ControllerButton::DpadUp,0 }, std::make_unique<StopMove>(o->GetComponent<PeterPepperComponent>()));
					Input::GetInstance().BindKey({ ButtonStates::buttonUp,ControllerButton::DpadDown,0 }, std::make_unique<StopMove>(o->GetComponent<PeterPepperComponent>()));
					
					Input::GetInstance().BindKey({ ButtonStates::buttonDown,ControllerButton::ButtonX,0 }, std::make_unique<NextLevel>(o->GetComponent<PeterPepperComponent>()));

					Input::GetInstance().BindKey({ ButtonStates::buttonUp,ControllerButton::ButtonA,0 }, std::make_unique<Throw>(o->GetComponent<PeterPepperComponent>()));


				}
				
				count++;

			}

			if(o->GetTag() == "Enemy")
			{
				dae::Input::GetInstance().BindKey({ ButtonStates::buttonPressed,SDLK_a,1 }, std::make_unique<MoveHotdog>(o->GetComponent<BasicEnemyComponent>(), glm::vec3(-80.0f, 0.0f, 0.0f)));
				dae::Input::GetInstance().BindKey({ ButtonStates::buttonPressed,SDLK_d,1 }, std::make_unique<MoveHotdog>(o->GetComponent<BasicEnemyComponent>(), glm::vec3(80.0f, 0.0f, 0.0f)));
				Input::GetInstance().BindKey({ ButtonStates::buttonPressed,SDLK_w,1 }, std::make_unique<MoveHotdog>(o->GetComponent<BasicEnemyComponent>(), glm::vec3(0.0f, -80.0f, 0.0f)));
				Input::GetInstance().BindKey({ ButtonStates::buttonPressed,SDLK_s,1 }, std::make_unique<MoveHotdog>(o->GetComponent<BasicEnemyComponent>(), glm::vec3(0.0f, 80.0f, 0.0f)));

				Input::GetInstance().BindKey({ ButtonStates::buttonUp,SDLK_a,1 }, std::make_unique<StopMoveHotdog>(o->GetComponent<BasicEnemyComponent>()));
				Input::GetInstance().BindKey({ ButtonStates::buttonUp,SDLK_d,1 }, std::make_unique<StopMoveHotdog>(o->GetComponent<BasicEnemyComponent>()));
				Input::GetInstance().BindKey({ ButtonStates::buttonUp,SDLK_w,1 }, std::make_unique<StopMoveHotdog>(o->GetComponent<BasicEnemyComponent>()));
				Input::GetInstance().BindKey({ ButtonStates::buttonUp,SDLK_s,1 }, std::make_unique<StopMoveHotdog>(o->GetComponent<BasicEnemyComponent>()));
				
			}
		}
		SceneManager::GetInstance().SetCurrentScene(name);
	}

}

void SceneChanger::SetControlObjects(const std::vector<dae::GameObject*>& controlObjects)
{
	m_pControlObjects = controlObjects;
}
void SceneChanger::SetLevelManagers(const std::vector<dae::GameObject*>& levelManagers)
{
	m_pLevelManagers = levelManagers;
}
}
