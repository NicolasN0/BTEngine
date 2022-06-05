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
		virtual ~EnemyState(){};
		virtual  EnemyState* Update(dae::BasicEnemyComponent& enemy, float dt) { return nullptr; }
		virtual void UpdateSprites(dae::BasicEnemyComponent& enemy){}
		virtual void Enter(dae::BasicEnemyComponent& enemy) {}
	};


	class EnemyStunnedState : public EnemyState
	{
	public:
		virtual ~EnemyStunnedState(){};
		virtual  EnemyState* Update(dae::BasicEnemyComponent& enemy, float dt);
		virtual void UpdateSprites(dae::BasicEnemyComponent& enemy);
		virtual void Enter(dae::BasicEnemyComponent& enemy);

	private:
		float m_StunTimer;
		float m_MaxStunTime;
		dae::SpriteComponent* m_SpriteComp;
	};

	class EnemyMovingState : public EnemyState
	{
	public:
		virtual ~EnemyMovingState() {};
		virtual EnemyState* Update(dae::BasicEnemyComponent& enemy, float dt);
		virtual void UpdateSprites(dae::BasicEnemyComponent& enemy);
		virtual void Enter(dae::BasicEnemyComponent& enemy);
	private:
		void SetTarget(dae::BasicEnemyComponent& enemy);
		dae::SpriteComponent* m_SpriteComp;
		std::vector<dae::GameObject*> m_Players;
		bool m_PlayerCountChecked;
		bool m_UpdateTargets;
	};


	class EnemyFallingState : public EnemyState
	{
	public:
		virtual ~EnemyFallingState() {};
		virtual  EnemyState* Update(dae::BasicEnemyComponent& enemy, float dt);
	
		virtual void UpdateSprites(dae::BasicEnemyComponent& enemy)
		{
			
		};
		virtual void Enter(dae::BasicEnemyComponent& enemy) {};
	};

	class EnemyDyingState : public EnemyState
	{
	public:
		virtual ~EnemyDyingState() {};
		virtual  EnemyState* Update(dae::BasicEnemyComponent& enemy, float dt);
		virtual void UpdateSprites(dae::BasicEnemyComponent& enemy);
		virtual void Enter(dae::BasicEnemyComponent& enemy);

	private:
		void SpawnScoreEffect(dae::BasicEnemyComponent& enemy, int rarity);
		float m_DyingTimer;
		float m_MaxDyingTime;
		dae::SpriteComponent* m_SpriteComp;
	};




