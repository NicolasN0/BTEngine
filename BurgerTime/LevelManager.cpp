#include "LevelManager.h"

#include <iostream>
#include "document.h"
#include "filereadstream.h"
#include "rapidjson.h"

#include "Commands.h"
#include "Scene.h"
#include "ContainerComponent.h"
#include "HighscoreManager.h"
#include "IngredientPartComponent.h"
#include "InputManager.h"
#include "TextureComponent.h"

dae::LevelManager::LevelManager(Scene* const scene,const std::vector<GameObject*>& players,const std::vector<GameObject*>& enemeyPlayers,const std::vector<GameObject*>& lvlBackground,const std::wstring& levelFile)
: m_Level{ 1 }
, m_pScene{ scene }
, m_LevelMade{}
, m_pPlayers(players)
, m_pLevelObjects()
, m_pEnemyPlayers(enemeyPlayers)
, m_pLvlBackground(lvlBackground)
, m_LadderSize(9, 40, 1)
, m_PlatformSize(95, 10, 1)
, m_ContainerSize(65, 70, 1)
, m_MaxEnemies{ 1,7,9 }
, m_CurrentEnemies()
, m_EnemyPosLevel1()
, m_EnemyPosLevel2()
, m_EnemyPosLevel3()
,m_SpawnTimer()
,m_SpawnMax(6)
,m_SpawnCount(1)


{
	ReadInLevel(levelFile);
	const rapidjson::Value& spawnpoints1 = m_Doc["level1"]["enemySpawn"];
	const rapidjson::Value& spawnpoints2 = m_Doc["level2"]["enemySpawn"];
	const rapidjson::Value& spawnpoints3 = m_Doc["level3"]["enemySpawn"];
	for (rapidjson::Value::ConstValueIterator it = spawnpoints1.Begin(); it != spawnpoints1.End(); it++)
	{
		const rapidjson::Value& spawnpoint = *it;
		m_EnemyPosLevel1.push_back(glm::vec3(spawnpoint["x"].GetFloat(), spawnpoint["y"].GetFloat(), 1));

	}
	for (rapidjson::Value::ConstValueIterator it = spawnpoints2.Begin(); it != spawnpoints2.End(); it++)
	{
		const rapidjson::Value& spawnpoint = *it;
		m_EnemyPosLevel2.push_back(glm::vec3(spawnpoint["x"].GetFloat(), spawnpoint["y"].GetFloat(), 1));

	}
	for (rapidjson::Value::ConstValueIterator it = spawnpoints3.Begin(); it != spawnpoints3.End(); it++)
	{
		const rapidjson::Value& spawnpoint = *it;
		m_EnemyPosLevel3.push_back(glm::vec3(spawnpoint["x"].GetFloat(), spawnpoint["y"].GetFloat(), 1));

	}
	
	
}
void dae::LevelManager::Update(float dt)
{
	if(m_LevelMade == true)
	{
		CheckLevelCompleted();
	} else
	{
		ClearLevel();
		MakeLevel(m_Level);
	}

	m_SpawnTimer += dt;
	if(m_SpawnTimer > m_SpawnMax)
	{
		m_CurrentEnemies = static_cast<int>(m_pScene->GetObjectsInWorldWithTag("Enemy").size());
		switch(m_Level)
		{
		case 1:
			if(m_CurrentEnemies < m_MaxEnemies.at(m_Level-1))
			{
				int randIndex = rand() % m_EnemyPosLevel1.size();
				
				if (m_SpawnCount % m_MaxEnemies.at(m_Level - 1) == 0)
				{

					MakeEnemey(m_EnemyPosLevel1.at(randIndex), EEnemyType::Egg);
				}
				else if (m_SpawnCount % (m_MaxEnemies.at(m_Level - 1) - 1) == 0)
				{
					MakeEnemey(m_EnemyPosLevel1.at(randIndex), EEnemyType::Pickle);

				}
				else
				{
					MakeEnemey(m_EnemyPosLevel1.at(randIndex), EEnemyType::Hotdog);
				}
				m_CurrentEnemies = static_cast<int>(m_pScene->GetObjectsInWorldWithTag("Enemy").size());
				m_SpawnCount++;
				std::cout << m_CurrentEnemies;
				m_SpawnTimer = 0;
			}
			break;

		case 2:
			if (m_CurrentEnemies < m_MaxEnemies.at(m_Level-1))
			{
				int randIndex = rand() % m_EnemyPosLevel2.size();
				std::cout << randIndex;
				if (m_CurrentEnemies == m_MaxEnemies.at(m_Level - 1) - 1)
				{

					MakeEnemey(m_EnemyPosLevel2.at(randIndex), EEnemyType::Egg);
				}
				else if (m_CurrentEnemies == m_MaxEnemies.at(m_Level - 1) - 2)
				{
					MakeEnemey(m_EnemyPosLevel2.at(randIndex), EEnemyType::Pickle);

				}
				else
				{
					MakeEnemey(m_EnemyPosLevel2.at(randIndex), EEnemyType::Hotdog);
				}
				m_CurrentEnemies = static_cast<int>(m_pScene->GetObjectsInWorldWithTag("Enemy").size());
				m_SpawnTimer = 0;
			}
			break;

		case 3:
			if (m_CurrentEnemies < m_MaxEnemies.at(m_Level-1))
			{
				int randIndex = rand() % m_EnemyPosLevel3.size();
				std::cout << randIndex;
				if (m_CurrentEnemies == m_MaxEnemies.at(m_Level - 1) - 1)
				{

					MakeEnemey(m_EnemyPosLevel3.at(randIndex), EEnemyType::Egg);
				}
				else if (m_CurrentEnemies == m_MaxEnemies.at(m_Level - 1) - 2)
				{
					MakeEnemey(m_EnemyPosLevel3.at(randIndex), EEnemyType::Pickle);

				}
				else
				{
					MakeEnemey(m_EnemyPosLevel3.at(randIndex), EEnemyType::Hotdog);
				}
				m_CurrentEnemies = static_cast<int>(m_pScene->GetObjectsInWorldWithTag("Enemy").size());
				m_SpawnTimer = 0;
			}
			break;
		}
		
	}


	
}

