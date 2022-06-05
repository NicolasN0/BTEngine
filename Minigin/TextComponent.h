#pragma once
#include "MonoBehaviour.h"
#include <SDL.h>
#include <memory>
namespace dae
{
	class Font;
	class Texture2D;
	class TextComponent final : public MonoBehaviour
	{
	public:
		TextComponent(const std::string& filename,int size,SDL_Color color = { 255,255,255 });
		void Initialize();
		void Update(float dt) override;
		void FixedUpdate(float ) override {};
		void Render() const override;

		void SetText(const std::string& text);
		
	private:
		bool m_NeedsUpdate;
		float m_Counter;
		SDL_Color m_Color;
		std::string m_Text;
		std::shared_ptr<Font> m_spFont;
		std::shared_ptr<Texture2D> m_spTextTexture;
	};

}

