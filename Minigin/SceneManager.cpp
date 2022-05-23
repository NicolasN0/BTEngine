#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Update(float dt)
{
	for(auto& scene : m_Scenes)
	{
		scene->Update(dt);
	}
}

void dae::SceneManager::FixedUpdate(float timestep)
{
	for (auto& scene : m_Scenes)
	{
		scene->FixedUpdate(timestep);
	}
}

void dae::SceneManager::Render()
{
	for (const auto& scene : m_Scenes)
	{
		scene->Render();
	}
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);
	return *scene;
}
