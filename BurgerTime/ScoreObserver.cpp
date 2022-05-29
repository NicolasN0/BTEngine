//#include "MiniginPCH.h"
#include "ScoreObserver.h"

dae::ScoreObserver::ScoreObserver(TextComponent* textComponent) : m_pTextComponent(textComponent)
{
	//textComponent->SetParent(GetParent());
}

void dae::ScoreObserver::Notify(const GameObject& , Event event)
{
	switch(event)
	{
	case Event::PlayerPickup:
		m_pTextComponent->SetText("Score increased");
		break;
	case Event::HotDogKilled:
		//m_pTextComponent->SetText()
		break;
	}
}

void dae::ScoreObserver::Update(float )
{
}

void dae::ScoreObserver::FixedUpdate(float )
{
}
