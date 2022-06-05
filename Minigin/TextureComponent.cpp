#include "MiniginPCH.h"
#include "TextureComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Texture2D.h"

dae::TextureComponent::TextureComponent(const std::string& filename)
{
	m_spTexture = ResourceManager::GetInstance().LoadTexture(filename);
	
	int w;
	int h;
	SDL_QueryTexture(m_spTexture->GetSDLTexture(), nullptr, nullptr, &w, &h);
	SetSize(glm::vec3(w, h, 1));


}

void dae::TextureComponent::Render() const
{
	const auto& pos = GetParent()->GetTransform().GetPosition();
	const auto& scale = GetParent()->GetTransform().GetScale();
	
	SDL_Rect destRect;
	destRect.x = static_cast<int>(pos.x);
	destRect.y = static_cast<int>(pos.y);
	SDL_QueryTexture(m_spTexture->GetSDLTexture(), nullptr, nullptr, &destRect.w, &destRect.h);

	destRect.w = static_cast<int>(destRect.w * scale.x);
	destRect.h = static_cast<int>(destRect.h * scale.y);

	
	SDL_RenderCopy(Renderer::GetInstance().GetSDLRenderer(), m_spTexture->GetSDLTexture(), nullptr, &destRect);
}
