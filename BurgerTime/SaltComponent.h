#pragma once
#include <MonoBehaviour.h>

#include "SpriteComponent.h"

namespace dae
{
	class SaltComponent :
	    public MonoBehaviour
	{
	public:
		SaltComponent();
		virtual void Update(float dt);
		virtual void FixedUpdate(float timestep);

		void SetSpriteComp(SpriteComponent* comp);
		void UpdateSprite(float dt);
	private:
		SpriteComponent* m_SpriteComp;
		float m_LifeTime;
		float m_MaxLifeTime;
	};
	
}

