#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "MonoBehaviour.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include "Scene.h"

dae::GameObject::GameObject() : m_Visible(true)
,m_DebugDraw()
,m_pScene()
,m_SetToDelete()
,m_pParent()
,m_Size()
,m_LocalScale()
,m_Transform()
,m_LocalPos()
,m_Tag()
,m_pChilds()
,m_pComponents()
{
	m_Transform.SetScale(1, 1, 1);
	m_Size = glm::vec3(1, 1, 1);
	m_LocalScale = glm::vec3(1, 1, 1);
	if(m_pParent != nullptr)
	{
		m_Transform.SetPosition(m_pParent->GetPosition());
	}
}

dae::GameObject::~GameObject()
{
	for (auto component : m_pComponents) 
	{
		if(component)
		{
			
			delete component;
			component = nullptr;
		}
	}

	size_t sizeChild = m_pChilds.size();
	for(size_t i = 0; i<sizeChild;i++)
	{
		delete m_pChilds.at(i);
		m_pChilds.at(i) = nullptr;
	}
	
};

void dae::GameObject::Update(float dt)
{
	for (auto component : m_pComponents) 
	{


		component->Update(dt);
	}

	size_t size = m_pChilds.size();
	for(size_t i = 0; i < size;i++)
	{
		m_pChilds.at(i)->Update(dt);
	}

	
}

void dae::GameObject::FixedUpdate(float )
{
	
}

void dae::GameObject::Render() const
{
	if(m_Visible)
	{
		
		for (auto component : m_pComponents)
		{
			component->Render();

		}

		size_t size = m_pChilds.size();
		for (size_t i = 0; i < size; i++)
		{
			m_pChilds.at(i)->Render();
		}

		//Put in draw Rect debug code?
		if(m_DebugDraw == true)
		{
			SDL_SetRenderDrawColor(Renderer::GetInstance().GetSDLRenderer(), 255, 0, 0,255);
			SDL_Rect r;
			r.x = static_cast<int>(GetPosition().x);
			r.y = static_cast<int>(GetPosition().y);
			r.w = static_cast<int>(m_Size.x);
			r.h = static_cast<int>(m_Size.y);
			SDL_RenderDrawRect(Renderer::GetInstance().GetSDLRenderer(), &r);
			
		}
	}
}


void dae::GameObject::SetPosition(float x, float y)
{
	
	SetPosition(glm::vec3(x, y, 0));
}

void dae::GameObject::SetPosition(const glm::vec3& pos)
{
	
	if (m_pParent == nullptr)
	{
		m_Transform.SetPosition(pos);

		for (auto c : m_pChilds)
		{

			c->UpdatePos();
		}
	}
	else
	{

		SetLocalPosition(pos.x, pos.y);


		m_Transform.SetPosition(GetLocalPosition().x + GetParent()->GetPosition().x, GetLocalPosition().y + GetParent()->GetPosition().y, 0);

		for (auto c : m_pChilds)
		{

			c->UpdatePos();
		}
	}
}

void dae::GameObject::SetScale(float x, float y)
{
	


	if (m_pParent == nullptr)
	{
		m_Transform.SetScale(x, y, 1.0f);

		//ChangeSize depending on scale
		m_Size *= GetScale();

		for (auto c : m_pChilds)
		{
		
			c->UpdateScale();
		}
	}
	else
	{

		SetLocalScale(x, y);
		m_Transform.SetScale(m_LocalScale.x * GetParent()->GetScale().x, m_LocalScale.y* GetParent()->GetScale().y, 1);
		m_Size *= GetScale();
		for (auto c : m_pChilds)
		{
			c->UpdateScale();
		}
	}

}

const glm::vec3& dae::GameObject::GetPosition() const
{
	return m_Transform.GetPosition();
}

const glm::vec3& dae::GameObject::GetScale() const
{
	return m_Transform.GetScale();
}


void dae::GameObject::SetParent(GameObject* const parent)
{
	m_pParent = parent;
}

const dae::GameObject* dae::GameObject::GetParent() const
{
	return m_pParent;
}




size_t dae::GameObject::GetChildCount() const
{
	return m_pChilds.size();
}

dae::GameObject* dae::GameObject::GetChildAt(int index) const
{
	return m_pChilds.at(index);
}



void dae::GameObject::RemoveChild(int index) 
{
	m_pChilds.erase(m_pChilds.begin() + index);
}

