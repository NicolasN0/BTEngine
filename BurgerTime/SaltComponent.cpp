#include "SaltComponent.h"

#include "BasicEnemyComponent.h"

dae::SaltComponent::SaltComponent() : m_LifeTime() ,m_MaxLifeTime(1)
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

void dae::SaltComponent::FixedUpdate(float timestep)
{
}

void dae::SaltComponent::SetSpriteComp(SpriteComponent* comp)
{
	m_SpriteComp = comp;

	m_SpriteComp->SetFrameRow(3);
	m_SpriteComp->SetNumberOfFrames(4);
	m_SpriteComp->SetStartFrame(12);
}

void dae::SaltComponent::UpdateSprite(float dt)
{
	m_SpriteComp->SetFrameRow(3);
	m_SpriteComp->SetNumberOfFrames(4);
	m_SpriteComp->SetStartFrame(12);
}
