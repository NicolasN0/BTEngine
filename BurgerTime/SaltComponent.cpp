#include "SaltComponent.h"

#include "BasicEnemyComponent.h"

dae::SaltComponent::SaltComponent() : m_LifeTime() ,m_MaxLifeTime(1),m_pSpriteComp()
{

}

void dae::SaltComponent::Update(float dt)
{
	m_LifeTime += dt;
	UpdateSprite(dt);
	if(m_LifeTime > m_MaxLifeTime)
	{
		GetParent()->Delete();
	}

	for (auto o : m_Parent->GetAllOverlappingWithTag("Enemy"))
	{
		o->GetComponent<BasicEnemyComponent>()->SetStunned(true);
	}
	
}

void dae::SaltComponent::FixedUpdate(float )
{
}

void dae::SaltComponent::SetSpriteComp(SpriteComponent* comp)
{
	m_pSpriteComp = comp;

	m_pSpriteComp->SetFrameRow(3);
	m_pSpriteComp->SetNumberOfFrames(4);
	m_pSpriteComp->SetStartFrame(12);
}

void dae::SaltComponent::UpdateSprite(float )
{
	m_pSpriteComp->SetFrameRow(3);
	m_pSpriteComp->SetNumberOfFrames(4);
	m_pSpriteComp->SetStartFrame(12);
}
