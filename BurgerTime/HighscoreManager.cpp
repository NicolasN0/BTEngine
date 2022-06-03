#include "HighscoreManager.h"
#include <algorithm>

void dae::HighscoreManager::AddHighscore(int highscore)
{
	m_Highscores.push_back(highscore);
	//std::sort(m_Highscores.begin(), m_Highscores.end());
}

std::vector<int> dae::HighscoreManager::GetHighscores(int number)
{
	std::sort(m_Highscores.begin(), m_Highscores.end(), std::greater<>());
	std::vector<int> top;
	size_t size = m_Highscores.size();;
	for(size_t i{} ; i < number && i < size;i++)
	{
		top.push_back(m_Highscores.at(i));
	}

	return top;
}

void dae::HighscoreManager::SetHighscores(const std::vector<int>& highscores)
{
	m_Highscores = highscores;
	std::sort(m_Highscores.begin(), m_Highscores.end(),std::greater<>());
}

void dae::HighscoreManager::SetTextComponents(std::vector<TextComponent*>& textComponents)
{
	m_TextComponents = textComponents;
}

std::vector<dae::TextComponent*>& dae::HighscoreManager::GetTextComponents()
{
	return m_TextComponents;
}
