#include "BasicEnemyComponent.h"

#include <iostream>

void dae::BasicEnemyComponent::Update(float dt)
{
	//std::cout << m_Target->GetTransform().GetPosition().x;
	CheckOverlaps();
	UpdateDirection();
	UpdatePos(dt);
	//if(m_IsOnPlatform == true)
	//{
	//	if(m_Target->GetPosition().x < GetParent()->GetPosition().x)
	//	{
	//		glm::vec3 curPos = GetParent()->GetPosition();
	//		glm::vec3 furPos = glm::vec3(curPos.x - (m_MoveSpeed * dt), curPos.y, 1);
	//		GetParent()->SetPosition(furPos.x, furPos.y);

	//		if (m_IsOnPlatform == false)
	//		{
	//			GetParent()->SetPosition(curPos.x, curPos.y);
	//		}
	//	} else
	//	{
	//		glm::vec3 curPos = GetParent()->GetPosition();
	//		glm::vec3 furPos = glm::vec3(curPos.x + (m_MoveSpeed * dt), curPos.y, 1);
	//		GetParent()->SetPosition(furPos.x, furPos.y);

	//		if (m_IsOnPlatform == false)
	//		{
	//			GetParent()->SetPosition(curPos.x, curPos.y);
	//		}
	//	}
	//}

}

void dae::BasicEnemyComponent::FixedUpdate(float timestep)
{
}

void dae::BasicEnemyComponent::Render() const
{
}

void dae::BasicEnemyComponent::CheckOverlaps()
{
	if (GetParent()->IsOverlappingAnyWithTag("Ladder"))
	{
		//std::cout << "ladder";
		m_IsOnLadder = true;
	}
	else
	{
		m_IsOnLadder = false;
	}

	if (GetParent()->IsOverlappingAnyWithTag("Platform"))
	{
		//std::cout << "platform";
		m_IsOnPlatform = true;
	}
	else
	{
		m_IsOnPlatform = false;
	}
}

void dae::BasicEnemyComponent::UpdatePos(float dt)
{
	glm::vec3 curPos = GetParent()->GetPosition();
	glm::vec3 furPos = glm::vec3(curPos.x + (m_Direction.x * dt), curPos.y + (m_Direction.y * dt), 1);
	GetParent()->SetPosition(furPos.x, furPos.y);

	//glm::vec3 dirNor = m_Direction / m_MoveSpeed;
	//glm::vec3 furPosSize = glm::vec3(curPos.x + (GetParent()->GetSize().x * dirNor.x), curPos.y + (GetParent()->GetSize().y * dirNor.y), 1);
	//GetParent()->SetPosition(furPosSize.x, furPosSize.y); 

	if (m_IsOnPlatform == false)
	{
		GetParent()->SetPosition(curPos.x, curPos.y);
	}
}

void dae::BasicEnemyComponent::UpdateDirection()
{
	if(m_CanSwitch == true)
	{

		//Check if same line
		if(m_IsOnPlatform == true && (abs(m_Target->GetPosition().y - GetParent()->GetPosition().y) < 50.f) )
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
