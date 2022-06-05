
#include "IngredientPartComponent.h"

#include <iostream>

#include "IngredientComponent.h"
#include "Locator.h"

dae::IngredientPartComponent::IngredientPartComponent() : m_IsPressed(), m_HeightDiff(5.f)
{
	m_pAudioService = Locator::getAudio();
}

void dae::IngredientPartComponent::Update(float )
{

}

void dae::IngredientPartComponent::FixedUpdate(float )
{
}

void dae::IngredientPartComponent::Render() const
{
}

bool dae::IngredientPartComponent::GetIsPressed() const
{
	return m_IsPressed;
}

void dae::IngredientPartComponent::SetIsPressed(bool isPressed)
{
	m_pAudioService->SetEffectVolume(10);
	int soundId;
	soundId = m_pAudioService->LoadSound("../Data/Sounds/Press.wav");
	m_pAudioService->playSound(soundId);

	m_IsPressed = isPressed;
	GetParent()->SetPosition(GetParent()->GetLocalPosition().x, GetParent()->GetLocalPosition().y + m_HeightDiff);
	//Only now check for totalcount in ingredient self
	m_pParent->GetParent()->GetComponent<IngredientComponent>()->CheckPressedAmount();
}

void dae::IngredientPartComponent::Reset()
{
	m_IsPressed = false;
	GetParent()->SetPosition(GetParent()->GetLocalPosition().x, GetParent()->GetLocalPosition().y - m_HeightDiff);
}

void dae::IngredientPartComponent::UpdatePressed()
{
	if (m_IsPressed == false)
	{
		if (GetParent()->IsOverlappingAnyWithTag("Player"))
		{
			
			SetIsPressed(true);
		}
	}
}