void dae::LevelManager::FixedUpdate(float )
{
}



void dae::LevelManager::MakeLevel(int levelCount)
{
	switch(levelCount)
	{
	case 1:
#pragma region level1
		{
	
		
		for(size_t i = 0 ; i< m_pLvlBackground.size();i++)
		{
			if(i == levelCount-1)
			{
				m_pLvlBackground.at(i)->SetVisibility(true);
			} else
			{
				m_pLvlBackground.at(i)->SetVisibility(false);
			}
		}
			//Player start pos

			assert(m_Doc.HasMember("level1"));
			const rapidjson::Value& level = m_Doc["level1"];
			for(auto o : m_pPlayers)
			{
				o->SetPosition(level["playerStart"]["x"].GetFloat(), level["playerStart"]["y"].GetFloat()) ;
				
			}

			for (auto o : m_pEnemyPlayers)
			{
				o->SetPosition(m_EnemyPosLevel1.at(0));

			}
			const rapidjson::Value& ladders = level["ladders"];
			for (rapidjson::Value::ConstValueIterator it = ladders.Begin(); it != ladders.End(); it++)
			{
				const rapidjson::Value& ladder = *it;


				auto go = new GameObject;
				go->SetSize(glm::vec3(m_LadderSize.x, ladder["size"].GetFloat(), m_LadderSize.z));
				go->SetPosition(ladder["x"].GetFloat(), ladder["y"].GetFloat());
				go->SetDebugDraw(false);
				go->SetTag("Ladder");
				m_pLevelObjects.push_back(go);
				m_pScene->Add(go);

			}

		

			const rapidjson::Value& platforms = level["platforms"];
			for(rapidjson::Value::ConstValueIterator it = platforms.Begin();it != platforms.End();it++)
			{
				const rapidjson::Value& platform = *it;
				

				auto go = new GameObject;
				go->SetSize(glm::vec3(platform["size"].GetFloat(), m_PlatformSize.y, m_PlatformSize.z));
				go->SetPosition(platform["x"].GetFloat(), platform["y"].GetFloat());
				go->SetDebugDraw(false);
				go->SetTag("Platform");
				m_pLevelObjects.push_back(go);
				m_pScene->Add(go);

			}


			const rapidjson::Value& containers = level["container"];
			for (rapidjson::Value::ConstValueIterator it = containers.Begin(); it != containers.End(); it++)
			{
				const rapidjson::Value& container = *it;


				auto go = new GameObject;
				go->SetSize(glm::vec3(m_ContainerSize.x, m_ContainerSize.y, m_PlatformSize.z));
				go->SetPosition(container["x"].GetFloat(), container["y"].GetFloat());
				go->SetDebugDraw(false);
				go->SetTag("Container");
				m_pLevelObjects.push_back(go);
				go->AddComponent<ContainerComponent>(new ContainerComponent(container["amount"].GetInt()));
				m_pScene->Add(go);

			}

			const rapidjson::Value& containersPlatforms = level["containerPlatform"];
			for (rapidjson::Value::ConstValueIterator it = containersPlatforms.Begin(); it != containersPlatforms.End(); it++)
			{
				const rapidjson::Value& containerPlatform = *it;


				auto go = new GameObject;
				go->SetSize(glm::vec3(m_ContainerSize.x, m_PlatformSize.y, m_PlatformSize.z));
				go->SetPosition(containerPlatform["x"].GetFloat(), containerPlatform["y"].GetFloat());
				go->SetDebugDraw(false);
				go->SetTag("Platform");
				m_pLevelObjects.push_back(go);
				m_pScene->Add(go);

			}



		const rapidjson::Value& ingredients = level["ingredients"];
		for (rapidjson::Value::ConstValueIterator it = ingredients.Begin(); it != ingredients.End(); it++)
		{
			const rapidjson::Value& ingredient = *it;

			MakeIngredient(glm::vec3(ingredient["x"].GetFloat(), ingredient["y"].GetFloat(), 0), static_cast<EIngredientType>(ingredient["type"].GetInt()), m_pScene, false, m_pPlayers);
			

		}

		}
#pragma endregion level1
		break;
	case 2:
#pragma region level2
		{
			ClearLevel();
		
			for (size_t i = 0; i < m_pLvlBackground.size(); i++)
			{
				if (i == levelCount -1)
				{
					m_pLvlBackground.at(i)->SetVisibility(true);
				}
				else
				{
					m_pLvlBackground.at(i)->SetVisibility(false);
				}
			}
			//Player Start Pos


			assert(m_Doc.HasMember("level2"));
			const rapidjson::Value& level = m_Doc["level2"];
			for (auto o : m_pPlayers)
			{
				o->SetPosition(level["playerStart"]["x"].GetFloat(), level["playerStart"]["y"].GetFloat());

			}


			for (auto o : m_pEnemyPlayers)
			{
				o->SetPosition(m_EnemyPosLevel2.at(0));

			}

#pragma region ladder
			const rapidjson::Value& ladders = level["ladders"];
			for (rapidjson::Value::ConstValueIterator it = ladders.Begin(); it != ladders.End(); it++)
			{
				const rapidjson::Value& ladder = *it;


				auto go = new GameObject;
				go->SetSize(glm::vec3(m_LadderSize.x, ladder["size"].GetFloat(), m_LadderSize.z));
				go->SetPosition(ladder["x"].GetFloat(), ladder["y"].GetFloat());
				go->SetDebugDraw(false);
				go->SetTag("Ladder");
				m_pLevelObjects.push_back(go);
				m_pScene->Add(go);

			}

			
			
#pragma endregion ladder

#pragma region platform

			const rapidjson::Value& platforms = level["platforms"];
			for (rapidjson::Value::ConstValueIterator it = platforms.Begin(); it != platforms.End(); it++)
			{
				const rapidjson::Value& platform = *it;


				auto go = new GameObject;
				go->SetSize(glm::vec3(platform["size"].GetFloat(), m_PlatformSize.y, m_PlatformSize.z));
				go->SetPosition(platform["x"].GetFloat(), platform["y"].GetFloat());
				go->SetDebugDraw(false);
				go->SetTag("Platform");
				m_pLevelObjects.push_back(go);
				m_pScene->Add(go);

			}

		

#pragma endregion platform

#pragma region container
			const rapidjson::Value& containers = level["container"];
			for (rapidjson::Value::ConstValueIterator it = containers.Begin(); it != containers.End(); it++)
			{
				const rapidjson::Value& container = *it;


				auto go = new GameObject;
				go->SetSize(glm::vec3(m_ContainerSize.x, m_ContainerSize.y, m_PlatformSize.z));
				go->SetPosition(container["x"].GetFloat(), container["y"].GetFloat());
				go->SetDebugDraw(false);
				go->SetTag("Container");
				m_pLevelObjects.push_back(go);
				go->AddComponent<ContainerComponent>(new ContainerComponent(container["amount"].GetInt()));
				m_pScene->Add(go);

			}

			const rapidjson::Value& containersPlatforms = level["containerPlatform"];
			for (rapidjson::Value::ConstValueIterator it = containersPlatforms.Begin(); it != containersPlatforms.End(); it++)
			{
				const rapidjson::Value& containerPlatform = *it;


				auto go = new GameObject;
				go->SetSize(glm::vec3(m_ContainerSize.x, m_PlatformSize.y, m_PlatformSize.z));
				go->SetPosition(containerPlatform["x"].GetFloat(), containerPlatform["y"].GetFloat());
				go->SetDebugDraw(false);
				go->SetTag("Platform");
				m_pLevelObjects.push_back(go);
				m_pScene->Add(go);

			}
		
#pragma endregion container

#pragma region ingredients
			
			

			const rapidjson::Value& ingredients = level["ingredients"];
			for (rapidjson::Value::ConstValueIterator it = ingredients.Begin(); it != ingredients.End(); it++)
			{
				const rapidjson::Value& ingredient = *it;

				MakeIngredient(glm::vec3(ingredient["x"].GetFloat(), ingredient["y"].GetFloat(), 0), static_cast<EIngredientType>(ingredient["type"].GetInt()), m_pScene, false, m_pPlayers);


			}
#pragma endregion ingredients
			
		}
#pragma endregion level2
		break;
	case 3:
#pragma region level3
		{
			ClearLevel();
			
			for (size_t i = 0; i < m_pLvlBackground.size(); i++)
			{
				if (i == levelCount - 1)
				{
					m_pLvlBackground.at(i)->SetVisibility(true);
				}
				else
				{
					m_pLvlBackground.at(i)->SetVisibility(false);
				}
			}
			//Player Start Pos

			assert(m_Doc.HasMember("level3"));
			const rapidjson::Value& level = m_Doc["level3"];
			for (auto o : m_pPlayers)
			{
				o->SetPosition(level["playerStart"]["x"].GetFloat(), level["playerStart"]["y"].GetFloat());

			}
		

			for (auto o : m_pEnemyPlayers)
			{
				o->SetPosition(m_EnemyPosLevel3.at(0));

			}

#pragma region ladder
			const rapidjson::Value& ladders = level["ladders"];
			for (rapidjson::Value::ConstValueIterator it = ladders.Begin(); it != ladders.End(); it++)
			{
				const rapidjson::Value& ladder = *it;


				auto go = new GameObject;
				go->SetSize(glm::vec3(m_LadderSize.x, ladder["size"].GetFloat(), m_LadderSize.z));
				go->SetPosition(ladder["x"].GetFloat(), ladder["y"].GetFloat());
				go->SetDebugDraw(false);
				go->SetTag("Ladder");
				m_pLevelObjects.push_back(go);
				m_pScene->Add(go);

			}
		

#pragma endregion ladder

#pragma region platform

			const rapidjson::Value& platforms = level["platforms"];
			for (rapidjson::Value::ConstValueIterator it = platforms.Begin(); it != platforms.End(); it++)
			{
				const rapidjson::Value& platform = *it;


				auto go = new GameObject;
				go->SetSize(glm::vec3(platform["size"].GetFloat(), m_PlatformSize.y, m_PlatformSize.z));
				go->SetPosition(platform["x"].GetFloat(), platform["y"].GetFloat());
				go->SetDebugDraw(false);
				go->SetTag("Platform");
				m_pLevelObjects.push_back(go);
				m_pScene->Add(go);

			}

			
#pragma endregion platform

#pragma region container

			const rapidjson::Value& containers = level["container"];
			for (rapidjson::Value::ConstValueIterator it = containers.Begin(); it != containers.End(); it++)
			{
				const rapidjson::Value& container = *it;


				auto go = new GameObject;
				go->SetSize(glm::vec3(m_ContainerSize.x, m_ContainerSize.y, m_PlatformSize.z));
				go->SetPosition(container["x"].GetFloat(), container["y"].GetFloat());
				go->SetDebugDraw(false);
				go->SetTag("Container");
				m_pLevelObjects.push_back(go);
				go->AddComponent<ContainerComponent>(new ContainerComponent(container["amount"].GetInt()));
				m_pScene->Add(go);

			}

			const rapidjson::Value& containersPlatforms = level["containerPlatform"];
			for (rapidjson::Value::ConstValueIterator it = containersPlatforms.Begin(); it != containersPlatforms.End(); it++)
			{
				const rapidjson::Value& containerPlatform = *it;


				auto go = new GameObject;
				go->SetSize(glm::vec3(m_ContainerSize.x, m_PlatformSize.y, m_PlatformSize.z));
				go->SetPosition(containerPlatform["x"].GetFloat(), containerPlatform["y"].GetFloat());
				go->SetDebugDraw(false);
				go->SetTag("Platform");
				m_pLevelObjects.push_back(go);
				m_pScene->Add(go);

			}
		
#pragma endregion container

#pragma region ingrediens
			const rapidjson::Value& ingredients = level["ingredients"];
			for (rapidjson::Value::ConstValueIterator it = ingredients.Begin(); it != ingredients.End(); it++)
			{
				const rapidjson::Value& ingredient = *it;

				MakeIngredient(glm::vec3(ingredient["x"].GetFloat(), ingredient["y"].GetFloat(), 0), static_cast<EIngredientType>(ingredient["type"].GetInt()), m_pScene, false, m_pPlayers);


			}

		

#pragma endregion ingrediens
			
		}
#pragma endregion level3

		break;
	case 4:
		HighscoreManager::GetInstance().AddHighscore(m_pPlayers.at(0)->GetComponent<ValuesComponent>()->GetScores());
		m_Level = 1;
		SceneChanger::GetInstance().SetCurrentScene("highscore");
		break;
	default:
		std::cout << "no levelcounter";
		break;
	}

	m_LevelMade = true;
	
}

