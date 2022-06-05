#pragma once
#include "Observer.h"
#include "TextComponent.h"

namespace dae
{
	
	
	class PepperObserver final:
		public Observer
	{
	public:
		PepperObserver(TextComponent* const textComponent);

		void Notify(const GameObject& go, Event event) override;
	
	private:
		TextComponent* m_pTextComponent;
	};
}

