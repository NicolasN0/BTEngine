#include "ValuesComponent.h"

#include "Observer.h"

int dae::ValuesComponent::m_Lives{ 3 };
int dae::ValuesComponent::m_Score{};
int dae::ValuesComponent::m_Peppers{ 5 };

dae::ValuesComponent::ValuesComponent() : m_pSubject()
{
}

dae::ValuesComponent::~ValuesComponent()
{
	delete m_pSubject;
	m_pSubject = nullptr;
}

void dae::ValuesComponent::Update(float )
{
}

void dae::ValuesComponent::FixedUpdate(float )
{
}

void dae::ValuesComponent::Damage()
{
	m_Lives--;
	m_pSubject->Notify(*GetParent(), Event::PlayerDied);
}

void dae::ValuesComponent::IncreaseScore(int score)
{
	m_Score += score;
	m_pSubject->Notify(*GetParent(), Event::ScoreIncreased);
}

void dae::ValuesComponent::SetSubject(Subject* const subject)
{
	m_pSubject = subject;
}

int dae::ValuesComponent::GetLives() const
{
	return m_Lives;
}

void dae::ValuesComponent::SetLives(int lives)
{
	m_Lives = lives;
}

int dae::ValuesComponent::GetScores() const
{
	return m_Score;
}

int dae::ValuesComponent::GetPeppers() const
{
	return m_Peppers;
}

void dae::ValuesComponent::DecreasePeppers()
{
	m_Peppers--;
	m_pSubject->Notify(*GetParent(), Event::PepperUsed);
}

void dae::ValuesComponent::ResetObserver()
{
	m_pSubject->Notify(*GetParent(), Event::Reset);
}

void dae::ValuesComponent::Reset()
{
	
	m_Lives = 3;
	m_Score = 0;
	m_Peppers = 5;
}
