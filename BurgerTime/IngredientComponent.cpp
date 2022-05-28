#include "IngredientComponent.h"

#include <iostream>

#include "IngredientPartComponent.h"
#include "BasicEnemyComponent.h"
dae::IngredientComponent::IngredientComponent() : m_FallSpeed{200.f}
,m_PressedCount{}
,m_curPlatformHeight{}
,m_lastPlatformHeight{}
,m_PlatformSize{}
,m_inContainer{}
,m_isFalling{}
,m_isBouncing{}
,m_IngredientSize{}
, m_isCollected{}
,m_StandingEnemies{}
,m_HasMoved{}
,m_CurrentBounceHeight{}
,m_MaxBounceHeight{10.f}
,m_BounceSpeed{50.f}
{
}

void dae::IngredientComponent::Update(float dt)
{
	if (m_inContainer == false)
	{
		CheckContainerOverlap();
	}


	if (m_isFalling == true)
	{
		GetParent()->SetPosition(GetParent()->GetPosition().x, GetParent()->GetPosition().y + (m_FallSpeed * dt));

		//Also move all enemies with it below
		for(auto o : m_FallingEnemies)
		{
			o->SetPosition(o->GetPosition().x, o->GetPosition().y + (m_FallSpeed * dt));
		}
	}


	//Update pressed count and let fall if all
	m_PressedCount = 0;
	for(auto c : m_Parent->GetChilds())
	{
		
		IngredientPartComponent* part = c->GetComponent<IngredientPartComponent>();
		if(part != nullptr)
		{
			if(part->GetIsPressed() == true)
			{
				
				m_PressedCount++;
			}

		}
	}
	if(m_PressedCount == m_Parent->GetChildCount())
	{
		//Add the enemies to the list if they were already overlapping otherwise check for overlap later and destroy them
		//Should only happen once
		if(m_HasMoved == false)
		{
			std::vector<GameObject*> allEnemies = m_Parent->GetAllOverlappingWithTag("Enemy");

			//Check if not from other already set to is falling
			for(auto o : allEnemies)
			{
				if(o->GetComponent<BasicEnemyComponent>()->GetIsFalling() == false)
				{
					m_FallingEnemies.push_back(o);
					o->GetComponent<BasicEnemyComponent>()->SetIsFalling(true);
				}
			}
			m_StandingEnemies = m_FallingEnemies.size();
			
		}
		m_HasMoved = true;
		m_isFalling = true;
	}


	CheckCollisionPlatform();
	
	CheckCollisionIngredient();

	if(m_isFalling == false)
	{
		if(m_StandingEnemies > 0)
		{
			std::cout << "oh lord";
			m_StandingEnemies--;
			InstantLetFall();
		}
		
	}


	//test
	Bounce(dt);
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

void dae::IngredientComponent::InstantLetFall()
{

	SetIsFalling(true);
	for (auto c : m_Parent->GetChilds())
	{
		c->GetComponent<IngredientPartComponent>()->SetIsPressed(true);
	}
}

void dae::IngredientComponent::CheckCollisionIngredient()
{

	if (m_Parent->IsOverlappingAnyWithTag("Ingredient"))
	{
		if(m_inContainer == false)
		{
			GameObject* other = m_Parent->GetFirstOverlappingObjectWithTag("Ingredient");
			//if bigger (so lower) let the other fall
			if(other->GetPosition().y > m_Parent->GetPosition().y)
			{
				//Should not only set to falling true but also lower the is pressed vor everyChild
				//Else Resetting will always set ingredients higher

				//Check for is falling so it doenst get called multiple times
				if(other->GetComponent<IngredientComponent>()->GetIsFalling() == false)
				{
		
					other->GetComponent<IngredientComponent>()->InstantLetFall();
					
				}

			}
		} else
		{
			if(m_isCollected == false)
			{
				ResetFalling();
			}
		}
	}
}

void dae::IngredientComponent::CheckContainerOverlap()
{
	if (m_Parent->IsOverlappingAnyWithTag("Container"))
	{
		m_inContainer = true;
	}
}

void dae::IngredientComponent::ResetFalling()
{
	if(m_inContainer == true)
	{
		m_isCollected = true;
	}

	for (auto c : m_Parent->GetChilds())
	{
		c->GetComponent<IngredientPartComponent>()->Reset();
	}
	m_isFalling = false;
	m_PressedCount = 0;
	m_lastPlatformHeight = m_curPlatformHeight;

	//test
	m_isBouncing = true;
}

void dae::IngredientComponent::CheckCollisionPlatform()
{
	if (m_Parent->IsOverlappingAnyWithTag("Platform"))
	{
		//check if last platform is given value otherwise set both last and current
		//Check for 0 because initialized on 0
		if (m_lastPlatformHeight == 0 && m_curPlatformHeight == 0)
		{
			//Set to parent position + size because bottom parent will be top ingredient
			m_curPlatformHeight = m_Parent->GetPosition().y + m_Parent->GetSize().y;
			m_lastPlatformHeight = m_curPlatformHeight;
		}

		//If not both 0 set new platformheight
		m_curPlatformHeight = m_Parent->GetPosition().y + m_Parent->GetSize().y;

		//If platform size is not initialized get it
		if (m_PlatformSize == 0)
		{
			m_PlatformSize = m_Parent->GetFirstOverlappingObjectWithTag("Platform")->GetSize().y;
		}

		//IngredientSize
		if (m_IngredientSize == 0)
		{
			m_IngredientSize = m_Parent->GetChildAt(0)->GetSize().y;
		}
		//before resetting start bouncing function


		//check if current value is bigger diff then platform size then last value if true reset everything and let stand still
		if ((m_curPlatformHeight - m_lastPlatformHeight) > (m_PlatformSize + m_IngredientSize))
		{

			ResetFalling();
		}

	}
}

void dae::IngredientComponent::CheckCollisionEnemy()
{
	if(m_isFalling == true)
	{
		std::vector<GameObject*> overlapping;
		//get all of them and check if not falling and if not kill them

	}
}

void dae::IngredientComponent::Bounce(float dt)
{
	//m_isBouncing = true;
	if(m_isBouncing == true)
	{
		if(m_BouncingDown == false)
		{
			m_CurrentBounceHeight += m_BounceSpeed * dt;
			m_Parent->SetPosition(m_Parent->GetPosition().x, m_Parent->GetPosition().y - m_BounceSpeed *dt);
			
		} else
		{
			m_CurrentBounceHeight -= m_BounceSpeed * dt;
			m_Parent->SetPosition(m_Parent->GetPosition().x, m_Parent->GetPosition().y + m_BounceSpeed * dt);
		}

		if(m_CurrentBounceHeight > m_MaxBounceHeight)
		{
			m_BouncingDown = true;
		}


		if(m_CurrentBounceHeight < 0)
		{
			m_BouncingDown = false;
			m_isBouncing = false;
		}
		
	}

}
