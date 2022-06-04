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
		//void Update(float dt) override;
		//void FixedUpdate(float timestep) override;
	private:
		TextComponent* m_pTextComponent;
	};
	
}

