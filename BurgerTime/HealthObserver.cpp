#include "HealthObserver.h"
#include "PeterPepperComponent.h"
#include "ValuesComponent.h"
dae::HealthObserver::HealthObserver(TextComponent* const textComponent) : m_pTextComponent(textComponent)
{
}

void dae::HealthObserver::Notify(const GameObject& go, Event event)
{
	switch(event)
	{
	case Event::PlayerDied:
		m_pTextComponent->SetText(std::to_string(go.GetComponent<ValuesComponent>()->GetLives()));
		break;
	case Event::Reset:
		m_pTextComponent->SetText(std::to_string(go.GetComponent<ValuesComponent>()->GetLives()));
		break;
	}
}
