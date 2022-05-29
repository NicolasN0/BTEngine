#pragma once
#include "MonoBehaviour.h"
namespace dae
{
	class PeterPepperComponent :
	    public MonoBehaviour
	{
	public:
		PeterPepperComponent();
		~PeterPepperComponent();
		void Update(float dt);
		void FixedUpdate(float timestep);
		void Render() const;
		

		bool GetIsOnLadder() const { return m_IsOnLadder; }
		bool GetIsOnPlatform() const { return m_IsOnPlatform; }

	private:
		void Respawn();
	
		bool m_IsOnLadder{};
		bool m_IsOnPlatform{};
		glm::vec3 m_StartPos{ 250 ,250,0 };
	
	};
	
}

