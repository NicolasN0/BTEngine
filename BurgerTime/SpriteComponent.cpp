#include "SpriteComponent.h"

#include <SDL_render.h>

#include "Renderer.h"
#include "ResourceManager.h"
#include "Texture2D.h"

dae::SpriteComponent::SpriteComponent(const std::string& filename,int spritesW,int spritesH) : m_SpritesW(spritesW),m_SpritesH(spritesH)
,m_NrFramesPerSec(10)
,m_IsFlipped()

{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);

	int w;
	int h;
	SDL_QueryTexture(m_Texture->GetSDLTexture(), nullptr, nullptr, &w, &h);
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

void dae::SpriteComponent::FixedUpdate(float timestep)
{
}

void dae::SpriteComponent::Render() const
{


	//Sprite
	const auto& pos = GetParent()->GetTransform().GetPosition();
	const auto& scale = GetParent()->GetTransform().GetScale();
	SDL_Rect destRect;
	destRect.x = pos.x;
	destRect.y = pos.y;
	SDL_QueryTexture(m_Texture->GetSDLTexture(), nullptr, nullptr, &destRect.w, &destRect.h);
	/*destRect.w = destRect.w * scale.x;
	destRect.h = destRect.h * scale.y;*/


	int w;
	int h;
	SDL_QueryTexture(m_Texture->GetSDLTexture(), nullptr, nullptr, &w, &h);

	float srcW = w / m_SpritesW;
	float srcH = h / m_SpritesH;

	destRect.w = srcW * scale.x;
	destRect.h = srcH * scale.y;
	SDL_Rect srcRect{};


	srcRect.w = srcW;
	srcRect.h = srcH;
	srcRect.x = (m_AnimFrame + m_StartFrame) * srcW;
	srcRect.y = m_Framerow * srcH;

	SDL_Point point;
	
	SDL_RendererFlip flip;
	/*if(m_Flip)
	{

		flip = SDL_FLIP_HORIZONTAL;
		
		
	} else
	{
		flip = SDL_FLIP_NONE;
	}*/
	flip = SDL_FLIP_NONE;
	SDL_RenderCopyEx(Renderer::GetInstance().GetSDLRenderer(), m_Texture->GetSDLTexture(), &srcRect, &destRect, 0, &point, flip);



}

void dae::SpriteComponent::SetNumberOfFrames(int number)
{
	m_NrOfFrames = number;
}

void dae::SpriteComponent::SetFrameRow(int row)
{

	m_Framerow = row;
	//m_NrOfFrames = m_FramesPerRow.at(row);
}

void dae::SpriteComponent::SetFramesPerRow(std::vector<int> framesPerRow)
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
