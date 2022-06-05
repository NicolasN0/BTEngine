#include "BasicEnemyComponent.h"
#include "ValuesComponent.h"
#include <iostream>

#include "EnemyState.h"

dae::BasicEnemyComponent::~BasicEnemyComponent()
{
	delete m_State;
	m_State = nullptr;
}

dae::BasicEnemyComponent::BasicEnemyComponent(EEnemyType enemyType,  SpriteComponent* sprite, bool isPlayer) : m_Type{enemyType} , m_IsPlayer(isPlayer),m_SpriteComp(),m_Stunned(),m_StunTimer(),m_MaxStunTime(2)
,m_BlockedHor()
,m_BlockedVer()
,m_BlockedCor()
,m_CanSwitchPlatform(true)
,m_CanSwitchLadder(true)
{
	m_SpriteComp = sprite;
	switch (enemyType)
	{
	case EEnemyType::Hotdog:
		m_SpriteComp->SetFrameRow(2);
		m_SpriteComp->SetNumberOfFrames(2);
		m_SpriteComp->SetStartFrame(0);
		break;
	case EEnemyType::Pickle:
		m_SpriteComp->SetFrameRow(4);
		m_SpriteComp->SetNumberOfFrames(2);
		m_SpriteComp->SetStartFrame(0);
		break;
	case EEnemyType::Egg:
		m_SpriteComp->SetFrameRow(6);
		m_SpriteComp->SetNumberOfFrames(2);
		m_SpriteComp->SetStartFrame(0);
		break;
	}
	m_State = new EnemyMovingState();
	m_State->Enter(*this);
}

