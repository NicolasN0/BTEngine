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
,m_TotalFallingEnemies{}
,m_ValuesComp{}
{
	
}

void dae::IngredientComponent::Update(float dt)
{
	if(m_ValuesComp == nullptr)
	{
		InitializeValuesComp();
	}

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
		//Should only happen once per enemyFill
		if(m_HasMoved == false)
		{
			std::vector<GameObject*> allEnemies = m_Parent->GetAllOverlappingWithTag("Enemy");

			for(auto o : allEnemies)
			{
				if(o->GetComponent<BasicEnemyComponent>()->GetIsFalling() == false)
				{
					m_FallingEnemies.push_back(o);
					o->GetComponent<BasicEnemyComponent>()->SetIsFalling(true);
				}
			}
			m_StandingEnemies = m_FallingEnemies.size();
			m_TotalFallingEnemies = m_FallingEnemies.size();
			
		}
		m_HasMoved = true;
		m_isFalling = true;
	}


	CheckCollisionPlatform();
	
	CheckCollisionIngredient();

	Bounce(dt);

	if(m_isFalling == false && m_isBouncing == false)
	{
		if(m_StandingEnemies > 0)
		{
			m_StandingEnemies--;
			InstantLetFall();
		} else if(m_StandingEnemies == 0 && m_FallingEnemies.size() > 0)
		{
			/*for(auto o : m_FallingEnemies)
			{
				o->GetComponent<BasicEnemyComponent>()->Kill();
			}
			m_FallingEnemies.clear();
			m_HasMoved = false;
			m_TotalFallingEnemies = 0;*/
			KillStandingEnemies();
		}
		
	}


	CheckCollisionEnemy();
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
			
			if(other->GetPosition().y > m_Parent->GetPosition().y)
			{

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
	m_ValuesComp->IncreaseScore(50);
	
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
	if(m_isFalling == true || m_isBouncing == true)
	{
		std::vector<GameObject*> overlapping = m_Parent->GetAllOverlappingWithTag("Enemy");
		//get all of them and check if not falling and if not kill them
		for(auto o : overlapping)
		{
			BasicEnemyComponent* enemy = o->GetComponent<BasicEnemyComponent>();
			if(enemy->GetIsFalling() == false)
			{
				enemy->Kill();
			}
		}

	}
}

void dae::IngredientComponent::Bounce(float dt)
{
	
	if(m_isBouncing == true)
	{
		
		if(m_BouncingDown == false)
		{
			m_CurrentBounceHeight += m_BounceSpeed * dt;
			m_Parent->SetPosition(m_Parent->GetPosition().x, m_Parent->GetPosition().y - m_BounceSpeed *dt);
			//Move enemies too
			for (auto o : m_FallingEnemies)
			{
				o->SetPosition(o->GetPosition().x, o->GetPosition().y - m_BounceSpeed * dt);
			}
			
		} else
		{
			m_CurrentBounceHeight -= m_BounceSpeed * dt;
			m_Parent->SetPosition(m_Parent->GetPosition().x, m_Parent->GetPosition().y + m_BounceSpeed * dt);
			//Move enemies too
			for (auto o : m_FallingEnemies)
			{
				o->SetPosition(o->GetPosition().x, o->GetPosition().y + m_BounceSpeed * dt);
			}
		}

		if(m_CurrentBounceHeight > m_MaxBounceHeight)
		{
			m_BouncingDown = true;
		}

		

		if(m_CurrentBounceHeight < 0)
		{
			m_BouncingDown = false;
			m_isBouncing = false;
			m_CurrentBounceHeight = 0;
			std::cout << "bounceDone";
		}
		
	}

}

void dae::IngredientComponent::InitializeValuesComp()
{
	m_ValuesComp = m_Parent->GetScene()->GetObjectsInWorldWithTag("Player").at(0)->GetComponent<ValuesComponent>();
	if (m_ValuesComp == nullptr)
	{
		std::cout << "Cant find player";
	}
}

void dae::IngredientComponent::KillStandingEnemies()
{
	switch (m_TotalFallingEnemies)
	{
	case 1: 
		m_ValuesComp->IncreaseScore(500);
		break;
	case 2:
		m_ValuesComp->IncreaseScore(1000);
		break;
	case 3:
		m_ValuesComp->IncreaseScore(2000);
		break;
	case 4:
		m_ValuesComp->IncreaseScore(4000);
		break;
	case 5:
		m_ValuesComp->IncreaseScore(8000);
		break;
	case 6:
		m_ValuesComp->IncreaseScore(16000);
		break;

	default:
		m_ValuesComp->IncreaseScore(0);
		break;
	}


	for (auto o : m_FallingEnemies)
	{
		o->GetComponent<BasicEnemyComponent>()->Kill();
	}
	m_FallingEnemies.clear();
	m_HasMoved = false;
	m_TotalFallingEnemies = 0;
}
