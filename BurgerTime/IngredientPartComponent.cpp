
#include "IngredientPartComponent.h"

#include <iostream>

void dae::IngredientPartComponent::Update(float dt)
{
	if(m_IsPressed == false)
	{
		if(GetParent()->IsOverlappingAnyWithTag("Player"))
		{
			m_IsPressed = true;
			std::cout << "pressed";
			GetParent()->SetPosition(GetParent()->GetLocalPosition().x, GetParent()->GetLocalPosition().y +5.f);
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
}