void dae::BasicEnemyComponent::Update(float dt)
{
	/*if(m_Falling == false)
	{
		if(!m_Stunned)
		{
			
			CheckOverlaps();
			if(m_IsPlayer == false)
			{

				UpdateDirection();
			}
			UpdatePos(dt);
		}
		UpdateSprite();
		
	}

	if(m_Stunned)
	{
		m_StunTimer += dt;
		if(m_StunTimer > m_MaxStunTime)
		{
			m_Stunned = false;
			m_StunTimer = 0;
		}
	}*/
	
	//State Test
	EnemyState* state = m_State->Update(*this,dt);
	if(state != nullptr)
	{
		delete m_State;
		m_State = state;

		m_State->Enter(*this);
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

dae::EEnemyType dae::BasicEnemyComponent::GetType() const
{
	return m_Type;
}

void dae::BasicEnemyComponent::Kill()
{
	std::cout << "toDying";
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

	m_Dying = true;

	//m_Parent->~GameObject();
}

void dae::BasicEnemyComponent::SetSubject(Subject* subject)
{
	m_Subject = subject;
}

void dae::BasicEnemyComponent::SetSpriteComp(SpriteComponent* comp)
{
	m_SpriteComp = comp;
	//Give starting frame
	m_SpriteComp->SetFrameRow(2);
	m_SpriteComp->SetNumberOfFrames(2);
	m_SpriteComp->SetStartFrame(0);
}

void dae::BasicEnemyComponent::SetDirection(glm::vec3 movespeed)
{
	std::cout << "applies";
	//m_PlayerDir = movespeed;
	m_Direction = movespeed;
}

void dae::BasicEnemyComponent::SetStunned(bool stunned)
{
	m_Stunned = stunned;
	m_Direction = glm::vec3(0, 0, 0);
}

bool dae::BasicEnemyComponent::GetStunned() const
{
	return m_Stunned;
}

bool dae::BasicEnemyComponent::GetIsPlayer() const
{
	return m_IsPlayer;
}

glm::vec3 dae::BasicEnemyComponent::GetDirection() const
{
	return m_Direction;
}

void dae::BasicEnemyComponent::CheckOverlaps()
{
	if (GetParent()->IsCenterOverlappingAnyWithTag("Ladder"))
	{
		//std::cout << "ladder" << std::endl;
		m_IsOnLadder = true;
	}
	else
	{
		m_IsOnLadder = false;
	}

	if (GetParent()->IsCenterOverlappingAnyWithTag("Platform"))
	{
		//std::cout << "platform" << std::endl;
		m_IsOnPlatform = true;
	}
	else
	{
		m_IsOnPlatform = false;
	}
}

void dae::BasicEnemyComponent::UpdatePos(float dt)
{

	
	if (m_Direction.y > 0 || m_Direction.y < 0)
	{
		if (m_IsOnLadder == true)
		{
			glm::vec3 curPos = GetParent()->GetTransform().GetPosition();
			glm::vec3 furPos = glm::vec3(curPos.x + (m_Direction.x * dt), curPos.y + (m_Direction.y * dt), 1);


			GetParent()->SetPosition(furPos.x, furPos.y);

			if (GetParent()->IsCenterOverlappingAnyWithTag("Ladder") == false)
			{
				m_BlockedVer = true;
				m_BlockedCor = glm::vec3(GetParent()->GetPosition());
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
				m_BlockedHor = true;
				m_BlockedCor = glm::vec3(GetParent()->GetPosition());
				GetParent()->SetPosition(curPos.x, curPos.y);
			}
		}

	}
}

void dae::BasicEnemyComponent::UpdateDirection()
{
	//if(m_IsOnPlatform == true && m_IsOnLadder == true)
	//{
	//	m_CanSwitch = true;
	//}


	//if(m_CanSwitch == true)
	//{

	//	//Check if same line
	//	if(m_IsOnPlatform == true && (abs(m_Target->GetPosition().y - GetParent()->GetPosition().y) < 5.f) )
	//	{
	//		if (m_Target->GetPosition().x < GetParent()->GetPosition().x)
	//		{

	//			m_Direction = glm::vec3(-m_MoveSpeed, 0, 0);
	//		}
	//		else
	//		{
	//			m_Direction = glm::vec3(m_MoveSpeed, 0, 0);
	//		}

	//		//Return so it doesnt constantly checks
	//		return;
	//	}


	//	if(m_IsOnLadder == true)
	//	{
	//		if(m_Target->GetPosition().y < GetParent()->GetPosition().y)
	//		{
	//			
	//			m_Direction = glm::vec3(0, -m_MoveSpeed, 0);
	//		} else
	//		{
	//			m_Direction = glm::vec3(0, m_MoveSpeed, 0);
	//		}
	//		//Return so it doesnt constantly checks
	//		m_CanSwitch = false;
	//		//return;

	//	} else if(m_IsOnPlatform == true)
	//	{
	//		if (m_Target->GetPosition().x < GetParent()->GetPosition().x)
	//		{

	//			m_Direction = glm::vec3(-m_MoveSpeed, 0, 0);
	//		}
	//		else
	//		{
	//			m_Direction = glm::vec3(m_MoveSpeed, 0, 0);
	//		}

	//		
	//		m_CanSwitch = false;
	//		//return;
	//		
	//	}
	//}


	//Test

	if(m_IsOnPlatform == true && m_IsOnLadder == true)
	{
		m_CanSwitch = true;
	}


	if(m_CanSwitch == true)
	{

		
		if(m_IsOnPlatform == true && (abs(m_Target->GetPosition().y - GetParent()->GetPosition().y) < 5.f) && m_BlockedHor == false)
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



		if(m_IsOnLadder == true && m_BlockedVer == false)
		{
			if(m_Target->GetPosition().y < GetParent()->GetPosition().y)
			{
				
				m_Direction = glm::vec3(0, -m_MoveSpeed, 0);
			} else
			{
				m_Direction = glm::vec3(0, m_MoveSpeed, 0);
			}
			m_CanSwitch = false;

		} else if(m_IsOnPlatform == true && m_BlockedHor == false)
		{
			if (m_Target->GetPosition().x < GetParent()->GetPosition().x)
			{

				m_Direction = glm::vec3(-m_MoveSpeed, 0, 0);
			}
			else
			{
				m_Direction = glm::vec3(m_MoveSpeed, 0, 0);
			}

			
			m_CanSwitch = false;
			
		}
	}

	if(abs(GetParent()->GetPosition().y - m_BlockedCor.y) > 15)
	{
		m_BlockedHor = false;
	}

	if (abs(GetParent()->GetPosition().x - m_BlockedCor.y) > 15)
	{
		m_BlockedVer = false;
	}


	//test2
	//if (m_IsOnPlatform == true && m_IsOnLadder == true)
	//{
	//	m_CanSwitch = true;
	//}


	//if (m_CanSwitch == true)
	//{


	//	if (m_IsOnPlatform == true && (abs(m_Target->GetPosition().y - GetParent()->GetPosition().y) < 5.f) && m_BlockedHor == false)
	//	{
	//		if (m_Target->GetPosition().x < GetParent()->GetPosition().x)
	//		{

	//			m_Direction = glm::vec3(-m_MoveSpeed, 0, 0);
	//		}
	//		else
	//		{
	//			m_Direction = glm::vec3(m_MoveSpeed, 0, 0);
	//		}

	//		//Return so it doesnt constantly checks
	//		return;
	//	}

	//	//test
	//	glm::vec3 futurDir;
	//	if (m_Target->GetPosition().y < GetParent()->GetPosition().y)
	//	{

	//		futurDir.y = -m_MoveSpeed;
	//	}
	//	else
	//	{
	//		futurDir.y = m_MoveSpeed;
	//	}
	//	if (m_Target->GetPosition().x < GetParent()->GetPosition().x)
	//	{

	//		futurDir.x = -m_MoveSpeed;
	//	}
	//	else
	//	{
	//		futurDir.x = m_MoveSpeed;
	//	}
	//	//test


	//	if (m_IsOnLadder == true && m_BlockedVer == false && ((futurDir.y == m_Direction.y) || m_CanSwitchLadder == true))
	//	{
	//		if (m_Target->GetPosition().y < GetParent()->GetPosition().y)
	//		{

	//			m_Direction = glm::vec3(0, -m_MoveSpeed, 0);
	//		}
	//		else
	//		{
	//			m_Direction = glm::vec3(0, m_MoveSpeed, 0);
	//		}
	//		m_CanSwitch = false;
	//		//Only set self to false and other one later to true if coordinates turn out wel
	//		//m_CanSwitchPlatform = true;
	//		m_LastSwitchCor.x = GetParent()->GetPosition().x;


	//		m_CanSwitchLadder = false;
	//	}
	//	else if (m_IsOnPlatform == true && m_BlockedHor == false && ((futurDir.x == m_Direction.x) || m_CanSwitchPlatform == true))
	//	{
	//		if (m_Target->GetPosition().x < GetParent()->GetPosition().x)
	//		{

	//			m_Direction = glm::vec3(-m_MoveSpeed, 0, 0);
	//		}
	//		else
	//		{
	//			m_Direction = glm::vec3(m_MoveSpeed, 0, 0);
	//		}
	//		//m_CanSwitchLadder = true;
	//		m_LastSwitchCor.y = GetParent()->GetPosition().y;


	//		m_CanSwitchPlatform = false;

	//		m_CanSwitch = false;

	//	}
	//}

	//if (abs(GetParent()->GetPosition().y - m_BlockedCor.y) > 15)
	//{
	//	m_BlockedHor = false;
	//}

	//if (abs(GetParent()->GetPosition().x - m_BlockedCor.y) > 15)
	//{
	//	m_BlockedVer = false;
	//}

	//if(abs(GetParent()->GetPosition().y - m_LastSwitchCor.y) > 15)
	//{
	//	m_CanSwitchPlatform = true;
	//}

	//if (abs(GetParent()->GetPosition().x - m_LastSwitchCor.x) > 15)
	//{
	//	m_CanSwitchLadder = true;
	//}
	
}

void dae::BasicEnemyComponent::UpdateSprite()
{
	if(m_Stunned)
	{
		m_SpriteComp->SetFrameRow(3);
		m_SpriteComp->SetNumberOfFrames(2);
		m_SpriteComp->SetStartFrame(4);
	}

	if (m_Direction.y == 0 && m_Direction.x == 0 && m_Stunned == false)
	{
		m_SpriteComp->SetPaused(true);
	}
	else
	{
		m_SpriteComp->SetPaused(false);
	}

	if (m_Direction.y > 0)
	{
	
		m_SpriteComp->SetFrameRow(2);
		m_SpriteComp->SetNumberOfFrames(2);
		m_SpriteComp->SetStartFrame(0);
		

	}
	else if (m_Direction.y < 0)
	{
		m_SpriteComp->SetFrameRow(2);
		m_SpriteComp->SetNumberOfFrames(2);
		m_SpriteComp->SetStartFrame(4);
	}
	else if (m_Direction.x > 0)
	{
		m_SpriteComp->SetFrameRow(2);
		m_SpriteComp->SetNumberOfFrames(2);
		m_SpriteComp->SetStartFrame(2);
		

	}
	else if (m_Direction.x < 0)
	{
		m_SpriteComp->SetFrameRow(2);
		m_SpriteComp->SetNumberOfFrames(2);
		m_SpriteComp->SetStartFrame(2);
		
	}
}

dae::SpriteComponent* dae::BasicEnemyComponent::GetSpriteComp()
{
	return m_SpriteComp;
}

bool dae::BasicEnemyComponent::GetDying() const
{
	return m_Dying;
}

void dae::BasicEnemyComponent::SetDyingComplete(bool dyingComplete)
{
	m_DyingComplete = dyingComplete;
}

bool dae::BasicEnemyComponent::GetDyingComplete()
{
	return m_DyingComplete;
}

void dae::BasicEnemyComponent::SetHorizontalDir()
{
	if (m_Target->GetPosition().x < GetParent()->GetPosition().x)
	{

		m_Direction = glm::vec3(-m_MoveSpeed, 0, 0);
	}
	else
	{
		m_Direction = glm::vec3(m_MoveSpeed, 0, 0);
	}

	m_CanSwitch = false;
}

void dae::BasicEnemyComponent::SetVerticalDir()
{
	if (m_Target->GetPosition().y < GetParent()->GetPosition().y)
	{

		m_Direction = glm::vec3(0, -m_MoveSpeed, 0);
	}
	else
	{
		m_Direction = glm::vec3(0, m_MoveSpeed, 0);
	}
	m_CanSwitch = false;
}
