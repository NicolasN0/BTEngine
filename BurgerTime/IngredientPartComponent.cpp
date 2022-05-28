
#include "IngredientPartComponent.h"

#include <iostream>

dae::IngredientPartComponent::IngredientPartComponent() : m_IsPressed(), m_HeightDiff(5.f)
{
}

void dae::IngredientPartComponent::Update(float dt)
{
	if(m_IsPressed == false)
	{
		if(GetParent()->IsOverlappingAnyWithTag("Player"))
		{
			m_IsPressed = true;
			GetParent()->SetPosition(GetParent()->GetLocalPosition().x, GetParent()->GetLocalPosition().y + m_HeightDiff);
		}
	}
}

void dae::IngredientPartComponent::FixedUpdate(float timestep)
{
}

void dae::IngredientPartComponent::Render() const
{
}

bool dae::IngredientPartComponent::GetIsPressed() const
{
	return m_IsPressed;
}

void dae::IngredientPartComponent::SetIsPressed(bool isPressed)
{
	m_IsPressed = isPressed;
	GetParent()->SetPosition(GetParent()->GetLocalPosition().x, GetParent()->GetLocalPosition().y + m_HeightDiff);
}

void dae::IngredientPartComponent::Reset()
{
	m_IsPressed = false;
	GetParent()->SetPosition(GetParent()->GetLocalPosition().x, GetParent()->GetLocalPosition().y - m_HeightDiff);
}
