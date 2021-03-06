#pragma once
#include "Transform.h"
#include <string>
#include <vector>
#include "Subject.h"
#include <memory>


namespace dae
{
	class Scene;
	class Texture2D;
	class MonoBehaviour;
	
	class GameObject final
	{
	public:
		//Core
		void Update(float dt);
		void FixedUpdate(float timestep);
		void Render() const;

		
		//Rule of 5
		GameObject();
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		//Component
		template <typename T>
		void AddComponent(T* component);
		template <typename T>
		T* GetComponent() const;


		//Parent
		void SetParent(GameObject* const parent);
		const GameObject* GetParent() const;


		//Child
		size_t GetChildCount() const;
		GameObject* GetChildAt(int index) const;
		void RemoveChild(int index);
		void AddChild(GameObject* const go);
		const std::vector<GameObject*>& GetChilds() const;

		//Transform
		const Transform& GetTransform() const;
		void SetPosition(float x, float y);
		void SetPosition(const glm::vec3& pos);
		void SetScale(float x, float y);
		const glm::vec3 &GetPosition() const;
		const glm::vec3 &GetScale() const;

	
		const glm::vec3& GetSize() const;
		void SetSize(const glm::vec3& size);

		void SetLocalPosition(float x, float y);
		void SetLocalScale(float x, float y);
		void SetLocalPosition(const glm::vec3& pos);
		const glm::vec3& GetLocalPosition() const;

		void UpdatePos();
		void UpdateScale();


		//Tag
		const std::string& GetTag() const;
		void SetTag(const std::string& tag);


		//Overlapping
		bool GetIsOverlapping(dae::GameObject* const object);
		bool IsOverlappingAny();
		bool IsOverlappingAnyWithTag(const std::string& tag);
		bool IsCenterOverlappingAnyWithTag(const std::string& tag);
		GameObject* GetFirstOverlappingObjectWithTag(const std::string& tag);
		std::vector<GameObject*> GetAllOverlappingWithTag(const std::string& tag);

		//Scene
		Scene* GetScene() const;
		void SetScene(Scene* const scene);

		void Delete();
		bool isSetToDelete() const;

		void SetVisibility(bool visible);
		//Debug
		void SetDebugDraw(bool newVal);
	private:
		bool m_DebugDraw;
		bool m_SetToDelete;
		bool m_Visible;

		std::string m_Tag;

		glm::vec3 m_Size;
		glm::vec3 m_LocalPos;
		glm::vec3 m_LocalScale;

		Transform m_Transform;

		GameObject* m_pParent;
		Scene* m_pScene;

		std::vector<GameObject*> m_pChilds;
		std::vector<MonoBehaviour*> m_pComponents;
	};

	template <typename T>
	void dae::GameObject::AddComponent(T* component)
	{
		m_pComponents.push_back(component);
		component->SetParent(this);

		//change size if size of component is bigger
		if(component->GetHasSize())
		{
			glm::vec3 componentSize = component->GetSize();
			
			if(componentSize.x > m_Size.x)
			{
				m_Size = (glm::vec3(componentSize.x, m_Size.y, m_Size.z));
			}
			if(componentSize.y > m_Size.y)
			{
				m_Size = (glm::vec3(m_Size.x, componentSize.y, m_Size.z));
			}
		}
	}

	template <typename T>
	T* dae::GameObject::GetComponent() const
	{
		std::vector<dae::MonoBehaviour*>::const_iterator iterator = std::find_if(m_pComponents.cbegin(), m_pComponents.cend(), [](const dae::MonoBehaviour* comp)
			{
				return typeid(T) == typeid(*comp);

			});
		if (iterator == m_pComponents.cend())
		{
			return nullptr;
			
		}
		return static_cast<T*>(*iterator);
	}

}
