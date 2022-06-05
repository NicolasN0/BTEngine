
#include "PeterPepperComponent.h"

#include <iostream>
#include "SpriteComponent.h"
#include "BasicEnemyComponent.h"
#include "HighscoreManager.h"
#include "Locator.h"
#include "SaltComponent.h"
#include "Scene.h"
#include "SceneChanger.h"
#include "ValuesComponent.h"
dae::PeterPepperComponent::PeterPepperComponent() : m_pSpriteComp()
,m_pAudioService()
,m_IsOnLadder()
,m_IsOnPlatform()
,m_NextLevelTest()
,m_IsFlipped()
,m_IsFacingRight()
,m_StartPos(110,100,0)
{
	m_pAudioService = Locator::getAudio();
}



void dae::PeterPepperComponent::Update(float dt)
{
	
	if (GetParent()->IsCenterOverlappingAnyWithTag("Ladder"))
	{
		m_IsOnLadder = true;
	}
	else
	{
		m_IsOnLadder = false;
	}

	if (GetParent()->IsCenterOverlappingAnyWithTag("Platform"))
	{
		m_IsOnPlatform = true;
	}
	else
	{
		m_IsOnPlatform = false;
	}

	if(m_pParent->IsOverlappingAnyWithTag("Enemy") == true)
	{
		if(m_pParent->GetFirstOverlappingObjectWithTag("Enemy")->GetComponent<BasicEnemyComponent>()->GetStunned() == false)
		{
			
			Respawn();
		}
	}

	UpdatePos(dt);
	UpdateSprite(dt);
}

void dae::PeterPepperComponent::FixedUpdate(float)
{
}

void dae::PeterPepperComponent::Render() const
{
}

bool dae::PeterPepperComponent::GetIsOnLadder() const
{
	return m_IsOnLadder;
}

bool dae::PeterPepperComponent::GetIsOnPlatform() const
{
	return m_IsOnPlatform;
}

bool dae::PeterPepperComponent::GetNextLevel() const
{
	return m_NextLevelTest;
}

void dae::PeterPepperComponent::SetNextLevel(bool nextLevel)
{
	m_NextLevelTest = nextLevel;
}


void dae::PeterPepperComponent::UpdatePos(float dt)
{
	if (m_Movespeed.y > 0 || m_Movespeed.y < 0)
	{
		if (GetIsOnLadder() == true)
		{
			glm::vec3 curPos = GetParent()->GetTransform().GetPosition();
			glm::vec3 furPos = glm::vec3(curPos.x + (m_Movespeed.x * dt), curPos.y + (m_Movespeed.y * dt), 1);


			GetParent()->SetPosition(furPos.x, furPos.y);

			if (GetParent()->IsCenterOverlappingAnyWithTag("Ladder") == false)
			{
				GetParent()->SetPosition(curPos.x, curPos.y);
			}
		}

	}

	if (m_Movespeed.x > 0 || m_Movespeed.x < 0)
	{
		if (GetIsOnPlatform() == true)
		{
			glm::vec3 curPos = GetParent()->GetTransform().GetPosition();
			glm::vec3 furPos = glm::vec3(curPos.x + (m_Movespeed.x * dt), curPos.y + (m_Movespeed.y * dt), 1);
			GetParent()->SetPosition(furPos.x, furPos.y);

			if (GetParent()->IsCenterOverlappingAnyWithTag("Platform") == false)
			{
				GetParent()->SetPosition(curPos.x, curPos.y);

			}

		}
	}
	

}

void dae::PeterPepperComponent::SetMoveSpeed(const glm::vec3& movespeed)
{
	m_Movespeed = movespeed;
	if(m_Movespeed.x < 0)
	{
		m_IsFacingRight = false;
	}

	if( m_Movespeed.x > 0)
	{
		m_IsFacingRight = true;
	}
}

void dae::PeterPepperComponent::SetSpriteComp(SpriteComponent* const comp)
{
	m_pSpriteComp = comp;
	InitializeSprite();
}

void dae::PeterPepperComponent::ThrowSalt() const
{
	ValuesComponent* values = GetParent()->GetComponent<ValuesComponent>();
	if(values->GetPeppers() > 0)
	{
		m_pAudioService->SetEffectVolume(10);
		int soundId;
		soundId = m_pAudioService->LoadSound("../Data/Sounds/Salt.wav");
		m_pAudioService->playSound(soundId);


		GameObject* salt = new GameObject;
		salt->AddComponent<SaltComponent>(new SaltComponent());
		salt->AddComponent<SpriteComponent>(new SpriteComponent("PeterPepperSpriteTrans.png", 15, 11));
		salt->GetComponent<SaltComponent>()->SetSpriteComp(salt->GetComponent<SpriteComponent>());
		if(m_IsFacingRight)
		{
			salt->SetPosition(GetParent()->GetPosition().x + 10, GetParent()->GetPosition().y);
		}else
		{
			salt->SetPosition(GetParent()->GetPosition().x - 10, GetParent()->GetPosition().y);
		}
		salt->SetScale(1.5f, 1.5f);
		GetParent()->GetScene()->Add(salt);

		values->DecreasePeppers();
		std::cout << values->GetPeppers();
	}
}

void dae::PeterPepperComponent::UpdateSprite(float )
{
	if(m_Movespeed.y == 0 && m_Movespeed.x == 0)
	{
		m_pSpriteComp->SetPaused(true);
	} else
	{
		m_pSpriteComp->SetPaused(false);
	}

	if(m_Movespeed.y > 0)
	{
		m_pSpriteComp->SetFrameRow(0);
		m_pSpriteComp->SetNumberOfFrames(3);
		m_pSpriteComp->SetStartFrame(0);
		

	} else if(m_Movespeed.y < 0)
	{
		m_pSpriteComp->SetFrameRow(0);
		m_pSpriteComp->SetNumberOfFrames(3);
		m_pSpriteComp->SetStartFrame(6);
		
	} else if(m_Movespeed.x > 0)
	{
		m_pSpriteComp->SetFrameRow(0);
		m_pSpriteComp->SetNumberOfFrames(3);
		m_pSpriteComp->SetStartFrame(9);

	}
	else if (m_Movespeed.x < 0)
	{
		m_pSpriteComp->SetFrameRow(0);
		m_pSpriteComp->SetNumberOfFrames(3);
		m_pSpriteComp->SetStartFrame(3);
		
	}
}

void dae::PeterPepperComponent::Respawn() const
{
	if(m_pParent->GetComponent<ValuesComponent>()->GetLives() > 0)
	{
		m_pParent->GetComponent<ValuesComponent>()->Damage();
		m_pParent->SetPosition(m_StartPos);
	} else
	{
		//PushBack score
		HighscoreManager::GetInstance().AddHighscore(m_pParent->GetComponent<ValuesComponent>()->GetScores());
		SceneChanger::GetInstance().SetCurrentScene("highscore");
	}
}

void dae::PeterPepperComponent::InitializeSprite() const
{
	std::vector<int> framesPerRow{ 9,9,6,6,6,6,6,6,3,6,9 };
	m_pSpriteComp->SetFramesPerRow(framesPerRow);
}

