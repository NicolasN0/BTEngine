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
		void SetTextComponents(std::vector<TextComponent*>& textComponents);
		void SetHighscoreComp(std::vector<TextComponent*> comps);
		void UpdateHighScore();
		//void WriteHighscores();
		std::vector<TextComponent*>& GetTextComponents();
	private:
		friend class Singleton<HighscoreManager>;
		HighscoreManager() = default;
		std::vector<int> m_Highscores;
		std::vector<TextComponent*> m_TextComponents;
		std::vector<TextComponent*> m_HiSoreComps;
	};
}

