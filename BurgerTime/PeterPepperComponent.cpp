//#include "MiniginPCH.h"
#include "PeterPepperComponent.h"

#include <iostream>

#include "Observer.h"
#include "Scene.h"

dae::PeterPepperComponent::PeterPepperComponent() : m_Lives{3}
{
	
}

dae::PeterPepperComponent::~PeterPepperComponent()
{
	if (m_Subject != nullptr)
	{
		delete m_Subject;
		m_Subject = nullptr;

	}
}

void dae::PeterPepperComponent::Update(float)
{

	//if(GetParent()->IsOverlappingAnyWithTag("Ladder"))
	//{
	//	//std::cout << "ladder";
	//	m_IsOnLadder = true;
	//} else
	//{
	//	m_IsOnLadder = false;
	//}

	//if (GetParent()->IsOverlappingAnyWithTag("Platform"))
	//{
	//	//std::cout << "platform";
	//	m_IsOnPlatform = true;
	//} else
	//{
	//	m_IsOnPlatform = false;
	//}

	if (GetParent()->IsCenterOverlappingAnyWithTag("Ladder"))
	{
		//std::cout << "ladder";
		m_IsOnLadder = true;
	}
	else
	{
		m_IsOnLadder = false;
	}

	if (GetParent()->IsCenterOverlappingAnyWithTag("Platform"))
	{
		//std::cout << "platform";
		m_IsOnPlatform = true;
	}
	else
	{
		m_IsOnPlatform = false;
	}
}

void dae::PeterPepperComponent::FixedUpdate(float)
{
}

void dae::PeterPepperComponent::Render() const
{
}

void dae::PeterPepperComponent::SetSubject(Subject* subject)
{
	m_Subject = subject;
}

dae::Subject* dae::PeterPepperComponent::GetSubject()
{
	return m_Subject;
}


void dae::PeterPepperComponent::Damage()
{
	//notify dingetje
	//GetParent()->GetSubject()->Notify(*GetParent(), Event::PlayerDied);
	m_Subject->Notify(*GetParent(), Event::PlayerDied);
	m_Lives--;
}

void dae::PeterPepperComponent::IncreaseScore()
{
	m_Score += 5;
}
