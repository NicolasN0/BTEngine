#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "MonoBehaviour.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include "Scene.h"

dae::GameObject::GameObject()
{
	m_Transform.SetScale(1, 1, 1);
	m_Size = glm::vec3(1, 1, 1);
}

dae::GameObject::~GameObject()
{
	for (auto component : m_pComponents) 
	{
		delete component;
		component = nullptr;
	}
	if(m_Subject != nullptr)
	{
		delete m_Subject;
		m_Subject = nullptr;
		
	}
};
//LOOP OVER COMPONENTS AND UPDATE?
void dae::GameObject::Update(float dt)
{
	for (auto component : m_pComponents) 
	{
		component->Update(dt);
	}
}

void dae::GameObject::FixedUpdate(float timestep)
{
	UNREFERENCED_PARAMETER(timestep);
}

void dae::GameObject::Render() const
{

	for (auto component : m_pComponents)
	{
		component->Render();

	}

	//Put in draw Rect debug code?
	if(m_DebugDraw == true)
	{
		SDL_SetRenderDrawColor(Renderer::GetInstance().GetSDLRenderer(), 255, 0, 0,255);
		SDL_Rect r;
		r.x = GetPosition().x;
		r.y = GetPosition().y;
		r.w = m_Size.x;
		r.h = m_Size.y;
		SDL_RenderDrawRect(Renderer::GetInstance().GetSDLRenderer(), &r);
		
	}
}


void dae::GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}

void dae::GameObject::SetScale(float x, float y)
{
	m_Transform.SetScale(x, y, 0.0f);
}

const glm::vec3& dae::GameObject::GetPosition() const
{
	return m_Transform.GetPosition();
}

const glm::vec3& dae::GameObject::GetScale() const
{
	return m_Transform.GetScale();
}

void dae::GameObject::RemoveComponent() {}

void dae::GameObject::SetParent(GameObject* parent) 
{
	m_Parent = parent;
}

dae::GameObject* dae::GameObject::GetParent() const 
{
	return m_Parent;
}

size_t dae::GameObject::GetChildCount() const
{
	return m_Childs.size();
}

dae::GameObject* dae::GameObject::GetChildAt(int index) const 
{
	return m_Childs.at(index);
}

void dae::GameObject::RemoveChild(int index) 
{
	m_Childs.erase(m_Childs.begin() + index);
}

void dae::GameObject::AddChild(GameObject* go) 
{
	m_Childs.push_back(go);
	go->SetParent(this);
}

void dae::GameObject::SetSubject(Subject* subject)
{
	m_Subject = subject;
}

dae::Subject* dae::GameObject::GetSubject()
{
	return m_Subject;
}

const glm::vec3& dae::GameObject::GetSize() const
{
	return m_Size;
}

void dae::GameObject::SetSize(glm::vec3 size)
{
	m_Size = size;
}

std::string dae::GameObject::GetTag() const
{
	return m_Tag;
}

void dae::GameObject::SetTag(std::string tag)
{
	m_Tag = tag;
}

bool dae::GameObject::GetIsOverlapping(std::shared_ptr<dae::GameObject> object)
{
	glm::vec3 l1 = GetPosition();
	glm::vec3 r1 = l1;
	r1.x += m_Size.x;
	r1.y += m_Size.y;

	glm::vec3 l2 = object->GetPosition();
	glm::vec3 r2 = l2;
	r2.x += m_Size.x;
	r2.y += m_Size.y;


	if (l1.x == r1.x || l1.y == r1.y || l2.x == r2.x
		|| l2.y == r2.y) {
		// the line cannot have positive overlap
		return false;
		
	}

	// If one rectangle is on left side of other
	if (l1.x >= r2.x || l2.x >= r1.x)
	{
		return false;
		
	}

	// If one rectangle is above other

	//test if works the same with y coordinates from this scene
	if (r1.y >= l2.y || r2.y >= l1.y)
	{
		return false;
		
	}



	return true;

}

