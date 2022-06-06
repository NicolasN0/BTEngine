#include "ContainerComponent.h"


dae::ContainerComponent::ContainerComponent(int maxIngredient) : m_IsFilled(), m_MaxIngredient(maxIngredient)
{
}

void dae::ContainerComponent::Update(float )
{
	if(m_IsFilled == false)
	{
		if(m_pParent->GetAllOverlappingWithTag("Ingredient").size() == static_cast<size_t>(m_MaxIngredient))
		{
			m_IsFilled = true;
		}
	}
}

void dae::ContainerComponent::FixedUpdate(float )
{
}

bool dae::ContainerComponent::GetIsFilled() const
{
	return m_IsFilled;
}


