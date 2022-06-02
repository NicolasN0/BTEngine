#pragma once
#include "MonoBehaviour.h"
#include "SpriteComponent.h"

namespace dae
{
	enum class EEnemyType
	{
		Hotdog,
		Egg,
		Pickle
	};


	class BasicEnemyComponent :
		public MonoBehaviour
	{
	public:
		BasicEnemyComponent(EEnemyType enemyType,bool isPlayer = false);
		void Update(float dt);
		void FixedUpdate(float timestep);
		void Render() const;

		bool GetIsOnLadder() const { return m_IsOnLadder; }
		bool GetIsOnPlatform() const { return m_IsOnPlatform; }

		void SetTarget(GameObject* target) { m_Target = target; }

		glm::vec3 GetPosition() const;
		void SetPosition(glm::vec3 pos);

		void SetIsFalling(bool isFalling);
		bool GetIsFalling() const;

		void Kill();

		void SetSubject(Subject* subject);

		void SetSpriteComp(SpriteComponent* comp);

		void SetDirection(glm::vec3 movespeed);

		void SetStunned(bool stunned);
		bool GetStunned() const;
	private:
		void CheckOverlaps();
		void UpdatePos(float dt);
		void UpdateDirection();
		
		void UpdateSprite();

		bool m_Stunned;
		float m_StunTimer;
		float m_MaxStunTime;

		glm::vec3 m_PlayerDir;
		bool m_IsOnLadder{};
		bool m_IsOnPlatform{};
		bool m_Falling{};
		GameObject* m_Target{};
		float m_MoveSpeed{20};
		bool m_CanSwitch{true};
		glm::vec3 m_Direction{};
		Subject* m_Subject{};

		EEnemyType m_Type;
		bool m_IsPlayer{};

		SpriteComponent* m_SpriteComp;

		
	};

}
