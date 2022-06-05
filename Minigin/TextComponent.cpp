#include "MiniginPCH.h"
#include "TextComponent.h"
#include "FPSComponent.h"
#include <SDL_ttf.h>
#include "Font.h"
#include "Renderer.h"
#include "Texture2D.h"
#include "ResourceManager.h"
dae::TextComponent::TextComponent(const std::string& filename, int size, SDL_Color color) : m_Color{color},m_NeedsUpdate(),m_Counter()
{
	
	m_spFont = ResourceManager::GetInstance().LoadFont(filename,size);
	Initialize();
}

void dae::TextComponent::Initialize() 
{}


void dae::TextComponent::Update(float dt)  
{
	m_Counter += dt;
	if (m_Counter > 1)
	{
		m_NeedsUpdate = true;
	}

	if(m_NeedsUpdate)
	{
		//const SDL_Color color = { 255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_spFont->GetFont(), m_Text.c_str(), m_Color);
		if (surf == nullptr) 
		{
		throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr) 
		{
		throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_spTextTexture = std::make_shared<Texture2D>(texture);
		m_NeedsUpdate = false;
		
	}
};


void dae::TextComponent::Render() const
{
	if (m_spTextTexture != nullptr)
		{
			if(GetParent() != nullptr)
			{
				
				const auto& pos = GetParent()->GetTransform().GetPosition();
				Renderer::GetInstance().RenderTexture(*m_spTextTexture, pos.x, pos.y);
			}
		}
}

void dae::TextComponent::SetText(const std::string& text) 
{
	m_Text = text;
	m_NeedsUpdate = true;
}

