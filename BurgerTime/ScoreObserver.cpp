#include "ScoreObserver.h"
#include "PeterPepperComponent.h"
#include "ValuesComponent.h"
dae::ScoreObserver::ScoreObserver(TextComponent* const textComponent) : m_pTextComponent(textComponent)
{
	
}

void dae::ScoreObserver::Notify(const GameObject& go, Event event)
{
	switch(event)
	{
	case Event::PlayerPickup:
		m_pTextComponent->SetText("Score increased");
		break;
	case Event::ScoreIncreased:
		m_pTextComponent->SetText(std::to_string(go.GetComponent<ValuesComponent>()->GetScores()));
		break;
	case Event::Reset:
 		m_pTextComponent->SetText(std::to_string(go.GetComponent<ValuesComponent>()->GetScores()));
		break;
	
	}
}

