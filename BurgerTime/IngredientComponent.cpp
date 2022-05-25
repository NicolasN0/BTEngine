#include "IngredientComponent.h"
#include "IngredientPartComponent.h"
dae::IngredientComponent::IngredientComponent() : m_FallSpeed{200.f},m_PressedCount{}
{
}

void dae::IngredientComponent::Update(float dt)
{
	if (m_isFalling == true)
	{
		GetParent()->SetPosition(GetParent()->GetPosition().x, GetParent()->GetPosition().y + (m_FallSpeed * dt));
	}

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
		m_isFalling = true;
	}

	if(m_Parent->IsOverlappingAnyWithTag("Platform"))
	{
		//check if last platform is given value otherwise set both last and current
		//if(m_lastPlatformHeight)

		//check if current value is bigger diff then platform size then last value if true reset everything and let stand still
		//before resetting start bouncing function
	}
}

void dae::IngredientComponent::FixedUpdate(float timestep)
{
}

void dae::IngredientComponent::Render() const
{
}
