#pragma once
#include "MonoBehaviour.h"
namespace dae
{
	class BasicEnemyComponent :
		public MonoBehaviour
	{
	public:
		BasicEnemyComponent() = default;
		void Update(float dt);
		void FixedUpdate(float timestep);
		void Render() const;

		bool GetIsOnLadder() const { return m_IsOnLadder; }
		bool GetIsOnPlatform() const { return m_IsOnPlatform; }

		void SetTarget(std::shared_ptr<GameObject> target) { m_Target = target; }
	private:
		void CheckOverlaps();
		void UpdatePos();
		void UpdateDirection();

		bool m_IsOnLadder{};
		bool m_IsOnPlatform{};
		std::shared_ptr<GameObject> m_Target{};
		float m_MoveSpeed{20};
		bool m_CanSwitch{true};
		glm::vec3 m_Direction{};
		
	};

}
