//#include "MiniginPCH.h"
#include "HealthObserver.h"
#include "PeterPepperComponent.h"
dae::HealthObserver::HealthObserver(TextComponent* textComponent) : m_pTextComponent(textComponent)
{
	//textComponent->SetParent(GetParent());
}

void dae::HealthObserver::Notify(const GameObject& go, Event event)
{
	switch(event)
	{
	case Event::PlayerDied:
		m_pTextComponent->SetText(std::to_string(go.GetComponent<PeterPepperComponent>()->GetLives()));
		//m_pTextComponent->SetText("2");
		break;
	}
}

void dae::HealthObserver::Update(float )
{
}

void dae::HealthObserver::FixedUpdate(float )
{
}
