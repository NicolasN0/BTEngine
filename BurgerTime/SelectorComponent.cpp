#include "SelectorComponent.h"

void dae::SelectorComponent::Update(float dt)
{
}

void dae::SelectorComponent::FixedUpdate(float timestep)
{
}

void dae::SelectorComponent::NextGameMode()
{
	m_Selected++;
}

void dae::SelectorComponent::PreviousGameMode()
{
	m_Selected--;
}

int dae::SelectorComponent::GetSelected()
{
	return m_Selected;
}
