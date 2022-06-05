#pragma once
#include <MonoBehaviour.h>
namespace dae
{
	
	class EffectComponent final:
	    public MonoBehaviour
	{
	public:
		EffectComponent(float lifetime);
		virtual void Update(float dt) override;
		virtual void FixedUpdate(float timestep) override;
	private:
		float m_Lifetime;
		float m_MaxLifeTime;
	};
}

