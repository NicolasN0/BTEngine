#pragma once
#include <MonoBehaviour.h>
namespace dae
{
	
	class EffectComponent :
	    public MonoBehaviour
	{
	public:
		EffectComponent(float lifetime);
		virtual void Update(float dt);
		virtual void FixedUpdate(float timestep);
	private:
		float m_Lifetime;
		float m_MaxLifeTime;
	};
}

