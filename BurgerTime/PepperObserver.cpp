#include "PepperObserver.h"

#include "ValuesComponent.h"


dae::PepperObserver::PepperObserver(TextComponent* textComponent) : m_pTextComponent(textComponent)
{
	
}

void dae::PepperObserver::Notify(const GameObject& go, Event event)
{
	switch (event)
	{
	case Event::PepperUsed:
		m_pTextComponent->SetText(std::to_string(go.GetComponent<ValuesComponent>()->GetPeppers()));
		break;
	case Event::Reset:
		m_pTextComponent->SetText(std::to_string(go.GetComponent<ValuesComponent>()->GetPeppers()));
		break;
	}
}