void dae::LevelManager::ClearLevel()
{
	m_CurrentEnemies = 0;
	m_SpawnCount = 1;
	for(auto o: m_pLevelObjects)
	{
		o->Delete();
	}
	m_pLevelObjects.clear();
}

int dae::LevelManager::GetCurLevel() const
{
	return m_Level;
}

void dae::LevelManager::CheckLevelCompleted()
{
	int count{};
	std::vector<GameObject*> AllContainers;
	AllContainers = m_pScene->GetObjectsInWorldWithTag("Container");
	for(auto o : AllContainers)
	{
		if(o->GetComponent<ContainerComponent>()->GetIsFilled() == true)
		{
			count++;
		}
	}
	if(count == AllContainers.size())
	{
		m_Level++;
		m_LevelMade = false;
	}

	
	for(auto o:m_pPlayers)
	{
		if(o->GetComponent<PeterPepperComponent>()->GetNextLevel())
		{
			m_Level++;
			m_LevelMade = false;
			o->GetComponent<PeterPepperComponent>()->SetNextLevel(false);
		}
	}
}

void dae::LevelManager::MakeIngredient(const glm::vec3& pos, EIngredientType ingredientType, Scene* const, bool debugDraw, const std::vector<GameObject*>& players)
{
	auto totalIngredient = new GameObject;
	auto part1 = new GameObject;
	auto part2 = new GameObject;
	auto part3 = new GameObject;
	auto part4 = new GameObject;

	totalIngredient->AddChild(part1);
	totalIngredient->AddChild(part2);
	totalIngredient->AddChild(part3);
	totalIngredient->AddChild(part4);

	for (int i{}; i < totalIngredient->GetChildCount(); i++)
	{
		switch (ingredientType)
		{
		case EIngredientType::Bun:
			if (i == 0)
			{
				totalIngredient->GetChildAt(i)->AddComponent<dae::TextureComponent>(new dae::TextureComponent("Ingredients/BunL.png"));

			}
			else if (i == totalIngredient->GetChildCount() - 1)
			{
				totalIngredient->GetChildAt(i)->AddComponent<dae::TextureComponent>(new dae::TextureComponent("Ingredients/BunR.png"));
			}
			else
			{
				totalIngredient->GetChildAt(i)->AddComponent<dae::TextureComponent>(new dae::TextureComponent("Ingredients/Bun.png"));
			}
			break;
		case EIngredientType::Cheese:
			if (i == 0)
			{
				totalIngredient->GetChildAt(i)->AddComponent<dae::TextureComponent>(new dae::TextureComponent("Ingredients/CheeseL.png"));

			}
			else if (i == totalIngredient->GetChildCount() - 1)
			{
				totalIngredient->GetChildAt(i)->AddComponent<dae::TextureComponent>(new dae::TextureComponent("Ingredients/CheeseR.png"));
			}
			else
			{
				totalIngredient->GetChildAt(i)->AddComponent<dae::TextureComponent>(new dae::TextureComponent("Ingredients/Cheese.png"));
			}
			break;
		case EIngredientType::Lettuce:
			if (i == 0)
			{
				totalIngredient->GetChildAt(i)->AddComponent<dae::TextureComponent>(new dae::TextureComponent("Ingredients/LettuceL.png"));

			}
			else if (i == totalIngredient->GetChildCount() - 1)
			{
				totalIngredient->GetChildAt(i)->AddComponent<dae::TextureComponent>(new dae::TextureComponent("Ingredients/LettuceR.png"));
			}
			else
			{
				totalIngredient->GetChildAt(i)->AddComponent<dae::TextureComponent>(new dae::TextureComponent("Ingredients/Lettuce.png"));
			}
			break;
		case EIngredientType::Tomato:
			if (i == 0)
			{
				totalIngredient->GetChildAt(i)->AddComponent<dae::TextureComponent>(new dae::TextureComponent("Ingredients/TomatoL.png"));

			}
			else if (i == totalIngredient->GetChildCount() - 1)
			{
				totalIngredient->GetChildAt(i)->AddComponent<dae::TextureComponent>(new dae::TextureComponent("Ingredients/TomatoR.png"));
			}
			else
			{
				totalIngredient->GetChildAt(i)->AddComponent<dae::TextureComponent>(new dae::TextureComponent("Ingredients/Tomato.png"));
			}
			break;
		case EIngredientType::Patty:
			if (i == 0)
			{
				totalIngredient->GetChildAt(i)->AddComponent<dae::TextureComponent>(new dae::TextureComponent("Ingredients/PattyL.png"));

			}
			else if (i == totalIngredient->GetChildCount() - 1)
			{
				totalIngredient->GetChildAt(i)->AddComponent<dae::TextureComponent>(new dae::TextureComponent("Ingredients/PattyR.png"));
			}
			else
			{
				totalIngredient->GetChildAt(i)->AddComponent<dae::TextureComponent>(new dae::TextureComponent("Ingredients/Patty.png"));
			}
			break;
		case EIngredientType::BunBottom:
			if (i == 0)
			{
				totalIngredient->GetChildAt(i)->AddComponent<dae::TextureComponent>(new dae::TextureComponent("Ingredients/BunBotL.png"));

			}
			else if (i == totalIngredient->GetChildCount() - 1)
			{
				totalIngredient->GetChildAt(i)->AddComponent<dae::TextureComponent>(new dae::TextureComponent("Ingredients/BunBotR.png"));
			}
			else
			{
				totalIngredient->GetChildAt(i)->AddComponent<dae::TextureComponent>(new dae::TextureComponent("Ingredients/BunBot.png"));
			}
			break;
		default:
			std::cout << "noType";
			break;
		}

		totalIngredient->GetChildAt(i)->AddComponent<dae::IngredientPartComponent>(new dae::IngredientPartComponent());

	}


	float totalSize{};
	part1->SetPosition(0, 0);
	totalSize += part1->GetSize().x;
	part2->SetPosition(totalSize, 0);
	totalSize += part2->GetSize().x;
	part3->SetPosition(totalSize, 0);
	totalSize += part3->GetSize().x;
	part4->SetPosition(totalSize, 0);
	totalSize += part4->GetSize().x;


	totalIngredient->SetDebugDraw(debugDraw);
	part1->SetDebugDraw(debugDraw);
	part2->SetDebugDraw(debugDraw);
	part3->SetDebugDraw(debugDraw);
	part4->SetDebugDraw(debugDraw);


	totalIngredient->SetSize(glm::vec3(totalSize, part1->GetSize().y, 0));
	totalIngredient->SetScale(1.8f, 1.8f);
	totalIngredient->SetTag("Ingredient");

	totalIngredient->SetPosition(pos.x, pos.y);
	totalIngredient->AddComponent<IngredientComponent>(new IngredientComponent);
	totalIngredient->GetComponent<IngredientComponent>()->SetPlayers(players);
	m_pLevelObjects.push_back(part1);
	m_pLevelObjects.push_back(part2);
	m_pLevelObjects.push_back(part3);
	m_pLevelObjects.push_back(part4);
	m_pLevelObjects.push_back(totalIngredient);
	m_pScene->Add(totalIngredient);
}

