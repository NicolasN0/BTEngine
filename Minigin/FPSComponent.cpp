#include "MiniginPCH.h"
#include "FPSComponent.h"
#include "TextComponent.h"
void dae::FPSComponent::Update(float dt) 
{
	m_Frames++;
	m_Gametime += dt;
	if(m_Gametime > 1)
	{
		m_FPS = m_Frames;
		m_Frames = 0;
		m_Gametime = 0.f;
		DisplayText();
	}
	//std::cout << m_FPS;
}

void dae::FPSComponent::FixedUpdate(float timestep)
{
	(timestep);
}

int dae::FPSComponent::GetFPS() const
{
	return m_FPS;
}

void dae::FPSComponent::DisplayText() 
{
	GetParent()->GetComponent<TextComponent>()->SetText(std::to_string(m_FPS));
}