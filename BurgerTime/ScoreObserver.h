#pragma once
#include "Observer.h"
#include "TextComponent.h"

namespace dae
{
	class ScoreObserver final:
	    public Observer
	{
	public:
		ScoreObserver(TextComponent* const textComponent);

		void Notify(const GameObject& go, Event event) override;
	
	private:
		TextComponent* m_pTextComponent;
	};
	
}

