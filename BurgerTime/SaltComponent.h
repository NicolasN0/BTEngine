#pragma once
#include <MonoBehaviour.h>



namespace dae
{
	class SpriteComponent;

	class SaltComponent final :
	    public MonoBehaviour
	{
	public:
		SaltComponent();
		virtual void Update(float dt) override;
		virtual void FixedUpdate(float timestep) override;

		void SetSpriteComp(SpriteComponent* const comp);
		void UpdateSprite(float dt);
	private:
		SpriteComponent* m_pSpriteComp;
		float m_LifeTime;
		float m_MaxLifeTime;
	};
	
}

