#pragma once
#include "MonoBehaviour.h"
#include "SpriteComponent.h"
#include "EnemyState.h"
namespace dae
{
	enum class EEnemyType
	{
		Hotdog,
		Egg,
		Pickle
	};



	class BasicEnemyComponent final :
		public MonoBehaviour
	{
	public:
		//Rule of 5
		BasicEnemyComponent(EEnemyType enemyType,SpriteComponent* const sprite,bool isPlayer = false);
		~BasicEnemyComponent() override;

		BasicEnemyComponent(const BasicEnemyComponent&) = delete;
		BasicEnemyComponent(BasicEnemyComponent&&) noexcept = delete;

		BasicEnemyComponent& operator=(const BasicEnemyComponent&) = delete;
		BasicEnemyComponent& operator=(BasicEnemyComponent&&) noexcept = delete;

		//Core
		void Update(float dt) override;
		void FixedUpdate(float timestep) override;
		void Render() const override;

		//Getter
		bool GetIsOnLadder() const; 
		bool GetIsOnPlatform() const;
		bool GetIsFalling() const;
		bool GetIsPlayer() const;
		bool GetStunned() const;
		bool GetDying() const;
		bool GetDyingComplete() const;
		const glm::vec3& GetPosition() const;
		const glm::vec3& GetDirection() const;
		const glm::vec3& GetPrevDir() const;
		SpriteComponent* const GetSpriteComp() const;
		EEnemyType GetType() const;

		//Setter
		void SetTarget(GameObject* const target);
		void SetPosition(const glm::vec3& pos);
		void SetIsFalling(bool isFalling);
		void SetSubject(Subject* const subject);
		void SetSpriteComp(SpriteComponent* const comp);
		void SetDirection(const glm::vec3& movespeed);
		void SetStunned(bool stunned);
		void SetDyingComplete(bool dyingComplete);
		void SetCanSwitch(bool canSwitch);
		void SetPrevDir(const glm::vec3& prevDir);
		//Public
		void Kill();
		void CheckOverlaps();
		void UpdatePos(float dt);
		void UpdateDirection();
		



	private:
		void SetHorizontalDir();
		void SetVerticalDir();

		bool m_Stunned;
		bool m_Dying;
		bool m_DyingComplete;
		bool m_IsOnLadder;
		bool m_IsOnPlatform;
		bool m_Falling;
		bool m_CanSwitch;
		bool m_IsPlayer;
		bool m_BlockedHor;
		bool m_BlockedVer;
		bool m_CanSwitchLadder;
		bool m_CanSwitchPlatform;

		float m_StunTimer;
		float m_MaxStunTime;
		float m_MoveSpeed;

		glm::vec3 m_PrevDir;
		glm::vec3 m_PlayerDir;
		glm::vec3 m_Direction;
		glm::vec3 m_BlockedCor;
		glm::vec3 m_LastSwitchCor;

		EEnemyType m_Type;

		GameObject* m_pTarget;
		EnemyState* m_pState;
		Subject* m_pSubject;
		SpriteComponent* m_pSpriteComp;


	};

}
