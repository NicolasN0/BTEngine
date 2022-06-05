#include "BasicEnemyComponent.h"
#include "ValuesComponent.h"
#include <iostream>
#include "Scene.h"

dae::BasicEnemyComponent::~BasicEnemyComponent()
{
	delete m_pState;
	m_pState = nullptr;
}

dae::BasicEnemyComponent::BasicEnemyComponent(EEnemyType enemyType, SpriteComponent* const sprite, bool isPlayer) : m_Type{ enemyType }
, m_IsPlayer(isPlayer)
, m_pSpriteComp()
, m_Stunned()
, m_StunTimer()
, m_MaxStunTime(2)
, m_BlockedHor()
, m_BlockedVer()
, m_BlockedCor()
, m_CanSwitchPlatform(true)
, m_CanSwitchLadder(true)
,m_Dying()
,m_DyingComplete()
,m_IsOnLadder()
,m_IsOnPlatform()
,m_Falling()
,m_MoveSpeed(20)
,m_Direction()
,m_PlayerDir()
,m_CanSwitch(true)
,m_LastSwitchCor()
,m_pTarget()
,m_pState()
,m_pSubject()
,m_PrevDir()

{
	m_pSpriteComp = sprite;
	switch (enemyType)
	{
	case EEnemyType::Hotdog:
		m_pSpriteComp->SetFrameRow(2);
		m_pSpriteComp->SetNumberOfFrames(2);
		m_pSpriteComp->SetStartFrame(0);
		break;
	case EEnemyType::Pickle:
		m_pSpriteComp->SetFrameRow(4);
		m_pSpriteComp->SetNumberOfFrames(2);
		m_pSpriteComp->SetStartFrame(0);
		break;
	case EEnemyType::Egg:
		m_pSpriteComp->SetFrameRow(6);
		m_pSpriteComp->SetNumberOfFrames(2);
		m_pSpriteComp->SetStartFrame(0);
		break;
	}
	m_pState = new EnemyMovingState();
	m_pState->Enter(*this);

	
	
}

void dae::BasicEnemyComponent::Update(float dt)
{

	EnemyState* state = m_pState->Update(*this,dt);
	if(state != nullptr)
	{
		delete m_pState;
		m_pState = state;

		m_pState->Enter(*this);
	}


}

void dae::BasicEnemyComponent::FixedUpdate(float )
{
}

void dae::BasicEnemyComponent::Render() const
{
}

bool dae::BasicEnemyComponent::GetIsOnLadder() const
{
	return m_IsOnLadder;
}

bool dae::BasicEnemyComponent::GetIsOnPlatform() const
{
	return m_IsOnPlatform;
}

const glm::vec3& dae::BasicEnemyComponent::GetPosition() const
{
	return m_pParent->GetPosition();
}

void dae::BasicEnemyComponent::SetPosition(const glm::vec3& pos)
{
	m_pParent->SetPosition(pos);
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

void dae::BasicEnemyComponent::SetTarget(GameObject* const target)
{
	m_pTarget = target;
}

void dae::BasicEnemyComponent::Kill()
{
	switch(m_Type)
	{
	case EEnemyType::Hotdog:
		m_pTarget->GetComponent<ValuesComponent>()->IncreaseScore(100);
		break;
	case EEnemyType::Pickle:
		m_pTarget->GetComponent<ValuesComponent>()->IncreaseScore(200);
		break;
	case EEnemyType::Egg:
		m_pTarget->GetComponent<ValuesComponent>()->IncreaseScore(300);
		break;
	default:
		std::cout << "no type selected";
		break;
	}

	m_Dying = true;

}

void dae::BasicEnemyComponent::SetSubject(Subject* const subject)
{
	m_pSubject = subject;
}

void dae::BasicEnemyComponent::SetSpriteComp(SpriteComponent* const comp)
{
	m_pSpriteComp = comp;
	//Give starting frame
	m_pSpriteComp->SetFrameRow(2);
	m_pSpriteComp->SetNumberOfFrames(2);
	m_pSpriteComp->SetStartFrame(0);
}

void dae::BasicEnemyComponent::SetDirection(const glm::vec3& movespeed)
{
	
	m_Direction = movespeed;
}

void dae::BasicEnemyComponent::SetStunned(bool stunned)
{
	m_Stunned = stunned;
	if(stunned)
	{
		//only remember prev if going to stunned
		m_PrevDir = m_Direction;
	}
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

const glm::vec3& dae::BasicEnemyComponent::GetDirection() const
{
	return m_Direction;
}

const glm::vec3& dae::BasicEnemyComponent::GetPrevDir() const
{
	return m_PrevDir;
}

void dae::BasicEnemyComponent::CheckOverlaps()
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
				//test
				m_CanSwitchPlatform = true;

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
				//test
				m_CanSwitchLadder = true;

				m_BlockedHor = true;
				m_BlockedCor = glm::vec3(GetParent()->GetPosition());
				GetParent()->SetPosition(curPos.x, curPos.y);
			}
		}

	}
}

