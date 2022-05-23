//#include "MiniginPCH.h"
#include "PeterPepperComponent.h"

#include <iostream>

#include "Observer.h"
#include "Scene.h"

dae::PeterPepperComponent::PeterPepperComponent() : m_Lives{3}
{
	
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

void dae::PeterPepperComponent::Damage()
{
	//notify dingetje
	GetParent()->GetSubject()->Notify(*GetParent(), Event::PlayerDied);
	m_Lives--;
}

void dae::PeterPepperComponent::IncreaseScore()
{
	m_Score += 5;
}
