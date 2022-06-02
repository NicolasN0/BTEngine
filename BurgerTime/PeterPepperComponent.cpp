//#include "MiniginPCH.h"
#include "PeterPepperComponent.h"

#include <iostream>

#include "Observer.h"
#include "Scene.h"
#include "SceneChanger.h"
#include "ValuesComponent.h"
dae::PeterPepperComponent::PeterPepperComponent() : m_SpriteComp()
{
	
}

dae::PeterPepperComponent::~PeterPepperComponent()
{
	
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

	if(m_Parent->IsOverlappingAnyWithTag("Enemy") == true)
	{
		Respawn();
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

void dae::PeterPepperComponent::SetMoveSpeed(glm::vec3 movespeed)
{
	m_Movespeed = movespeed;
}

void dae::PeterPepperComponent::SetSpriteComp(SpriteComponent* comp)
{
	m_SpriteComp = comp;
	InitializeSprite();
}

void dae::PeterPepperComponent::UpdateSprite(float dt)
{
	if(m_Movespeed.y == 0 && m_Movespeed.x == 0)
	{
		m_SpriteComp->SetPaused(true);
	} else
	{
		m_SpriteComp->SetPaused(false);
	}

	if(m_Movespeed.y > 0)
	{
		//set framerow
		m_SpriteComp->SetFrameRow(0);
		m_SpriteComp->SetNumberOfFrames(3);
		m_SpriteComp->SetStartFrame(0);
		//m_SpriteComp->SetFlip(false);

	} else if(m_Movespeed.y < 0)
	{
		m_SpriteComp->SetFrameRow(0);
		m_SpriteComp->SetNumberOfFrames(3);
		m_SpriteComp->SetStartFrame(6);
		//m_SpriteComp->SetFlip(false);
	} else if(m_Movespeed.x > 0)
	{
		m_SpriteComp->SetFrameRow(0);
		m_SpriteComp->SetNumberOfFrames(3);
		m_SpriteComp->SetStartFrame(9);
		//m_SpriteComp->SetFlip(true);
		//if(!m_IsFlipped)
		//{
		//	m_SpriteComp->SetFlip(true);
		//	//m_IsFlipped = true;
		//} 
	
	}
	else if (m_Movespeed.x < 0)
	{
		m_SpriteComp->SetFrameRow(0);
		m_SpriteComp->SetNumberOfFrames(3);
		m_SpriteComp->SetStartFrame(3);
		//m_SpriteComp->SetFlip(false);
	}
}

void dae::PeterPepperComponent::Respawn()
{
	if(m_Parent->GetComponent<ValuesComponent>()->GetLives() > 0)
	{
		//Damage();
		m_Parent->GetComponent<ValuesComponent>()->Damage();
		m_Parent->SetPosition(m_StartPos);
	} else
	{
		m_Parent->GetComponent<ValuesComponent>()->SetLives(3);
		SceneChanger::GetInstance().SetCurrentScene("highscore");
	}
}

void dae::PeterPepperComponent::InitializeSprite()
{
	std::vector<int> framesPerRow{ 9,9,6,6,6,6,6,6,3,6,9 };
	m_SpriteComp->SetFramesPerRow(framesPerRow);
}

