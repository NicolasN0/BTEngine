#pragma once
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
		void SetParent( GameObject* const go )  { m_pParent = go; }
		GameObject* GetParent() const { return m_pParent; }
		void SetSize(const glm::vec3& size) { m_Size = size; m_HasSize = true; }
		const glm::vec3 &GetSize() const { return m_Size; }
		bool GetHasSize() const { return m_HasSize; }
	
	protected:

		GameObject* m_pParent;
		glm::vec3 m_Size;
		bool m_HasSize;
	};

}