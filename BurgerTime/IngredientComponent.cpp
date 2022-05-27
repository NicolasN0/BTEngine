#include "IngredientComponent.h"

#include <iostream>

#include "IngredientPartComponent.h"
dae::IngredientComponent::IngredientComponent() : m_FallSpeed{200.f},m_PressedCount{}, m_curPlatformHeight{},m_lastPlatformHeight{},m_PlatformSize{}
{
}

void dae::IngredientComponent::Update(float dt)
{
	if (m_isFalling == true)
	{
		GetParent()->SetPosition(GetParent()->GetPosition().x, GetParent()->GetPosition().y + (m_FallSpeed * dt));
	}


	//Update pressed count and let fall if all
	m_PressedCount = 0;
	for(auto c : m_Parent->GetChilds())
	{
		if(c->GetComponent<IngredientPartComponent>()->GetIsPressed() == true)
		{
			m_PressedCount++;

		}
	}
	if(m_PressedCount == m_Parent->GetChildCount())
	{
		//std::cout << "FALL" << std::endl;
		m_isFalling = true;
	}


	if(m_Parent->IsOverlappingAnyWithTag("Platform"))
	{
		//check if last platform is given value otherwise set both last and current
		//Check for 0 because initialized on 0
		if(m_lastPlatformHeight == 0 && m_curPlatformHeight == 0)
		{
			//Set to parent position + size because bottom parent will be top ingredient
			m_curPlatformHeight = m_Parent->GetPosition().y + m_Parent->GetSize().y;
			m_lastPlatformHeight = m_curPlatformHeight;
		}

		//If not both 0 set new platformheight
		m_curPlatformHeight = m_Parent->GetPosition().y + m_Parent->GetSize().y;

		//If platform size is not initialized get it
		if(m_PlatformSize == 0)
		{
			m_PlatformSize = m_Parent->GetFirstOverlappingObjectWithTag("Platform")->GetSize().y;
		}

		//IngredientSize
		if(m_IngredientSize == 0)
		{
			m_IngredientSize = m_Parent->GetChildAt(0)->GetSize().y;
		}
		//before resetting start bouncing function


		//check if current value is bigger diff then platform size then last value if true reset everything and let stand still
		if((m_curPlatformHeight - m_lastPlatformHeight) > (m_PlatformSize + m_IngredientSize))
		{
			//std::cout << "Reset" << std::endl;;
			for(auto c : m_Parent->GetChilds())
			{
				c->GetComponent<IngredientPartComponent>()->SetIsPressed(false);
			}
			m_isFalling = false;
			m_PressedCount = 0;
			m_lastPlatformHeight = m_curPlatformHeight;
		}
	}

	CheckCollisionIngredient();
}

void dae::IngredientComponent::FixedUpdate(float timestep)
{
}

void dae::IngredientComponent::Render() const
{
}

bool dae::IngredientComponent::GetIsFalling() const
{
	return m_isFalling;
}

void dae::IngredientComponent::SetIsFalling(bool isFalling)
{
	m_isFalling = isFalling;
}

void dae::IngredientComponent::CheckCollisionIngredient()
{
	if (m_Parent->IsOverlappingAnyWithTag("Ingredient"))
	{
		GameObject* other = m_Parent->GetFirstOverlappingObjectWithTag("Ingredient");
		//if bigger (so lower) let the other fall
		if(other->GetPosition().y > m_Parent->GetPosition().y)
		{
			//std::cout << "happens";
			other->GetComponent<IngredientComponent>()->SetIsFalling(true);
		}
	}
}
