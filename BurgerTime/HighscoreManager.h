#pragma once
#include "GameObject.h"
#include "Singleton.h"
#include "TextComponent.h"

namespace dae
{
	
	class HighscoreManager final : public Singleton<HighscoreManager>
	{
	public:
		void AddHighscore(int highscore);
		std::vector<int> GetHighscores(int number);
		void SetHighscores(const std::vector<int>& highscores);
		void SetTextComponents(const std::vector<TextComponent*>& textComponents);
		void SetHighscoreComp(const std::vector<TextComponent*>& comps);
		void UpdateHighScore();
		//void WriteHighscores();
		std::vector<TextComponent*>& GetTextComponents();
	private:
		friend class Singleton<HighscoreManager>;
		HighscoreManager() = default;
		std::vector<int> m_Highscores;
		std::vector<TextComponent*> m_pTextComponents;
		std::vector<TextComponent*> m_pHiSoreComps;
	};
}

