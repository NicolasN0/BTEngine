#include "ValuesComponent.h"
#include "Observer.h"

void dae::ValuesComponent::Update(float dt)
{
}

void dae::ValuesComponent::FixedUpdate(float timestep)
{
}

void dae::ValuesComponent::Damage()
{
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

int dae::ValuesComponent::GetScores() const
{
	return m_Score;
}
