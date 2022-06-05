#include "EnemyState.h"

#include <iostream>

#include "BasicEnemyComponent.h"
#include "EffectComponent.h"
#include "Scene.h"
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

	
	UpdateSprites(enemy);
	if(enemy.GetIsFalling())
	{
		return new EnemyFallingState();
	}

	
	

	return nullptr;
}

void EnemyStunnedState::UpdateSprites(dae::BasicEnemyComponent& enemy)
{
	switch(enemy.GetType())
	{
	case dae::EEnemyType::Hotdog:
		m_pSpriteComp->SetFrameRow(3);
		m_pSpriteComp->SetNumberOfFrames(2);
		m_pSpriteComp->SetStartFrame(4);
		break;
	case dae::EEnemyType::Pickle:
		m_pSpriteComp->SetFrameRow(5);
		m_pSpriteComp->SetNumberOfFrames(2);
		m_pSpriteComp->SetStartFrame(4);
		break;
	case dae::EEnemyType::Egg:
		m_pSpriteComp->SetFrameRow(7);
		m_pSpriteComp->SetNumberOfFrames(2);
		m_pSpriteComp->SetStartFrame(4);
		break;
	}
}

void EnemyStunnedState::Enter(dae::BasicEnemyComponent& enemy)
{
	m_pSpriteComp = enemy.GetSpriteComp();
	m_MaxStunTime = 2;
}

EnemyState* EnemyMovingState::Update(dae::BasicEnemyComponent& enemy, float dt)
{
	if (enemy.GetDying())
	{
		return new EnemyDyingState();
	}

	if(!m_PlayerCountChecked)
	{
		m_pPlayers = enemy.GetParent()->GetScene()->GetObjectsInWorldWithTag("Player");
		if (m_pPlayers.size() > 1)
		{
			m_UpdateTargets = true;
		}
		m_PlayerCountChecked = true;
	}

	if(m_UpdateTargets)
	{
		SetTarget(enemy);
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
		m_pSpriteComp->SetPaused(true);
	}
	else
	{
		m_pSpriteComp->SetPaused(false);
	}
	dae::EEnemyType type = enemy.GetType();

	if (dir.y > 0)
	{
		switch (type)
		{
		case dae::EEnemyType::Hotdog:
			m_pSpriteComp->SetFrameRow(2);
			m_pSpriteComp->SetNumberOfFrames(2);
			m_pSpriteComp->SetStartFrame(0);
			break;
		case dae::EEnemyType::Pickle:
			m_pSpriteComp->SetFrameRow(4);
			m_pSpriteComp->SetNumberOfFrames(2);
			m_pSpriteComp->SetStartFrame(0);
			break;
		case dae::EEnemyType::Egg:
			m_pSpriteComp->SetFrameRow(6);
			m_pSpriteComp->SetNumberOfFrames(2);
			m_pSpriteComp->SetStartFrame(0);
			break;
		}


	}
	else if (dir.y < 0)
	{
		switch (type)
		{
		case dae::EEnemyType::Hotdog:
			m_pSpriteComp->SetFrameRow(2);
			m_pSpriteComp->SetNumberOfFrames(2);
			m_pSpriteComp->SetStartFrame(4);
			break;
		case dae::EEnemyType::Pickle:
			m_pSpriteComp->SetFrameRow(4);
			m_pSpriteComp->SetNumberOfFrames(2);
			m_pSpriteComp->SetStartFrame(4);
			break;
		case dae::EEnemyType::Egg:
			m_pSpriteComp->SetFrameRow(6);
			m_pSpriteComp->SetNumberOfFrames(2);
			m_pSpriteComp->SetStartFrame(4);
			break;
		}
	}
	else if (dir.x > 0)
	{
		switch (type)
		{
		case dae::EEnemyType::Hotdog:
			m_pSpriteComp->SetFrameRow(2);
			m_pSpriteComp->SetNumberOfFrames(2);
			m_pSpriteComp->SetStartFrame(6);
			break;
		case dae::EEnemyType::Pickle:
			m_pSpriteComp->SetFrameRow(4);
			m_pSpriteComp->SetNumberOfFrames(2);
			m_pSpriteComp->SetStartFrame(9);
			break;
		case dae::EEnemyType::Egg:
			m_pSpriteComp->SetFrameRow(6);
			m_pSpriteComp->SetNumberOfFrames(2);
			m_pSpriteComp->SetStartFrame(9);
			break;
		}


	}
	else if (dir.x < 0)
	{
		switch (type)
		{
		case dae::EEnemyType::Hotdog:
			m_pSpriteComp->SetFrameRow(2);
			m_pSpriteComp->SetNumberOfFrames(2);
			m_pSpriteComp->SetStartFrame(2);
			break;
		case dae::EEnemyType::Pickle:
			m_pSpriteComp->SetFrameRow(4);
			m_pSpriteComp->SetNumberOfFrames(2);
			m_pSpriteComp->SetStartFrame(2);
			break;
		case dae::EEnemyType::Egg:
			m_pSpriteComp->SetFrameRow(6);
			m_pSpriteComp->SetNumberOfFrames(2);
			m_pSpriteComp->SetStartFrame(2);
			break;
		}

	}
}

