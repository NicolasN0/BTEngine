#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Update(float dt)
{
	
	m_spCurrentScene->Update(dt);
}

void dae::SceneManager::FixedUpdate(float timestep)
{
	
	m_spCurrentScene->FixedUpdate(timestep);
}

void dae::SceneManager::Render() const
{
	
	m_spCurrentScene->Render();
}

void dae::SceneManager::ClearScenes()
{
	m_spScenes.clear();
}

void dae::SceneManager::SetDelete(bool deleteScene)
{
	m_DeleteScenes = deleteScene;
}

void dae::SceneManager::SetCurrentScene(const std::string& name)
{
	for(auto& scene : m_spScenes)
	{
		if(scene->GetName() == name)
		{
			m_spCurrentScene = scene;
		}
	}
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_spScenes.push_back(scene);
	m_spCurrentScene = scene;
	return *scene;
}
