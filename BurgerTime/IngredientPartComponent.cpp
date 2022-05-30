
#include "IngredientPartComponent.h"

#include <iostream>

#include "IngredientComponent.h"

dae::IngredientPartComponent::IngredientPartComponent() : m_IsPressed(), m_HeightDiff(5.f)
{
}

void dae::IngredientPartComponent::Update(float dt)
{
	//if(m_IsPressed == false)
	//{
	//	if(GetParent()->IsOverlappingAnyWithTag("Player"))
	//	{
	//		/*m_IsPressed = true;
	//		GetParent()->SetPosition(GetParent()->GetLocalPosition().x, GetParent()->GetLocalPosition().y + m_HeightDiff);*/
	//		SetIsPressed(true);
	//	}
	//}
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
	//Only now check for totalcount in ingredient self
	m_Parent->GetParent()->GetComponent<IngredientComponent>()->CheckPressedAmount();
}

void dae::IngredientPartComponent::Reset()
{
	m_IsPressed = false;
	GetParent()->SetPosition(GetParent()->GetLocalPosition().x, GetParent()->GetLocalPosition().y - m_HeightDiff);
}

void dae::IngredientPartComponent::UpdatePressed()
{
	if (m_IsPressed == false)
	{
		if (GetParent()->IsOverlappingAnyWithTag("Player"))
		{
			
			SetIsPressed(true);
		}
	}
}