void EnemyMovingState::Enter(dae::BasicEnemyComponent& enemy)
{
	m_pSpriteComp = enemy.GetSpriteComp();

	
}

void EnemyMovingState::SetTarget(dae::BasicEnemyComponent& enemy)
{
	int index{};
	float maxDist{};


	glm::vec3 pos = enemy.GetParent()->GetPosition();
	for(size_t i{}; i < m_pPlayers.size();i++)
	{
		glm::vec3 playerPos = m_pPlayers.at(i)->GetPosition();
		float dist = sqrtf(powf(pos.x - pos.y, 2) + powf(playerPos.x - playerPos.y, 2));
		if(dist > maxDist)
		{
			maxDist = dist;
			index = static_cast<int>(i);
		}
	}
	enemy.SetTarget(m_pPlayers.at(index));
}

EnemyState* EnemyDyingState::Update(dae::BasicEnemyComponent& enemy, float dt)
{
	UpdateSprites(enemy);
	m_DyingTimer += dt;
	if (m_DyingTimer > m_MaxDyingTime)
	{
		switch(enemy.GetType())
		{
		case dae::EEnemyType::Hotdog:
			{
				SpawnScoreEffect(enemy,0);

			}
			break;
		case dae::EEnemyType::Pickle:
			{
				SpawnScoreEffect(enemy, 1);

			}
			break;
		case dae::EEnemyType::Egg:
			{
				SpawnScoreEffect(enemy, 2);
		
			}
			break;
		}

		std::cout << "Actual Kill";
		enemy.GetParent()->Delete();
	}

	return nullptr;
}

void EnemyDyingState::UpdateSprites(dae::BasicEnemyComponent& enemy)
{
	switch (enemy.GetType())
	{
	case dae::EEnemyType::Hotdog:
		m_pSpriteComp->SetFrameRow(3);
		m_pSpriteComp->SetNumberOfFrames(4);
		m_pSpriteComp->SetStartFrame(0);
		break;
	case dae::EEnemyType::Pickle:
		m_pSpriteComp->SetFrameRow(5);
		m_pSpriteComp->SetNumberOfFrames(4);
		m_pSpriteComp->SetStartFrame(0);
		break;
	case dae::EEnemyType::Egg:
		m_pSpriteComp->SetFrameRow(7);
		m_pSpriteComp->SetNumberOfFrames(4);
		m_pSpriteComp->SetStartFrame(0);
		break;
	}
}

void EnemyDyingState::Enter(dae::BasicEnemyComponent& enemy)
{
	m_pSpriteComp = enemy.GetSpriteComp();
	m_MaxDyingTime = 0.3f;
}

void EnemyDyingState::SpawnScoreEffect(dae::BasicEnemyComponent& enemy, int rarity)
{

	dae::SpriteComponent* effectSprite = new dae::SpriteComponent("PeterPepperSpriteTrans.png", 15, 11);
	dae::GameObject* score = new dae::GameObject();
	score->AddComponent(effectSprite);
	score->SetPosition(enemy.GetParent()->GetPosition());
	score->SetScale(2, 2);
	score->AddComponent<dae::EffectComponent>(new dae::EffectComponent(1));
	effectSprite->SetFrameRow(10);
	effectSprite->SetNumberOfFrames(1);
	effectSprite->SetStartFrame(rarity);
	enemy.GetParent()->GetScene()->Add(score);
}

EnemyState* EnemyFallingState::Update(dae::BasicEnemyComponent& enemy, float )
{
	if (enemy.GetDying())
	{
		return new EnemyDyingState();
	}
	return nullptr;
}
