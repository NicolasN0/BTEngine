#include "SelectorComponent.h"

dae::SelectorComponent::SelectorComponent() : m_Selected()
{
}

void dae::SelectorComponent::Update(float )
{
}

void dae::SelectorComponent::FixedUpdate(float )
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

int dae::SelectorComponent::GetSelected() const
{
	return m_Selected;
}
