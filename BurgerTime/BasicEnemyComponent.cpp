#include "BasicEnemyComponent.h"
#include "ValuesComponent.h"
#include <iostream>

dae::BasicEnemyComponent::BasicEnemyComponent(EEnemyType enemyType, bool isPlayer) : m_Type{enemyType} , m_IsPlayer(isPlayer)
{
}

void dae::BasicEnemyComponent::Update(float dt)
{
	if(m_Falling == false)
	{
		CheckOverlaps();
		if(m_IsPlayer == false)
		{

			UpdateDirection();
			UpdatePos(dt);
		}

		
	}


}

void dae::BasicEnemyComponent::FixedUpdate(float )
{
}

void dae::BasicEnemyComponent::Render() const
{
}

glm::vec3 dae::BasicEnemyComponent::GetPosition() const
{
	return m_Parent->GetPosition();
}

void dae::BasicEnemyComponent::SetPosition(glm::vec3 pos)
{
	m_Parent->SetPosition(pos);
}



void dae::BasicEnemyComponent::SetIsFalling(bool isFalling)
{
	m_Falling = isFalling;
}

bool dae::BasicEnemyComponent::GetIsFalling() const
{
	return m_Falling;
}

void dae::BasicEnemyComponent::Kill()
{
	std::cout << "kill";
	switch(m_Type)
	{
	case EEnemyType::Hotdog:
		m_Target->GetComponent<ValuesComponent>()->IncreaseScore(100);
		break;
	case EEnemyType::Pickle:
		m_Target->GetComponent<ValuesComponent>()->IncreaseScore(200);
		break;
	case EEnemyType::Egg:
		m_Target->GetComponent<ValuesComponent>()->IncreaseScore(300);
		break;
	default:
		std::cout << "no type selected";
		break;
	}

	m_Parent->~GameObject();
}

void dae::BasicEnemyComponent::SetSubject(Subject* subject)
{
	m_Subject = subject;
}

void dae::BasicEnemyComponent::CheckOverlaps()
{
	if (GetParent()->IsCenterOverlappingAnyWithTag("Ladder"))
	{
		std::cout << "ladder" << std::endl;
		m_IsOnLadder = true;
	}
	else
	{
		m_IsOnLadder = false;
	}

	if (GetParent()->IsCenterOverlappingAnyWithTag("Platform"))
	{
		std::cout << "platform" << std::endl;
		m_IsOnPlatform = true;
	}
	else
	{
		m_IsOnPlatform = false;
	}
}

void dae::BasicEnemyComponent::UpdatePos(float dt)
{

	/*glm::vec3 curPos = GetParent()->GetPosition();
	glm::vec3 furPos = glm::vec3(curPos.x + (m_Direction.x * dt), curPos.y + (m_Direction.y * dt), 1);
	GetParent()->SetPosition(furPos.x, furPos.y);*/


	/*if(m_Direction.x > 0 || m_Direction.x < 0)
	{
		if (m_IsOnPlatform == false)
		{
			GetParent()->SetPosition(curPos.x, curPos.y);
			m_CanSwitch = true;
		}
	}

	if (m_Direction.y > 0 || m_Direction.y < 0)
	{
		if (m_IsOnLadder == false)
		{
			GetParent()->SetPosition(curPos.x, curPos.y);
			m_CanSwitch = true;
		}
	}*/
	if (m_Direction.y > 0 || m_Direction.y < 0)
	{
		if (m_IsOnLadder == true)
		{
			glm::vec3 curPos = GetParent()->GetTransform().GetPosition();
			glm::vec3 furPos = glm::vec3(curPos.x + (m_Direction.x * dt), curPos.y + (m_Direction.y * dt), 1);


			GetParent()->SetPosition(furPos.x, furPos.y);

			if (GetParent()->IsCenterOverlappingAnyWithTag("Ladder") == false)
			{
				GetParent()->SetPosition(curPos.x, curPos.y);
			}
		}

	}

	if (m_Direction.x > 0 || m_Direction.x < 0)
	{
		if (m_IsOnPlatform == true)
		{
			glm::vec3 curPos = GetParent()->GetTransform().GetPosition();
			glm::vec3 furPos = glm::vec3(curPos.x + (m_Direction.x * dt), curPos.y + (m_Direction.y * dt), 1);


			GetParent()->SetPosition(furPos.x, furPos.y);

			if (GetParent()->IsCenterOverlappingAnyWithTag("Platform") == false)
			{
				GetParent()->SetPosition(curPos.x, curPos.y);
			}
		}

	}
}

void dae::BasicEnemyComponent::UpdateDirection()
{
	if(m_IsOnPlatform == true && m_IsOnLadder == true)
	{
		m_CanSwitch = true;
	}


	if(m_CanSwitch == true)
	{

		//Check if same line
		if(m_IsOnPlatform == true && (abs(m_Target->GetPosition().y - GetParent()->GetPosition().y) < 5.f) )
		{
			if (m_Target->GetPosition().x < GetParent()->GetPosition().x)
			{

				m_Direction = glm::vec3(-m_MoveSpeed, 0, 0);
			}
			else
			{
				m_Direction = glm::vec3(m_MoveSpeed, 0, 0);
			}

			//Return so it doesnt constantly checks
			return;
		}


		if(m_IsOnLadder == true)
		{
			if(m_Target->GetPosition().y < GetParent()->GetPosition().y)
			{
				
				m_Direction = glm::vec3(0, -m_MoveSpeed, 0);
			} else
			{
				m_Direction = glm::vec3(0, m_MoveSpeed, 0);
			}
			//Return so it doesnt constantly checks
			m_CanSwitch = false;
			//return;

		} else if(m_IsOnPlatform == true)
		{
			if (m_Target->GetPosition().x < GetParent()->GetPosition().x)
			{

				m_Direction = glm::vec3(-m_MoveSpeed, 0, 0);
			}
			else
			{
				m_Direction = glm::vec3(m_MoveSpeed, 0, 0);
			}

			//Return so it doesnt constantly checks
			m_CanSwitch = false;
			//return;
			
		}
	}
}
