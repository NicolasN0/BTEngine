#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

using namespace dae;

unsigned int Scene::m_IdCounter = 0;

std::vector<std::shared_ptr<GameObject>> dae::Scene::GetAllObjectsInWorld()
{
	return m_Objects;
}

std::vector<std::shared_ptr<GameObject>> dae::Scene::GetObjectsInWorldWithTag(std::string tag)
{
	std::vector<std::shared_ptr<GameObject>> m_ObjectsWithTag;
	for(auto o : m_Objects)
	{
		if(o->GetTag() == tag)
		{
			m_ObjectsWithTag.push_back(o);
		}
	}
	return m_ObjectsWithTag;
}

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene() = default;

void Scene::Add(const std::shared_ptr<GameObject>& object)
{
	m_Objects.push_back(object);
	object->SetScene(this);
}

void Scene::Update(float dt)
{
	for(auto& object : m_Objects)
	{
		object->Update(dt);
	}
}

void Scene::FixedUpdate(float timestep)
{
	for (auto& object : m_Objects)
	{
		object->FixedUpdate(timestep);
	}
}

void Scene::Render() const
{
	for (const auto& object : m_Objects)
	{
		object->Render();
	}
}

