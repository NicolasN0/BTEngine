#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

using namespace dae;

unsigned int Scene::m_IdCounter = 0;

std::vector<GameObject*> dae::Scene::GetAllObjectsInWorld()
{
	return m_Objects;
}

std::vector<GameObject*> dae::Scene::GetObjectsInWorldWithTag(std::string tag)
{
	std::vector<GameObject*> m_ObjectsWithTag;
	for(auto o : m_Objects)
	{
		if(o->GetTag() == tag)
		{
			m_ObjectsWithTag.push_back(o);
		}
	}
	return m_ObjectsWithTag;
}

bool Scene::IsPointInRectangle(glm::vec3 point, glm::vec3 posRectangle, glm::vec3 sizeRectangle)
{
	float tlx, tly, brx, bry;
	tlx = posRectangle.x;
	tly = posRectangle.y;

	brx = posRectangle.x + sizeRectangle.x;
	bry = posRectangle.y + sizeRectangle.y;

	if(point.x >= tlx && point.x <= brx && point.y >= tly && point.y <= brx)
	{
		return true;
	}
	return false;

}

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene()
{
	for(auto o : m_Objects)
	{
		delete o;
		o = nullptr;
	}
}


void Scene::Add(GameObject* object)
{
	m_Objects.push_back(object);
	object->SetScene(this);

	//Add all child objects
	for(auto c : object->GetChilds())
	{
		m_Objects.push_back(c);
		c->SetScene(this);
	}
	
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

