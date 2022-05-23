#pragma once
#include "MonoBehaviour.h"
#include "Observer.h"
#include "TextComponent.h"
namespace dae
{
	class HealthObserver :
	    public Observer, public MonoBehaviour
	{
	public:
		HealthObserver(TextComponent* textComponent);
		void Notify(const GameObject& go, Event event) override;
		void Update(float dt) override;
		void FixedUpdate(float timestep) override;

	private:
		TextComponent* m_pTextComponent;
	};
	
}

