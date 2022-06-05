#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

using namespace dae;


const std::vector<GameObject*>& dae::Scene::GetAllObjectsInWorld() const
{
	return m_pObjects;
}

std::vector<GameObject*> dae::Scene::GetObjectsInWorldWithTag(const std::string& tag) const
{
	std::vector<GameObject*> m_ObjectsWithTag;
	for(auto o : m_pObjects)
	{
		if(o->GetTag() == tag)
		{
			m_ObjectsWithTag.push_back(o);
		}
	}
	return m_ObjectsWithTag;
}

bool Scene::IsPointInRectangle(const glm::vec3& point, const glm::vec3& posRectangle, const glm::vec3& sizeRectangle) const
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

const std::string& dae::Scene::GetName() const
{
	return m_Name;
}

Scene::Scene(const std::string& name) : m_Name(name) ,m_pObjects(){}

Scene::~Scene()
{
	
	size_t size = m_pObjects.size();
	for(size_t i = 0 ; i<size;i++)
	{
		delete m_pObjects.at(i);
		m_pObjects.at(i) = nullptr;
	}
}


void Scene::Add(GameObject* const object)
{
	m_pObjects.push_back(object);
	object->SetScene(this);

	//Add all child objects
	for(auto c : object->GetChilds())
	{
		c->SetScene(this);
	}
	
}

void Scene::Update(float dt)
{
	
	size_t size = m_pObjects.size();
	for(size_t i = 0; i< size;i++)
	{
		m_pObjects.at(i)->Update(dt);
	}
	auto end = std::remove_if(m_pObjects.begin(), m_pObjects.end(), [](auto* object)
	{
		if(object->isSetToDelete())
		{
			delete object;
			object = nullptr;
			return true;
		}
		return false;
	});
	m_pObjects.erase(end, m_pObjects.end());
	
}

void Scene::FixedUpdate(float timestep)
{
	for (auto& object : m_pObjects)
	{
		object->FixedUpdate(timestep);
	}
}

void Scene::Render() const
{
	for (const auto& object : m_pObjects)
	{
		object->Render();
	}
}

