#include "ContainerComponent.h"

#include <iostream>

dae::ContainerComponent::ContainerComponent(int maxIngredient) : m_IsFilled(), m_MaxIngredient(maxIngredient)
{
}

void dae::ContainerComponent::Update(float dt)
{
	if(m_IsFilled == false)
	{
		if(m_Parent->GetAllOverlappingWithTag("Ingredient").size() == m_MaxIngredient)
		{
			m_IsFilled = true;
			std::cout << "Filled";
		}
	}
}

void dae::ContainerComponent::FixedUpdate(float timestep)
{
}

bool dae::ContainerComponent::GetIsFilled() const
{
	return m_IsFilled;
}


