#pragma once
#include "Observer.h"
#include "TextComponent.h"

namespace dae
{
	class ScoreObserver :
	    public Observer
	{
	public:
		ScoreObserver(TextComponent* textComponent);

		void Notify(const GameObject& go, Event event) override;
	
	private:
		TextComponent* m_pTextComponent;
	};
	
}

