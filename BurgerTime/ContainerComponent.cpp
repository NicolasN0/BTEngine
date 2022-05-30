#include "ContainerComponent.h"

dae::ContainerComponent::ContainerComponent(int maxIngredient = 3) : m_IsFilled(), m_MaxIngredient(maxIngredient)
{
}

void dae::ContainerComponent::Update(float dt)
{
	if(m_IsFilled == false)
	{
		if(m_Parent->GetAllOverlappingWithTag("Ingredient").size() == 5)
		{
			m_IsFilled = true;
		}
	}
}

bool dae::ContainerComponent::GetIsFilled() const
{
	return m_IsFilled;
}

//void dae::ContainerComponent::SetMaxIngredient(int maxIngredient)
//{
//	m_MaxIngedient = maxIngredient;
//}
