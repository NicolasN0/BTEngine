#pragma once
#include "TextComponent.h"
#include "Singleton.h"


namespace dae
{

	class HighscoreManager final : public Singleton<HighscoreManager>
	{
	public:
		//Getter
		std::vector<int> GetHighscores(int number);
		const std::vector<TextComponent*>& GetTextComponents() const;

		//Setter
		void SetHighscores(const std::vector<int>& highscores);
		void SetTextComponents(const std::vector<TextComponent*>& textComponents);
		void SetHighscoreComp(const std::vector<TextComponent*>& comps);

		//Public
		void UpdateHighScore();
		void AddHighscore(int highscore);
	private:
		friend class Singleton<HighscoreManager>;
		HighscoreManager() = default;
		std::vector<int> m_Highscores;
		std::vector<TextComponent*> m_pTextComponents;
		std::vector<TextComponent*> m_pHiSoreComps;
	};
}