void dae::BasicEnemyComponent::UpdateDirection()
{

	if (m_IsOnPlatform == true && m_IsOnLadder == true)
	{
		m_CanSwitch = true;
	}


	if (m_CanSwitch == true)
	{


		if (m_IsOnPlatform == true && (abs(m_pTarget->GetPosition().y - GetParent()->GetPosition().y) < 5.f) && m_BlockedHor == false)
		{
			if (m_pTarget->GetPosition().x < GetParent()->GetPosition().x)
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

		glm::vec3 futurDir;
		if (m_pTarget->GetPosition().y < GetParent()->GetPosition().y)
		{

			futurDir.y = -m_MoveSpeed;
		}
		else
		{
			futurDir.y = m_MoveSpeed;
		}
		if (m_pTarget->GetPosition().x < GetParent()->GetPosition().x)
		{

			futurDir.x = -m_MoveSpeed;
		}
		else
		{
			futurDir.x = m_MoveSpeed;
		}
		


		if (m_IsOnLadder == true && m_BlockedVer == false && ((futurDir.y == m_Direction.y) || m_CanSwitchLadder == true))
		{
			if (m_pTarget->GetPosition().y < GetParent()->GetPosition().y)
			{

				m_Direction = glm::vec3(0, -m_MoveSpeed, 0);
			}
			else
			{
				m_Direction = glm::vec3(0, m_MoveSpeed, 0);
			}
			m_CanSwitch = false;

			m_LastSwitchCor.x = GetParent()->GetPosition().x;
			
			m_CanSwitchLadder = false;
		}
		else if (m_IsOnPlatform == true && m_BlockedHor == false && ((futurDir.x == m_Direction.x) || m_CanSwitchPlatform == true))
		{
			if (m_pTarget->GetPosition().x < GetParent()->GetPosition().x)
			{

				m_Direction = glm::vec3(-m_MoveSpeed, 0, 0);
			}
			else
			{
				m_Direction = glm::vec3(m_MoveSpeed, 0, 0);
			}
			
			m_CanSwitch = false;

			m_LastSwitchCor.y = GetParent()->GetPosition().y;

			m_CanSwitchPlatform = false;


		}
	}

	if (abs(GetParent()->GetPosition().y - m_BlockedCor.y) > 15)
	{
		m_BlockedHor = false;
	}

	if (abs(GetParent()->GetPosition().x - m_BlockedCor.x) > 15)
	{
		m_BlockedVer = false;
	}

	if(abs(GetParent()->GetPosition().y - m_LastSwitchCor.y) > 10)
	{
		m_CanSwitchPlatform = true;
	}

	if (abs(GetParent()->GetPosition().x - m_LastSwitchCor.x) > 10)
	{
		m_CanSwitchLadder = true;
	}

	
}



dae::SpriteComponent* const dae::BasicEnemyComponent::GetSpriteComp() const
{
	return m_pSpriteComp;
}

bool dae::BasicEnemyComponent::GetDying() const
{
	return m_Dying;
}

void dae::BasicEnemyComponent::SetDyingComplete(bool dyingComplete)
{
	m_DyingComplete = dyingComplete;
}

void dae::BasicEnemyComponent::SetCanSwitch(bool canSwitch)
{
	m_CanSwitch = canSwitch;
}

void dae::BasicEnemyComponent::SetPrevDir(const glm::vec3& prevDir)
{
	m_PrevDir = prevDir;
}

bool dae::BasicEnemyComponent::GetDyingComplete() const
{
	return m_DyingComplete;
}



void dae::BasicEnemyComponent::SetHorizontalDir()
{
	if (m_pTarget->GetPosition().x < GetParent()->GetPosition().x)
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
	if (m_pTarget->GetPosition().y < GetParent()->GetPosition().y)
	{

		m_Direction = glm::vec3(0, -m_MoveSpeed, 0);
	}
	else
	{
		m_Direction = glm::vec3(0, m_MoveSpeed, 0);
	}
	m_CanSwitch = false;
}
