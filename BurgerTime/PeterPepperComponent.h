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
		int GetLives() { return m_Lives; }
		int GetScore() { return m_Score; }
		void Damage();
		void IncreaseScore();

		bool GetIsOnLadder() const { return m_IsOnLadder; }
		bool GetIsOnPlatform() const { return m_IsOnPlatform; }

		void SetSubject(Subject* subject);
		Subject* GetSubject();
	private:
		void Respawn();
		int m_Lives{};
		int m_Score{};
		bool m_IsOnLadder{};
		bool m_IsOnPlatform{};
		glm::vec3 m_StartPos{ 250 ,250,0 };
		Subject* m_Subject{};
	};
	
}

