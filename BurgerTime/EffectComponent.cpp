#include "EffectComponent.h"

dae::EffectComponent::EffectComponent(float lifetime) : m_Lifetime()
, m_MaxLifeTime(lifetime)
{
}

void dae::EffectComponent::Update(float dt)
{
	m_Lifetime += dt;
	if(m_Lifetime > m_MaxLifeTime)
	{
		GetParent()->Delete();
	}
}

void dae::EffectComponent::FixedUpdate(float )
{
}
