#include "ValuesComponent.h"

#include <iostream>

#include "Observer.h"

int dae::ValuesComponent::m_Lives{ 3 };
int dae::ValuesComponent::m_Score{};
int dae::ValuesComponent::m_Peppers{ 5 };

dae::ValuesComponent::~ValuesComponent()
{
	delete m_Subject;
	m_Subject = nullptr;
}

void dae::ValuesComponent::Update(float dt)
{
}

void dae::ValuesComponent::FixedUpdate(float timestep)
{
}

void dae::ValuesComponent::Damage()
{
	std::cout << "dam" << std::endl;
	m_Lives--;
	m_Subject->Notify(*GetParent(), Event::PlayerDied);
}

void dae::ValuesComponent::IncreaseScore(int score)
{
	m_Score += score;
	m_Subject->Notify(*GetParent(), Event::ScoreIncreased);
}

void dae::ValuesComponent::SetSubject(Subject* subject)
{
	m_Subject = subject;
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
}

void dae::ValuesComponent::ResetObserver()
{
	m_Subject->Notify(*GetParent(), Event::Reset);
}

void dae::ValuesComponent::Reset()
{
	
	m_Lives = 3;
	m_Score = 0;
	m_Peppers = 5;
}
