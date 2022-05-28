#pragma once
#include "MonoBehaviour.h"
namespace dae
{
	class BasicEnemyComponent :
		public MonoBehaviour
	{
	public:
		BasicEnemyComponent();
		void Update(float dt);
		void FixedUpdate(float timestep);
		void Render() const;

		bool GetIsOnLadder() const { return m_IsOnLadder; }
		bool GetIsOnPlatform() const { return m_IsOnPlatform; }

		void SetTarget(GameObject* target) { m_Target = target; }

		glm::vec3 GetPosition() const;
		void SetPosition(glm::vec3 pos);

		//void DecreaseFallCount();
		void SetIsFalling(bool isFalling);
		bool GetIsFalling() const;

		void Kill();
	private:
		void CheckOverlaps();
		void UpdatePos(float dt);
		void UpdateDirection();

		//int m_RemainingFallCount;
		bool m_IsOnLadder{};
		bool m_IsOnPlatform{};
		bool m_Falling{};
		GameObject* m_Target{};
		float m_MoveSpeed{20};
		bool m_CanSwitch{true};
		glm::vec3 m_Direction{};
		
	};

}
