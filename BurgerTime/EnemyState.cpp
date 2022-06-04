#include "EnemyState.h"

#include <iostream>

#include "BasicEnemyComponent.h"
#include "SpriteComponent.h"

EnemyState* EnemyStunnedState::Update(dae::BasicEnemyComponent& enemy, float dt)
{

	if(enemy.GetDying())
	{
		return new EnemyDyingState();
	}
	
	m_StunTimer += dt;
	if (m_StunTimer > m_MaxStunTime)
	{
		enemy.SetStunned(false);
		m_StunTimer = 0;
		return new EnemyMovingState();
	}

	//enemy.UpdateSprite();
	UpdateSprites(enemy);
	if(enemy.GetIsFalling())
	{
		return new EnemyFallingState();
	}

	
	

	return nullptr;
}

void EnemyStunnedState::UpdateSprites(dae::BasicEnemyComponent& enemy)
{
	m_SpriteComp->SetFrameRow(3);
	m_SpriteComp->SetNumberOfFrames(2);
	m_SpriteComp->SetStartFrame(4);
}

void EnemyStunnedState::Enter(dae::BasicEnemyComponent& enemy)
{
	m_SpriteComp = enemy.GetSpriteComp();
	m_MaxStunTime = 2;
}

EnemyState* EnemyMovingState::Update(dae::BasicEnemyComponent& enemy, float dt)
{
	if (enemy.GetDying())
	{
		return new EnemyDyingState();
	}

	enemy.CheckOverlaps();
	if (enemy.GetIsPlayer() == false)
	{

		enemy.UpdateDirection();
	}
	enemy.UpdatePos(dt);

	UpdateSprites(enemy);

	if (enemy.GetStunned())
	{
		return new EnemyStunnedState();
	}

	if(enemy.GetIsFalling())
	{
		return new EnemyFallingState();
	}
	return nullptr;
}

void EnemyMovingState::UpdateSprites(dae::BasicEnemyComponent& enemy)
{
	glm::vec3 dir = enemy.GetDirection();
	if (dir.y == 0 && dir.x == 0)
	{
		m_SpriteComp->SetPaused(true);
	}
	else
	{
		m_SpriteComp->SetPaused(false);
	}

	if (dir.y > 0)
	{

		m_SpriteComp->SetFrameRow(2);
		m_SpriteComp->SetNumberOfFrames(2);
		m_SpriteComp->SetStartFrame(0);


	}
	else if (dir.y < 0)
	{
		m_SpriteComp->SetFrameRow(2);
		m_SpriteComp->SetNumberOfFrames(2);
		m_SpriteComp->SetStartFrame(4);
	}
	else if (dir.x > 0)
	{
		m_SpriteComp->SetFrameRow(2);
		m_SpriteComp->SetNumberOfFrames(2);
		m_SpriteComp->SetStartFrame(2);


	}
	else if (dir.x < 0)
	{
		m_SpriteComp->SetFrameRow(2);
		m_SpriteComp->SetNumberOfFrames(2);
		m_SpriteComp->SetStartFrame(2);

	}
}

void EnemyMovingState::Enter(dae::BasicEnemyComponent& enemy)
{
	m_SpriteComp = enemy.GetSpriteComp();
}

EnemyState* EnemyDyingState::Update(dae::BasicEnemyComponent& enemy, float dt)
{
	//enemy.UpdateSprite();
	UpdateSprites(enemy);
	m_DyingTimer += dt;
	if (m_DyingTimer > m_MaxDyingTime)
	{
		//enemy.SetDyingComplete(true);
		std::cout << "Actual Kill";
		enemy.GetParent()->Delete();
	}

	return nullptr;
}

void EnemyDyingState::UpdateSprites(dae::BasicEnemyComponent& enemy)
{
	m_SpriteComp->SetFrameRow(3);
	m_SpriteComp->SetNumberOfFrames(4);
	m_SpriteComp->SetStartFrame(0);
}

void EnemyDyingState::Enter(dae::BasicEnemyComponent& enemy)
{
	m_SpriteComp = enemy.GetSpriteComp();
	m_MaxDyingTime = 0.3f;
}

EnemyState* EnemyFallingState::Update(dae::BasicEnemyComponent& enemy, float dt)
{
	if (enemy.GetDying())
	{
		return new EnemyDyingState();
	}
	return nullptr;
}
