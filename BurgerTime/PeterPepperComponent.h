#pragma once
#include "MonoBehaviour.h"
namespace dae
{
	class PeterPepperComponent :
	    public MonoBehaviour
	{
	public:
		PeterPepperComponent();
		void Update(float dt);
		void FixedUpdate(float timestep);
		void Render() const;
		int GetLives() { return m_Lives; }
		int GetScore() { return m_Score; }
		void Damage();
		void IncreaseScore();

		bool GetIsOnLadder() const { return m_IsOnLadder; }
		bool GetIsOnPlatform() const { return m_IsOnPlatform; }
	private:
		int m_Lives{};
		int m_Score{};
		bool m_IsOnLadder{};
		bool m_IsOnPlatform{};
	};
	
}

