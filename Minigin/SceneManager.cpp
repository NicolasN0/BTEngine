#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Update(float dt)
{
	
	m_CurrentScene->Update(dt);
}

void dae::SceneManager::FixedUpdate(float timestep)
{
	
	m_CurrentScene->FixedUpdate(timestep);
}

void dae::SceneManager::Render()
{
	
	m_CurrentScene->Render();
}

void dae::SceneManager::ClearScenes()
{
	m_Scenes.clear();
}

void dae::SceneManager::SetDelete(bool deleteScene)
{
	m_DeleteScenes = deleteScene;
}

void dae::SceneManager::SetCurrentScene(std::string name)
{
	for(auto& scene : m_Scenes)
	{
		if(scene->GetName() == name)
		{
			m_CurrentScene = scene;
		}
	}
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);
	m_CurrentScene = scene;
	return *scene;
}
