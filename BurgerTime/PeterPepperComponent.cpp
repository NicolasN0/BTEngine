//#include "MiniginPCH.h"
#include "PeterPepperComponent.h"

#include <iostream>

#include "Observer.h"
#include "Scene.h"
#include "ValuesComponent.h"
dae::PeterPepperComponent::PeterPepperComponent() 
{
	
}

dae::PeterPepperComponent::~PeterPepperComponent()
{
	/*if (m_Subject != nullptr)
	{
		delete m_Subject;
		m_Subject = nullptr;

	}*/
}

void dae::PeterPepperComponent::Update(float)
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
}

void dae::PeterPepperComponent::FixedUpdate(float)
{
}

void dae::PeterPepperComponent::Render() const
{
}

//void dae::PeterPepperComponent::SetSubject(Subject* subject)
//{
//	m_Subject = subject;
//}
//
//dae::Subject* dae::PeterPepperComponent::GetSubject()
//{
//	return m_Subject;
//}

void dae::PeterPepperComponent::Respawn()
{
	if(m_Parent->GetComponent<ValuesComponent>()->GetLives() > 0)
	{
		//Damage();
		m_Parent->GetComponent<ValuesComponent>()->Damage();
		m_Parent->SetPosition(m_StartPos);
	} /*else
	{
		m_Subject->Notify(*GetParent(), Event::GameOver);
	}*/
}


//void dae::PeterPepperComponent::Damage()
//{
//	
//	m_Lives--;
//	m_Subject->Notify(*GetParent(), Event::PlayerDied);
//}
//
//void dae::PeterPepperComponent::IncreaseScore()
//{
//	m_Score += 5;
//}
