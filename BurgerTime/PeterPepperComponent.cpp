//#include "MiniginPCH.h"
#include "PeterPepperComponent.h"

#include <iostream>

#include "Observer.h"
#include "Scene.h"
#include "SceneChanger.h"
#include "ValuesComponent.h"
dae::PeterPepperComponent::PeterPepperComponent() 
{
	
}

dae::PeterPepperComponent::~PeterPepperComponent()
{
	
}

void dae::PeterPepperComponent::Update(float dt)
{
	//std::cout << std::to_string(GetParent()->GetPosition().x) + ' ' + std::to_string(GetParent()->GetPosition().y) << std::endl;
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
	//m_Movespeed = glm::vec3(0, 0, 0);

}

void dae::PeterPepperComponent::SetMoveSpeed(glm::vec3 movespeed)
{
	m_Movespeed = movespeed;
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
		SceneChanger::GetInstance().SetCurrentScene("highscore");
	}
}

