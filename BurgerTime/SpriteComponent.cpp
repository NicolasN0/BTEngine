#include "SpriteComponent.h"

#include <SDL_render.h>

#include "Renderer.h"
#include "ResourceManager.h"
#include "Texture2D.h"

dae::SpriteComponent::SpriteComponent(const std::string& filename,int spritesW,int spritesH) : m_SpritesW(spritesW)
,m_SpritesH(spritesH)
,m_NrFramesPerSec(10)
,m_spTexture()
,m_NrOfFrames()
,m_Framerow()
,m_Paused()
,m_Flip()
,m_StartFrame()
,m_FramesPerRow()
,m_AnimTime()
,m_AnimFrame()
{
	m_spTexture = ResourceManager::GetInstance().LoadTexture(filename);

	int w;
	int h;
	SDL_QueryTexture(m_spTexture->GetSDLTexture(), nullptr, nullptr, &w, &h);
	SetSize(glm::vec3(w/ m_SpritesW, h/ m_SpritesH, 1));
	
	
	
}

void dae::SpriteComponent::Update(float dt)
{


	float timePerFrame{ 1.0f / m_NrFramesPerSec };

	if(!m_Paused)
	{
		m_AnimTime += dt;

		if (m_AnimTime >= timePerFrame) {
			m_AnimTime = 0.0f;
			if(m_NrOfFrames != 0)
			{
				
				++m_AnimFrame %= m_NrOfFrames;
			}

		}
	}
}

void dae::SpriteComponent::FixedUpdate(float )
{
}

void dae::SpriteComponent::Render() const
{


	//Sprite
	const auto& pos = GetParent()->GetTransform().GetPosition();
	const auto& scale = GetParent()->GetTransform().GetScale();
	SDL_Rect destRect;
	destRect.x = static_cast<int>(pos.x);
	destRect.y = static_cast<int>(pos.y);
	SDL_QueryTexture(m_spTexture->GetSDLTexture(), nullptr, nullptr, &destRect.w, &destRect.h);
	


	int w;
	int h;
	SDL_QueryTexture(m_spTexture->GetSDLTexture(), nullptr, nullptr, &w, &h);

	float srcW = static_cast<float>(w / m_SpritesW);
	float srcH = static_cast<float>(h / m_SpritesH);

	destRect.w = static_cast<int>(srcW * scale.x);
	destRect.h = static_cast<int>(srcH * scale.y);
	SDL_Rect srcRect{};


	srcRect.w = static_cast<int>(srcW);
	srcRect.h = static_cast<int>(srcH);
	srcRect.x = (m_AnimFrame + m_StartFrame) * static_cast<int>(srcW);
	srcRect.y = m_Framerow * static_cast<int>(srcH);

	SDL_Point point;
	
	SDL_RendererFlip flip;

	flip = SDL_FLIP_NONE;
	SDL_RenderCopyEx(Renderer::GetInstance().GetSDLRenderer(), m_spTexture->GetSDLTexture(), &srcRect, &destRect, 0, &point, flip);



}

void dae::SpriteComponent::SetNumberOfFrames(int number)
{
	m_NrOfFrames = number;
}

void dae::SpriteComponent::SetFrameRow(int row)
{

	m_Framerow = row;
}

void dae::SpriteComponent::SetFramesPerRow(const std::vector<int>& framesPerRow)
{
	m_FramesPerRow = framesPerRow;
}

void dae::SpriteComponent::SetStartFrame(int number)
{
	m_StartFrame = number;
}

void dae::SpriteComponent::SetPaused(bool pause)
{
	m_Paused = pause;
}

void dae::SpriteComponent::SetFlip(bool flip)
{
	m_Flip = flip;
}
