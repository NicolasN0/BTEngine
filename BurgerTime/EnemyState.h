#pragma once
#include <vector>


namespace dae
{
	class GameObject;
	class BasicEnemyComponent;
	class SpriteComponent;
		
}

	class EnemyState
	{
	public:
		virtual ~EnemyState(){}
		virtual  EnemyState* Update(dae::BasicEnemyComponent& , float ) { return nullptr; }
		virtual void UpdateSprites(dae::BasicEnemyComponent& ){}
		virtual void Enter(dae::BasicEnemyComponent& ) {}
	};


	class EnemyStunnedState final : public EnemyState
	{
	public:
		EnemyStunnedState() : m_StunTimer(),m_MaxStunTime(),m_pSpriteComp(){}
		virtual  EnemyState* Update(dae::BasicEnemyComponent& enemy, float dt) override;
		virtual void UpdateSprites(dae::BasicEnemyComponent& enemy) override;
		virtual void Enter(dae::BasicEnemyComponent& enemy) override;

	private:
		float m_StunTimer;
		float m_MaxStunTime;
		dae::SpriteComponent* m_pSpriteComp;
	};

	class EnemyMovingState final : public EnemyState
	{
	public:
		EnemyMovingState() : m_UpdateTargets(),m_PlayerCountChecked(),m_pSpriteComp(),m_pPlayers(){}
		virtual EnemyState* Update(dae::BasicEnemyComponent& enemy, float dt) override;
		virtual void UpdateSprites(dae::BasicEnemyComponent& enemy) override;
		virtual void Enter(dae::BasicEnemyComponent& enemy) override;
	private:
		void SetTarget(dae::BasicEnemyComponent& enemy);

		dae::SpriteComponent* m_pSpriteComp;
		std::vector<dae::GameObject*> m_pPlayers;
		bool m_PlayerCountChecked;
		bool m_UpdateTargets;
	};


	class EnemyFallingState final : public EnemyState
	{
	public:
		virtual  EnemyState* Update(dae::BasicEnemyComponent& enemy, float dt) override;
	
		virtual void UpdateSprites(dae::BasicEnemyComponent& ) override {}
		virtual void Enter(dae::BasicEnemyComponent&) override {}
	};

	class EnemyDyingState final : public EnemyState
	{
	public:
		EnemyDyingState() : m_MaxDyingTime(),m_pSpriteComp(),m_DyingTimer(){}
		virtual  EnemyState* Update(dae::BasicEnemyComponent& enemy, float dt) override;
		virtual void UpdateSprites(dae::BasicEnemyComponent& enemy) override;
		virtual void Enter(dae::BasicEnemyComponent& enemy) override;

	private:
		void SpawnScoreEffect(dae::BasicEnemyComponent& enemy, int rarity);

		float m_DyingTimer;
		float m_MaxDyingTime;
		dae::SpriteComponent* m_pSpriteComp;
	};