void dae::GameObject::AddChild(GameObject* const go)
{
	m_pChilds.push_back(go);
	go->SetParent(this);
	go->SetLocalPosition(0, 0);
	this->SetPosition(GetPosition());

	//change size if size of Child is bigger
	glm::vec3 childSize = go->GetSize();
	if (childSize.x > m_Size.x)
	{
		m_Size = (glm::vec3(childSize.x, m_Size.y, m_Size.z));
	}
	if (childSize.y > m_Size.y)
	{
		m_Size = (glm::vec3(m_Size.x, childSize.y, m_Size.z));
	}
	
	
}

const std::vector<dae::GameObject*>& dae::GameObject::GetChilds() const
{
	return m_pChilds;
}

const dae::Transform& dae::GameObject::GetTransform() const
{
	return m_Transform;
}

const glm::vec3& dae::GameObject::GetSize() const
{
	return m_Size;
}

void dae::GameObject::SetSize(const glm::vec3& size)
{
	m_Size = size;
}

void dae::GameObject::SetLocalPosition(float x, float y)
{
	m_LocalPos = glm::vec3(x, y, 0);
}

void dae::GameObject::SetLocalScale(float x, float y)
{
	m_LocalScale = glm::vec3(x, y, 1.f);
}

void dae::GameObject::SetLocalPosition(const glm::vec3& pos)
{
	m_LocalPos = pos;
}

const glm::vec3& dae::GameObject::GetLocalPosition() const
{
	return m_LocalPos;
}

void dae::GameObject::UpdatePos()
{
	if(m_pParent != nullptr)
	{
		m_Transform.SetPosition(m_LocalPos + m_pParent->GetPosition());
	}
}

void dae::GameObject::UpdateScale()
{
	if (m_pParent != nullptr)
	{
		m_Transform.SetScale(m_LocalScale.x * m_pParent->GetScale().x, m_LocalScale.y * m_pParent->GetScale().y,1);
	
		m_LocalPos.x *= GetScale().x;
		m_LocalPos.y *= GetScale().y;
		m_LocalPos.z *= GetScale().z;

		m_Size.x *= GetScale().x;
		m_Size.y *= GetScale().y;
		m_Size.z *= GetScale().z;
		UpdatePos();
	}
}

const std::string& dae::GameObject::GetTag() const
{
	return m_Tag;
}

void dae::GameObject::SetTag(const std::string& tag)
{
	m_Tag = tag;
}

bool dae::GameObject::GetIsOverlapping(GameObject* const object)
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
	if(m_pScene != nullptr)
	{
		std::vector < GameObject* > objects = m_pScene->GetAllObjectsInWorld();
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


			if (o == this)
			{
				continue;
			}

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

bool dae::GameObject::IsOverlappingAnyWithTag(const std::string& tag)
{
	if (m_pScene != nullptr)
	{
		std::vector < GameObject* > objects = m_pScene->GetObjectsInWorldWithTag(tag);
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


			if(o == this)
			{
				continue;
			}

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

bool dae::GameObject::IsCenterOverlappingAnyWithTag(const std::string& tag)
{
	if (m_pScene != nullptr)
	{
		std::vector <GameObject* > objects = m_pScene->GetObjectsInWorldWithTag(tag);
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


			if (o == this)
			{
				continue;
			}

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

dae::GameObject* dae::GameObject::GetFirstOverlappingObjectWithTag(const std::string& tag)
{
	if (m_pScene != nullptr)
	{
		std::vector < GameObject* > objects = m_pScene->GetObjectsInWorldWithTag(tag);
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


			if (o == this)
			{
				continue;
			}

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



			return o;
		}
	}
	return nullptr;
}

std::vector<dae::GameObject*> dae::GameObject::GetAllOverlappingWithTag(const std::string& tag)
{
	std::vector<GameObject*> overlapping;
	if (m_pScene != nullptr)
	{
		std::vector < GameObject* > objects = m_pScene->GetObjectsInWorldWithTag(tag);
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


			if (o == this)
			{
				continue;
			}

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


			overlapping.push_back(o);
			
		}
	}
	return overlapping;
}

dae::Scene* dae::GameObject::GetScene() const
{
	return m_pScene;
}



void dae::GameObject::SetScene(Scene* const scene)
{
	m_pScene = scene;
}

void dae::GameObject::Delete()
{
	m_SetToDelete = true;
}

bool dae::GameObject::isSetToDelete() const
{
	return m_SetToDelete;
}

void dae::GameObject::SetVisibility(bool visible)
{
	m_Visible = visible;
}

void dae::GameObject::SetDebugDraw(bool newVal)
{
	m_DebugDraw = newVal;
}
