#include "SceneChanger.h"

#include "Commands.h"
#include "InputManager.h"
#include "PeterPepperComponent.h"

namespace dae
{
	
void SceneChanger::SetCurrentScene(std::string name)
{
	dae::Input::GetInstance().ClearKeys();
	//dae::Input::GetInstance().SetClear(true);
	if(name == "start")
	{
		for (auto o : m_ControlObjects)
		{
			if (o->GetTag() == "Indicator")
			{

				Input::GetInstance().BindKey({ ButtonStates::buttonUp,SDLK_s,1 }, std::make_unique<Selector>(o->GetComponent<SelectorComponent>(), true, 3));
				Input::GetInstance().BindKey({ ButtonStates::buttonUp,SDLK_w,1 }, std::make_unique<Selector>(o->GetComponent<SelectorComponent>(), false, 3));
				Input::GetInstance().BindKey({ ButtonStates::buttonUp,SDLK_SPACE,1 }, std::make_unique<Continue>(o->GetComponent<SelectorComponent>()));
			}
		}
		SceneManager::GetInstance().SetCurrentScene(name);
		
	} else if(name == "game")
	{
		for(auto o : m_ControlObjects)
		{
			if(o->GetTag() == "Player")
			{
				
				dae::Input::GetInstance().BindKey({ ButtonStates::buttonPressed,SDLK_a,1 }, std::make_unique<Move>(o->GetComponent<PeterPepperComponent>(), glm::vec3(-80.0f, 0.0f, 0.0f)));
				dae::Input::GetInstance().BindKey({ ButtonStates::buttonPressed,SDLK_d,1 }, std::make_unique<Move>(o->GetComponent<PeterPepperComponent>(), glm::vec3(80.0f, 0.0f, 0.0f)));
				Input::GetInstance().BindKey({ ButtonStates::buttonPressed,SDLK_w,1 }, std::make_unique<Move>(o->GetComponent<PeterPepperComponent>(), glm::vec3(0.0f, -80.0f, 0.0f)));
				Input::GetInstance().BindKey({ ButtonStates::buttonPressed,SDLK_s,1 }, std::make_unique<Move>(o->GetComponent<PeterPepperComponent>(), glm::vec3(0.0f, 80.0f, 0.0f)));
			}
		}
		SceneManager::GetInstance().SetCurrentScene(name);
	} else if(name == "highscore")
	{
		Input::GetInstance().BindKey({ ButtonStates::buttonUp,SDLK_SPACE,1 }, std::make_unique<Replay>());

		SceneManager::GetInstance().SetCurrentScene(name);
	}

}

void SceneChanger::SetControlObjects(std::vector<dae::GameObject*> controlObjects)
{
	m_ControlObjects = controlObjects;
}
}
