#pragma once
#include "MonoBehaviour.h"
#include "Observer.h"
#include "TextComponent.h"
namespace dae
{
	class HealthObserver :
	    public Observer
	{
	public:
		HealthObserver(TextComponent* textComponent);
		void Notify(const GameObject& go, Event event) override;
	

	private:
		TextComponent* m_pTextComponent;
	};
	
}

