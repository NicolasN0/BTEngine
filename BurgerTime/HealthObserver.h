#pragma once
#include "Observer.h"
#include "TextComponent.h"
namespace dae
{
	class HealthObserver final:
	    public Observer
	{
	public:
		HealthObserver(TextComponent* const textComponent);
		void Notify(const GameObject& go, Event event) override;
	

	private:
		TextComponent* m_pTextComponent;
	};
	
}

