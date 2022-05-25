#pragma once
#include "Transform.h"
#include "GameObject.h"
namespace dae
{
	class MonoBehaviour 
	{
	public:
		MonoBehaviour() = default;
		virtual ~MonoBehaviour() = default;
		virtual void Update(float dt) = 0;
		virtual void FixedUpdate(float timestep) = 0;
		virtual void Render() const {};
		void SetParent( GameObject* go )  { m_Parent = go; }
		GameObject* GetParent() const { return m_Parent; }
		void SetSize(glm::vec3 size) { m_Size = size; m_HasSize = true; }
		const glm::vec3 &GetSize() const { return m_Size; }
		bool GetHasSize() const { return m_HasSize; }
		// Transform& GetTransform() const { return m_Transform; }
	protected:
		//Transform m_Transform;
		GameObject* m_Parent;
		glm::vec3 m_Size;
		bool m_HasSize;
	};

}