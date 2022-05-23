#pragma once
#include "MonoBehaviour.h"
#include <SDL.h>
#include <memory>
namespace dae
{
	class Font;
	class Texture2D;
	class TextComponent : public MonoBehaviour
	{
	public:
		TextComponent(const std::string& filename,int size,SDL_Color color = { 255,255,255 });
		void Initialize();
		void Update(float dt) override;
		void FixedUpdate(float ) override {};
		void Render() const;

		void SetText(const std::string& text);
		//void SetPosition(float x, float y);
	private:
		bool m_NeedsUpdate{};
		std::string m_Text;
		std::shared_ptr<Font> m_Font;
		std::shared_ptr<Texture2D> m_TextTexture;
		float m_Counter{};
		SDL_Color m_Color;
	};

}

