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

void dae::PeterPepperComponent::Update(float)
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
}

void dae::PeterPepperComponent::FixedUpdate(float)
{
}

void dae::PeterPepperComponent::Render() const
{
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

