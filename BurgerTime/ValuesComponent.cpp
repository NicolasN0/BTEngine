#include "ValuesComponent.h"
#include "Observer.h"

int dae::ValuesComponent::m_Lives{ 3 };
int dae::ValuesComponent::m_Score{};

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

void dae::ValuesComponent::Reset()
{
	m_Lives = 3;
	m_Score = 0;
}
