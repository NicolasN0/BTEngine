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

		bool GetNextLevel() const { return m_NextLevelTest; }
		void SetNextLevel(bool nextLevel) { m_NextLevelTest = nextLevel; }

		void UpdatePos(float dt);
		void SetMoveSpeed(glm::vec3 movespeed);
	private:
		void Respawn();

		glm::vec3 m_Movespeed;
		bool m_IsOnLadder{};
		bool m_IsOnPlatform{};
		glm::vec3 m_StartPos{ 250 ,250,0 };

		bool m_NextLevelTest{};
	
	};
	
}