bool dae::GameObject::IsOverlappingAny()
{
	if(m_Scene != nullptr)
	{
		std::vector < std::shared_ptr<GameObject> > objects = m_Scene->GetAllObjectsInWorld();
		for(auto o :objects)
		{
		
			glm::vec3 l1 = GetPosition();
			glm::vec3 r1 = l1;
			r1.x += m_Size.x;
			r1.y += m_Size.y;

			glm::vec3 l2 = o->GetPosition();
			glm::vec3 r2 = l2;
			r2.x += m_Size.x;
			r2.y += m_Size.y;


			if (l1.x == r1.x || l1.y == r1.y || l2.x == r2.x
				|| l2.y == r2.y) {
				// the line cannot have positive overlap
				//return false;
				continue;
			}

			// If one rectangle is on left side of other
			if (l1.x >= r2.x || l2.x >= r1.x)
			{
				//return false;
				continue;
			}

			// If one rectangle is above other

			//test if works the same with y coordinates from this scene
			if (r1.y >= l2.y || r2.y >= l1.y)
			{
				//return false;
				continue;
			}



			return true;
		}
		
	}

	return false;
}

bool dae::GameObject::IsOverlappingAnyWithTag(std::string tag)
{
	if (m_Scene != nullptr)
	{
		std::vector < std::shared_ptr<GameObject> > objects = m_Scene->GetObjectsInWorldWithTag(tag);
		for (auto o : objects)
		{

			glm::vec3 l1 = GetPosition();
			glm::vec3 r1 = l1;
			r1.x += m_Size.x;
			r1.y += m_Size.y;

			glm::vec3 l2 = o->GetPosition();
			glm::vec3 r2 = l2;
			r2.x += o->GetSize().x;
			r2.y += o->GetSize().y;


			if (l1.x == r1.x || l1.y == r1.y || l2.x == r2.x
				|| l2.y == r2.y) {
				// the line cannot have positive overlap
				//return false;
				continue;
			}

			// If one rectangle is on left side of other
			if (l1.x >= r2.x || l2.x >= r1.x)
			{
				//return false;
				continue;
			}

			// If one rectangle is above other

			//test if works the same with y coordinates from this scene
			if (r1.y <= l2.y || r2.y <= l1.y)
			{
				//return false;
				continue;
			}



			return true;
		}
	}
	return false;
}

bool dae::GameObject::IsCenterOverlappingAnyWithTag(std::string tag)
{
	if (m_Scene != nullptr)
	{
		std::vector < std::shared_ptr<GameObject> > objects = m_Scene->GetObjectsInWorldWithTag(tag);
		for (auto o : objects)
		{

			glm::vec3 l1 = GetPosition();
			l1.x += m_Size.x / 2;
			l1.y += m_Size.y / 2;
			glm::vec3 r1 = l1;
			//One to work with point
			r1.x += 1;
			r1.y += 1;

			glm::vec3 l2 = o->GetPosition();
			glm::vec3 r2 = l2;
			r2.x += o->GetSize().x;
			r2.y += o->GetSize().y;


			if (l1.x == r1.x || l1.y == r1.y || l2.x == r2.x
				|| l2.y == r2.y) {
				// the line cannot have positive overlap
				//return false;
				continue;
			}

			// If one rectangle is on left side of other
			if (l1.x >= r2.x || l2.x >= r1.x)
			{
				//return false;
				continue;
			}

			// If one rectangle is above other

			//test if works the same with y coordinates from this scene
			if (r1.y <= l2.y || r2.y <= l1.y)
			{
				//return false;
				continue;
			}



			return true;
		}
	}
	return false;
}

dae::Scene* dae::GameObject::GetScene() const
{
	return m_Scene;
}



void dae::GameObject::SetScene(Scene* scene)
{
	m_Scene = scene;
}

void dae::GameObject::SetDebugDraw(bool newVal)
{
	m_DebugDraw = newVal;
}