void dae::LevelManager::MakeEnemey(const glm::vec3& pos, EEnemyType type)
{
	auto HotDog = new GameObject;
	SpriteComponent* enemySprite = new SpriteComponent("PeterPepperSpriteTrans.png", 15, 11);
	HotDog->AddComponent(enemySprite);
	HotDog->AddComponent<BasicEnemyComponent>(new BasicEnemyComponent(type, enemySprite));

	HotDog->SetDebugDraw(false);
	HotDog->SetPosition(pos);
	HotDog->SetScale(1.5f, 1.5f);
	HotDog->GetComponent<BasicEnemyComponent>()->SetTarget(m_pPlayers.at(0));
	HotDog->SetTag("Enemy");
	m_pLevelObjects.push_back(HotDog);
	m_pScene->Add(HotDog);

}

void dae::LevelManager::ReadInLevel(const std::wstring& filename)
{
	using rapidjson::Document;
	FILE* file = nullptr;
	_wfopen_s(&file, filename.c_str(), L"r");
	if(!file)
	{
		return;
	}
	fseek(file, 0, SEEK_END);
	size_t size = static_cast<size_t>(ftell(file));

	fseek(file, 0, SEEK_SET);

	char* buffer = new char[size];

	rapidjson::FileReadStream stream (file, buffer, sizeof(buffer));

	m_Doc.ParseStream(stream);
	delete[] buffer;
	fclose(file);


}
