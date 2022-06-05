#include "HighscoreManager.h"
#include <algorithm>
#include <document.h>
#include <filereadstream.h>
#include <filewritestream.h>
#include <writer.h>

void dae::HighscoreManager::AddHighscore(int highscore)
{
	m_Highscores.push_back(highscore);
	//std::sort(m_Highscores.begin(), m_Highscores.end());

	//Read
	using rapidjson::Document;
	FILE* file = nullptr;
	const std::wstring& filename{ L"../Data/Highscores.json" };
	_wfopen_s(&file, filename.c_str(), L"r");
	if (!file)
	{
		return;
	}
	fseek(file, 0, SEEK_END);
	size_t size = static_cast<size_t>(ftell(file));

	fseek(file, 0, SEEK_SET);

	char* buffer = new char[size];

	rapidjson::FileReadStream stream(file, buffer, sizeof(buffer));

	Document doc;
	doc.ParseStream(stream);
	delete[] buffer;
	fclose(file);

	rapidjson::Value& highscores = doc["highscores"];


	//Change
	Document::AllocatorType& allocator = doc.GetAllocator();
	highscores.PushBack(highscore, allocator);
	//Write
	FILE* fp = nullptr;
	fopen_s(&fp, "../Data/Highscores.json", "w"); // non-Windows use "w"

	char writeBuffer[65536];
	rapidjson::FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));

	rapidjson::Writer<rapidjson::FileWriteStream> writer(os);
	doc.Accept(writer);

	fclose(fp);
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

void dae::HighscoreManager::SetTextComponents(const std::vector<TextComponent*>& textComponents)
{
	m_pTextComponents = textComponents;
}

void dae::HighscoreManager::SetHighscoreComp(const std::vector<TextComponent*>& comps)
{
	m_pHiSoreComps = comps;
}

void dae::HighscoreManager::UpdateHighScore()
{
	for(auto o : m_pHiSoreComps)
	{
		
		o->SetText(std::to_string(GetHighscores(1).at(0)));
	}
}

//void dae::HighscoreManager::WriteHighscores()
//{
//
//}

std::vector<dae::TextComponent*>& dae::HighscoreManager::GetTextComponents()
{
	return m_pTextComponents;
}
