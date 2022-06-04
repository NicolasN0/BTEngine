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

dae::LevelManager::LevelManager(Scene* scene, std::vector<GameObject*> players, std::vector<GameObject*> enemeyPlayers, std::vector<GameObject*>& lvlBackground,const std::wstring& levelFile) : m_Level{ 1 }, m_Scene{ scene }, m_LevelMade{}, m_Players(players)
, m_EnemyPlayers(enemeyPlayers)
, m_LvlBackground(lvlBackground)
, m_LadderSize(9, 40, 1)
, m_PlatformSize(95, 10, 1)
, m_ContainerSize(65, 70, 1)
, m_MaxEnemies{ 5,7,9 }
, m_CurrentEnemies()
//, m_EnemyPosLevel1({ glm::vec3(250, 100,1),glm::vec3(447, 160,1),glm::vec3(362, 244,1),glm::vec3(280, 362,1) })
, m_EnemyPosLevel1()
//, m_EnemyPosLevel2({ glm::vec3(450, 213,1),glm::vec3(279, 369,1),glm::vec3(365, 245,1),glm::vec3(206, 276,1),glm::vec3(107, 213,1) })
, m_EnemyPosLevel2()
//, m_EnemyPosLevel3({ glm::vec3(279, 391,1),glm::vec3(278, 246,1),glm::vec3(365, 250,1),glm::vec3(449, 104,1),glm::vec3(109, 188,1) })
, m_EnemyPosLevel3()
,m_SpawnTimer()
,m_SpawnMax(6)

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
		switch(m_Level)
		{
		case 1:
			if(m_CurrentEnemies < m_MaxEnemies.at(m_Level-1))
			{
				//std::cout << "spawns";
				int randIndex = rand() % m_EnemyPosLevel1.size();
				std::cout << randIndex;
				MakeEnemey(m_EnemyPosLevel1.at(randIndex), EEnemyType::Hotdog);
				m_CurrentEnemies = m_Scene->GetObjectsInWorldWithTag("Enemy").size();
				m_SpawnTimer = 0;
			}
			break;

		case 2:
			if (m_CurrentEnemies < m_MaxEnemies.at(m_Level-1))
			{
				//std::cout << "spawns";
				int randIndex = rand() % m_EnemyPosLevel2.size();
				std::cout << randIndex;
				MakeEnemey(m_EnemyPosLevel2.at(randIndex), EEnemyType::Hotdog);
				m_CurrentEnemies = m_Scene->GetObjectsInWorldWithTag("Enemy").size();
				m_SpawnTimer = 0;
			}
			break;

		case 3:
			if (m_CurrentEnemies < m_MaxEnemies.at(m_Level-1))
			{
				//std::cout << "spawns";
				int randIndex = rand() % m_EnemyPosLevel3.size();
				std::cout << randIndex;
				MakeEnemey(m_EnemyPosLevel3.at(randIndex), EEnemyType::Hotdog);
				m_CurrentEnemies = m_Scene->GetObjectsInWorldWithTag("Enemy").size();
				m_SpawnTimer = 0;
			}
			break;
		}
		
	}


	
}

void dae::LevelManager::FixedUpdate(float timestep)
{
}



void dae::LevelManager::MakeLevel(int levelCount)
{
	switch(levelCount)
	{
	case 1:
#pragma region level1
		{
	
		
		for(size_t i = 0 ; i< m_LvlBackground.size();i++)
		{
			if(i == levelCount-1)
			{
				m_LvlBackground.at(i)->SetVisibility(true);
			} else
			{
				m_LvlBackground.at(i)->SetVisibility(false);
			}
		}
			//Player start pos

			assert(m_Doc.HasMember("level1"));
			const rapidjson::Value& level = m_Doc["level1"];
			for(auto o : m_Players)
			{
				//o->SetPosition(glm::vec3(110, 100,1));
				o->SetPosition(level["playerStart"]["x"].GetFloat(), level["playerStart"]["y"].GetFloat()) ;
				
			}

			for (auto o : m_EnemyPlayers)
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
				go->SetDebugDraw(true);
				go->SetTag("Ladder");
				m_LevelObjects.push_back(go);
				m_Scene->Add(go);

			}


		//const rapidjson::Value& platforms = level["platforms"];
		

		/*for (auto& v : platforms.GetArray())
		{
			go = new GameObject;
			go->SetSize(glm::vec3(v["size"].GetFloat(), m_PlatformSize.y, m_PlatformSize.z));
			go->SetPosition(v["x"].GetFloat(), v["y"].GetFloat());
			go->SetDebugDraw(true);
			go->SetTag("Platform");
			m_LevelObjects.push_back(go);
			m_Scene->Add(go);
		}*/
		

			const rapidjson::Value& platforms = level["platforms"];
			for(rapidjson::Value::ConstValueIterator it = platforms.Begin();it != platforms.End();it++)
			{
				const rapidjson::Value& platform = *it;
				

				auto go = new GameObject;
				go->SetSize(glm::vec3(platform["size"].GetFloat(), m_PlatformSize.y, m_PlatformSize.z));
				go->SetPosition(platform["x"].GetFloat(), platform["y"].GetFloat());
				go->SetDebugDraw(true);
				go->SetTag("Platform");
				m_LevelObjects.push_back(go);
				m_Scene->Add(go);

			}


			const rapidjson::Value& containers = level["container"];
			for (rapidjson::Value::ConstValueIterator it = containers.Begin(); it != containers.End(); it++)
			{
				const rapidjson::Value& container = *it;


				auto go = new GameObject;
				go->SetSize(glm::vec3(m_ContainerSize.x, m_ContainerSize.y, m_PlatformSize.z));
				go->SetPosition(container["x"].GetFloat(), container["y"].GetFloat());
				go->SetDebugDraw(true);
				go->SetTag("Container");
				m_LevelObjects.push_back(go);
				go->AddComponent<ContainerComponent>(new ContainerComponent(container["amount"].GetInt()));
				m_Scene->Add(go);

			}

			const rapidjson::Value& containersPlatforms = level["containerPlatform"];
			for (rapidjson::Value::ConstValueIterator it = containersPlatforms.Begin(); it != containersPlatforms.End(); it++)
			{
				const rapidjson::Value& containerPlatform = *it;


				auto go = new GameObject;
				go->SetSize(glm::vec3(m_ContainerSize.x, m_PlatformSize.y, m_PlatformSize.z));
				go->SetPosition(containerPlatform["x"].GetFloat(), containerPlatform["y"].GetFloat());
				go->SetDebugDraw(true);
				go->SetTag("Platform");
				m_LevelObjects.push_back(go);
				m_Scene->Add(go);

			}



		const rapidjson::Value& ingredients = level["ingredients"];
		for (rapidjson::Value::ConstValueIterator it = ingredients.Begin(); it != ingredients.End(); it++)
		{
			const rapidjson::Value& ingredient = *it;

			MakeIngredient(glm::vec3(ingredient["x"].GetFloat(), ingredient["y"].GetFloat(), 0), static_cast<EIngredientType>(ingredient["type"].GetInt()), m_Scene, true, m_Players);
			

		}

		}
#pragma endregion level1
		break;
	case 2:
#pragma region level2
		{
			ClearLevel();
		
			for (size_t i = 0; i < m_LvlBackground.size(); i++)
			{
				if (i == levelCount -1)
				{
					m_LvlBackground.at(i)->SetVisibility(true);
				}
				else
				{
					m_LvlBackground.at(i)->SetVisibility(false);
				}
			}
			//Player Start Pos


			assert(m_Doc.HasMember("level2"));
			const rapidjson::Value& level = m_Doc["level2"];
			for (auto o : m_Players)
			{
				//o->SetPosition(glm::vec3(110, 100,1));
				o->SetPosition(level["playerStart"]["x"].GetFloat(), level["playerStart"]["y"].GetFloat());

			}

			/*for (auto o : m_Players)
			{
				o->SetPosition(glm::vec3(103, 100, 2));

			}*/

			for (auto o : m_EnemyPlayers)
			{
				o->SetPosition(m_EnemyPosLevel2.at(0));

			}

			const rapidjson::Value& ladders = level["ladders"];
			for (rapidjson::Value::ConstValueIterator it = ladders.Begin(); it != ladders.End(); it++)
			{
				const rapidjson::Value& ladder = *it;


				auto go = new GameObject;
				go->SetSize(glm::vec3(m_LadderSize.x, ladder["size"].GetFloat(), m_LadderSize.z));
				go->SetPosition(ladder["x"].GetFloat(), ladder["y"].GetFloat());
				go->SetDebugDraw(true);
				go->SetTag("Ladder");
				m_LevelObjects.push_back(go);
				m_Scene->Add(go);

			}

#pragma region ladder
			/*auto go = new GameObject;
			go->SetSize(glm::vec3(m_LadderSize.x, 125, m_LadderSize.z));
			go->SetPosition(110, 105);
			go->SetDebugDraw(true);
			go->SetTag("Ladder");
			m_LevelObjects.push_back(go);
			m_Scene->Add(go);

			go = new GameObject;
			go->SetSize(glm::vec3(m_LadderSize.x, 125, m_LadderSize.z));
			go->SetPosition(153, 105);
			go->SetDebugDraw(true);
			go->SetTag("Ladder");
			m_LevelObjects.push_back(go);
			m_Scene->Add(go);

			go = new GameObject;
			go->SetSize(glm::vec3(m_LadderSize.x, 125, m_LadderSize.z));
			go->SetPosition(196, 105);
			go->SetDebugDraw(true);
			go->SetTag("Ladder");
			m_LevelObjects.push_back(go);
			m_Scene->Add(go);*/

		/*	go = new GameObject;
			go->SetSize(glm::vec3(m_LadderSize.x, 240, m_LadderSize.z));
			go->SetPosition(241, 105);
			go->SetDebugDraw(true);
			go->SetTag("Ladder");
			m_LevelObjects.push_back(go);
			m_Scene->Add(go);*/

		/*	go = new GameObject;
			go->SetSize(glm::vec3(m_LadderSize.x, 290, m_LadderSize.z));
			go->SetPosition(283, 105);
			go->SetDebugDraw(true);
			go->SetTag("Ladder");
			m_LevelObjects.push_back(go);
			m_Scene->Add(go);*/

			/*go = new GameObject;
			go->SetSize(glm::vec3(m_LadderSize.x, 240, m_LadderSize.z));
			go->SetPosition(326, 105);
			go->SetDebugDraw(true);
			go->SetTag("Ladder");
			m_LevelObjects.push_back(go);
			m_Scene->Add(go);*/

		/*	go = new GameObject;
			go->SetSize(glm::vec3(m_LadderSize.x, 125, m_LadderSize.z));
			go->SetPosition(369, 105);
			go->SetDebugDraw(true);
			go->SetTag("Ladder");
			m_LevelObjects.push_back(go);
			m_Scene->Add(go);*/

		/*	go = new GameObject;
			go->SetSize(glm::vec3(m_LadderSize.x, 125, m_LadderSize.z));
			go->SetPosition(412, 105);
			go->SetDebugDraw(true);
			go->SetTag("Ladder");
			m_LevelObjects.push_back(go);
			m_Scene->Add(go);*/

			/*go = new GameObject;
			go->SetSize(glm::vec3(m_LadderSize.x, 125, m_LadderSize.z));
			go->SetPosition(456, 105);
			go->SetDebugDraw(true);
			go->SetTag("Ladder");
			m_LevelObjects.push_back(go);
			m_Scene->Add(go);*/

			
#pragma endregion ladder

#pragma region platform

			const rapidjson::Value& platforms = level["platforms"];
			for (rapidjson::Value::ConstValueIterator it = platforms.Begin(); it != platforms.End(); it++)
			{
				const rapidjson::Value& platform = *it;


				auto go = new GameObject;
				go->SetSize(glm::vec3(platform["size"].GetFloat(), m_PlatformSize.y, m_PlatformSize.z));
				go->SetPosition(platform["x"].GetFloat(), platform["y"].GetFloat());
				go->SetDebugDraw(true);
				go->SetTag("Platform");
				m_LevelObjects.push_back(go);
				m_Scene->Add(go);

			}

			/*auto go = new GameObject;
			go->SetSize(glm::vec3(355, m_PlatformSize.y, m_PlatformSize.z));
			go->SetPosition(110, 105);
			go->SetDebugDraw(true);
			go->SetTag("Platform");
			m_LevelObjects.push_back(go);
			m_Scene->Add(go);*/

			/*go = new GameObject;
			go->SetSize(glm::vec3(182, m_PlatformSize.y, m_PlatformSize.z));
			go->SetPosition(110, 135);
			go->SetDebugDraw(true);
			go->SetTag("Platform");
			m_LevelObjects.push_back(go);
			m_Scene->Add(go);*/


			//go = new GameObject;
			//go->SetSize(glm::vec3(95, m_PlatformSize.y, m_PlatformSize.z));
			//go->SetPosition(110, 165);
			//go->SetDebugDraw(true);
			//go->SetTag("Platform");
			//m_LevelObjects.push_back(go);
			//m_Scene->Add(go);

		/*	go = new GameObject;
			go->SetSize(glm::vec3(355, m_PlatformSize.y, m_PlatformSize.z));
			go->SetPosition(110, 220);
			go->SetDebugDraw(true);
			go->SetTag("Platform");
			m_LevelObjects.push_back(go);
			m_Scene->Add(go);*/


		/*	go = new GameObject;
			go->SetSize(glm::vec3(96, m_PlatformSize.y, m_PlatformSize.z));
			go->SetPosition(196, 195);
			go->SetDebugDraw(true);
			go->SetTag("Platform");
			m_LevelObjects.push_back(go);
			m_Scene->Add(go);*/

			/*go = new GameObject;
			go->SetSize(glm::vec3(96, m_PlatformSize.y, m_PlatformSize.z));
			go->SetPosition(196, 280);
			go->SetDebugDraw(true);
			go->SetTag("Platform");
			m_LevelObjects.push_back(go);
			m_Scene->Add(go);*/

			//go = new GameObject;
			//go->SetSize(glm::vec3(182, m_PlatformSize.y, m_PlatformSize.z));
			//go->SetPosition(196, 335);
			//go->SetDebugDraw(true);
			//go->SetTag("Platform");
			//m_LevelObjects.push_back(go);
			//m_Scene->Add(go);


		/*	go = new GameObject;
			go->SetSize(glm::vec3(182, m_PlatformSize.y, m_PlatformSize.z));
			go->SetPosition(283, 165);
			go->SetDebugDraw(true);
			go->SetTag("Platform");
			m_LevelObjects.push_back(go);
			m_Scene->Add(go);*/

			/*go = new GameObject;
			go->SetSize(glm::vec3(95, m_PlatformSize.y, m_PlatformSize.z));
			go->SetPosition(283, 250);
			go->SetDebugDraw(true);
			go->SetTag("Platform");
			m_LevelObjects.push_back(go);
			m_Scene->Add(go);*/

			//go = new GameObject;
			//go->SetSize(glm::vec3(95, m_PlatformSize.y, m_PlatformSize.z));
			//go->SetPosition(283, 310);
			//go->SetDebugDraw(true);
			//go->SetTag("Platform");
			//m_LevelObjects.push_back(go);
			//m_Scene->Add(go);

			/*go = new GameObject;
			go->SetSize(glm::vec3(96, m_PlatformSize.y, m_PlatformSize.z));
			go->SetPosition(369, 195);
			go->SetDebugDraw(true);
			go->SetTag("Platform");
			m_LevelObjects.push_back(go);
			m_Scene->Add(go);*/

#pragma endregion platform

#pragma region container
			const rapidjson::Value& containers = level["container"];
			for (rapidjson::Value::ConstValueIterator it = containers.Begin(); it != containers.End(); it++)
			{
				const rapidjson::Value& container = *it;


				auto go = new GameObject;
				go->SetSize(glm::vec3(m_ContainerSize.x, m_ContainerSize.y, m_PlatformSize.z));
				go->SetPosition(container["x"].GetFloat(), container["y"].GetFloat());
				go->SetDebugDraw(true);
				go->SetTag("Container");
				m_LevelObjects.push_back(go);
				go->AddComponent<ContainerComponent>(new ContainerComponent(container["amount"].GetInt()));
				m_Scene->Add(go);

			}

			const rapidjson::Value& containersPlatforms = level["containerPlatform"];
			for (rapidjson::Value::ConstValueIterator it = containersPlatforms.Begin(); it != containersPlatforms.End(); it++)
			{
				const rapidjson::Value& containerPlatform = *it;


				auto go = new GameObject;
				go->SetSize(glm::vec3(m_ContainerSize.x, m_PlatformSize.y, m_PlatformSize.z));
				go->SetPosition(containerPlatform["x"].GetFloat(), containerPlatform["y"].GetFloat());
				go->SetDebugDraw(true);
				go->SetTag("Platform");
				m_LevelObjects.push_back(go);
				m_Scene->Add(go);

			}
		/*	auto go = new GameObject;
			go->SetSize(glm::vec3(m_ContainerSize.x, m_PlatformSize.y, m_PlatformSize.z));
			go->SetPosition(126, 370);
			go->SetDebugDraw(true);
			go->SetTag("Platform");
			m_LevelObjects.push_back(go);
			m_Scene->Add(go);*/

			/*go = new GameObject;
			go->SetSize(glm::vec3(m_ContainerSize.x, m_ContainerSize.y, m_PlatformSize.z));
			go->SetPosition(126, 310);
			go->SetDebugDraw(true);
			go->SetTag("Container");
			m_LevelObjects.push_back(go);
			go->AddComponent<ContainerComponent>(new ContainerComponent());
			m_Scene->Add(go);*/


			/*go = new GameObject;
			go->SetSize(glm::vec3(m_ContainerSize.x, m_PlatformSize.y, m_PlatformSize.z));
			go->SetPosition(212, 455);
			go->SetDebugDraw(true);
			go->SetTag("Platform");
			m_LevelObjects.push_back(go);
			m_Scene->Add(go);*/

		/*	go = new GameObject;
			go->SetSize(glm::vec3(m_ContainerSize.x, m_ContainerSize.y, m_PlatformSize.z));
			go->SetPosition(212, 395);
			go->SetDebugDraw(true);
			go->SetTag("Container");
			m_LevelObjects.push_back(go);
			go->AddComponent<ContainerComponent>(new ContainerComponent());
			m_Scene->Add(go);*/


		/*	go = new GameObject;
			go->SetSize(glm::vec3(m_ContainerSize.x, m_PlatformSize.y, m_PlatformSize.z));
			go->SetPosition(298, 455);
			go->SetDebugDraw(true);
			go->SetTag("Platform");
			m_LevelObjects.push_back(go);
			m_Scene->Add(go);*/

			/*go = new GameObject;
			go->SetSize(glm::vec3(m_ContainerSize.x, m_ContainerSize.y, m_PlatformSize.z));
			go->SetPosition(298, 395);
			go->SetDebugDraw(true);
			go->SetTag("Container");
			m_LevelObjects.push_back(go);
			go->AddComponent<ContainerComponent>(new ContainerComponent());
			m_Scene->Add(go);*/

			/*go = new GameObject;
			go->SetSize(glm::vec3(m_ContainerSize.x, m_PlatformSize.y, m_PlatformSize.z));
			go->SetPosition(384, 370);
			go->SetDebugDraw(true);
			go->SetTag("Platform");
			m_LevelObjects.push_back(go);
			m_Scene->Add(go);*/

		/*	go = new GameObject;
			go->SetSize(glm::vec3(m_ContainerSize.x, m_ContainerSize.y, m_PlatformSize.z));
			go->SetPosition(384, 310);
			go->SetDebugDraw(true);
			go->SetTag("Container");
			m_LevelObjects.push_back(go);
			go->AddComponent<ContainerComponent>(new ContainerComponent());
			m_Scene->Add(go);*/
#pragma endregion container

#pragma region ingredients
			
			/*MakeIngredient(glm::vec3(130, 102, 0), EIngredientType::Bun, m_Scene, false, m_Players);
			MakeIngredient(glm::vec3(130, 135, 0), EIngredientType::Lettuce, m_Scene, false, m_Players);
			MakeIngredient(glm::vec3(130, 165, 0), EIngredientType::Cheese, m_Scene, false, m_Players);
			MakeIngredient(glm::vec3(130, 220, 0), EIngredientType::BunBottom, m_Scene, false, m_Players);


			MakeIngredient(glm::vec3(215, 102, 0), EIngredientType::Bun, m_Scene, false, m_Players);
			MakeIngredient(glm::vec3(215, 135, 0), EIngredientType::Cheese, m_Scene, false, m_Players);
			MakeIngredient(glm::vec3(215, 190, 0), EIngredientType::Lettuce, m_Scene, false, m_Players);
			MakeIngredient(glm::vec3(215, 340, 0), EIngredientType::BunBottom, m_Scene, false, m_Players);

			MakeIngredient(glm::vec3(300, 102, 0), EIngredientType::Bun, m_Scene, false, m_Players);
			MakeIngredient(glm::vec3(300, 250, 0), EIngredientType::Cheese, m_Scene, false, m_Players);
			MakeIngredient(glm::vec3(300, 305, 0), EIngredientType::Lettuce, m_Scene, false, m_Players);
			MakeIngredient(glm::vec3(300, 340, 0), EIngredientType::BunBottom, m_Scene, false, m_Players);

			MakeIngredient(glm::vec3(387, 102, 0), EIngredientType::Bun, m_Scene, false, m_Players);
			MakeIngredient(glm::vec3(387, 165, 0), EIngredientType::Lettuce, m_Scene, false, m_Players);
			MakeIngredient(glm::vec3(387, 190, 0), EIngredientType::Cheese, m_Scene, false, m_Players);
			MakeIngredient(glm::vec3(387, 220, 0), EIngredientType::BunBottom, m_Scene, false, m_Players);*/

			const rapidjson::Value& ingredients = level["ingredients"];
			for (rapidjson::Value::ConstValueIterator it = ingredients.Begin(); it != ingredients.End(); it++)
			{
				const rapidjson::Value& ingredient = *it;

				MakeIngredient(glm::vec3(ingredient["x"].GetFloat(), ingredient["y"].GetFloat(), 0), static_cast<EIngredientType>(ingredient["type"].GetInt()), m_Scene, true, m_Players);


			}
#pragma endregion ingredients
			
		}
#pragma endregion level2
		break;
	case 3:
#pragma region level3
		{
			ClearLevel();
			
			for (size_t i = 0; i < m_LvlBackground.size(); i++)
			{
				if (i == levelCount - 1)
				{
					m_LvlBackground.at(i)->SetVisibility(true);
				}
				else
				{
					m_LvlBackground.at(i)->SetVisibility(false);
				}
			}
			//Player Start Pos

			assert(m_Doc.HasMember("level3"));
			const rapidjson::Value& level = m_Doc["level3"];
			for (auto o : m_Players)
			{
				//o->SetPosition(glm::vec3(110, 100,1));
				o->SetPosition(level["playerStart"]["x"].GetFloat(), level["playerStart"]["y"].GetFloat());

			}
			/*for (auto o : m_Players)
			{
				o->SetPosition(glm::vec3(103, 100, 1));

			}*/

			for (auto o : m_EnemyPlayers)
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
				go->SetDebugDraw(true);
				go->SetTag("Ladder");
				m_LevelObjects.push_back(go);
				m_Scene->Add(go);

			}
		/*	auto go = new GameObject;
			go->SetSize(glm::vec3(m_LadderSize.x, 95, m_LadderSize.z));
			go->SetPosition(109, 105);
			go->SetDebugDraw(true);
			go->SetTag("Ladder");
			m_LevelObjects.push_back(go);
			m_Scene->Add(go);

			go = new GameObject;
			go->SetSize(glm::vec3(m_LadderSize.x, 70, m_LadderSize.z));
			go->SetPosition(109, 310);
			go->SetDebugDraw(true);
			go->SetTag("Ladder");
			m_LevelObjects.push_back(go);
			m_Scene->Add(go);*/

		/*	go = new GameObject;
			go->SetSize(glm::vec3(m_LadderSize.x, 70, m_LadderSize.z));
			go->SetPosition(153, 310);
			go->SetDebugDraw(true);
			go->SetTag("Ladder");
			m_LevelObjects.push_back(go);
			m_Scene->Add(go);*/

		/*	go = new GameObject;
			go->SetSize(glm::vec3(m_LadderSize.x, 70, m_LadderSize.z));
			go->SetPosition(196, 105);
			go->SetDebugDraw(true);
			go->SetTag("Ladder");
			m_LevelObjects.push_back(go);
			m_Scene->Add(go);*/

			//go = new GameObject;
			//go->SetSize(glm::vec3(m_LadderSize.x, 235, m_LadderSize.z));
			//go->SetPosition(195, 195);
			//go->SetDebugDraw(true);
			//go->SetTag("Ladder");
			//m_LevelObjects.push_back(go);
			//m_Scene->Add(go);

			//go = new GameObject;
			//go->SetSize(glm::vec3(m_LadderSize.x, 40, m_LadderSize.z));
			//go->SetPosition(239, 105);
			//go->SetDebugDraw(true);
			//go->SetTag("Ladder");
			//m_LevelObjects.push_back(go);
			//m_Scene->Add(go);

		/*	go = new GameObject;
			go->SetSize(glm::vec3(m_LadderSize.x, 95, m_LadderSize.z));
			go->SetPosition(239, 165);
			go->SetDebugDraw(true);
			go->SetTag("Ladder");
			m_LevelObjects.push_back(go);
			m_Scene->Add(go);*/

		/*	go = new GameObject;
			go->SetSize(glm::vec3(m_LadderSize.x, 34, m_LadderSize.z));
			go->SetPosition(239, 396);
			go->SetDebugDraw(true);
			go->SetTag("Ladder");
			m_LevelObjects.push_back(go);
			m_Scene->Add(go);*/

		/*	go = new GameObject;
			go->SetSize(glm::vec3(m_LadderSize.x, 125, m_LadderSize.z));
			go->SetPosition(282, 135);
			go->SetDebugDraw(true);
			go->SetTag("Ladder");
			m_LevelObjects.push_back(go);
			m_Scene->Add(go);*/

			//go = new GameObject;
			//go->SetSize(glm::vec3(m_LadderSize.x, 34, m_LadderSize.z));
			//go->SetPosition(281, 396);
			//go->SetDebugDraw(true);
			//go->SetTag("Ladder");
			//m_LevelObjects.push_back(go);
			//m_Scene->Add(go);

		/*	go = new GameObject;
			go->SetSize(glm::vec3(m_LadderSize.x, 40, m_LadderSize.z));
			go->SetPosition(324, 105);
			go->SetDebugDraw(true);
			go->SetTag("Ladder");
			m_LevelObjects.push_back(go);
			m_Scene->Add(go);*/

			//go = new GameObject;
			//go->SetSize(glm::vec3(m_LadderSize.x, 40, m_LadderSize.z));
			//go->SetPosition(324, 195);
			//go->SetDebugDraw(true);
			//go->SetTag("Ladder");
			//m_LevelObjects.push_back(go);
			//m_Scene->Add(go);

		/*	go = new GameObject;
			go->SetSize(glm::vec3(m_LadderSize.x, 34, m_LadderSize.z));
			go->SetPosition(324, 396);
			go->SetDebugDraw(true);
			go->SetTag("Ladder");
			m_LevelObjects.push_back(go);
			m_Scene->Add(go);*/


		/*	go = new GameObject;
			go->SetSize(glm::vec3(m_LadderSize.x, 70, m_LadderSize.z));
			go->SetPosition(369, 135);
			go->SetDebugDraw(true);
			go->SetTag("Ladder");
			m_LevelObjects.push_back(go);
			m_Scene->Add(go);*/


			//go = new GameObject;
			//go->SetSize(glm::vec3(m_LadderSize.x, 205, m_LadderSize.z));
			//go->SetPosition(369, 225);
			//go->SetDebugDraw(true);
			//go->SetTag("Ladder");
			//m_LevelObjects.push_back(go);
			//m_Scene->Add(go);

			

		/*	go = new GameObject;
			go->SetSize(glm::vec3(m_LadderSize.x, 36, m_LadderSize.z));
			go->SetPosition(411, 344);
			go->SetDebugDraw(true);
			go->SetTag("Ladder");
			m_LevelObjects.push_back(go);
			m_Scene->Add(go);*/

			//go = new GameObject;
			//go->SetSize(glm::vec3(m_LadderSize.x, 100, m_LadderSize.z));
			//go->SetPosition(455, 105);
			//go->SetDebugDraw(true);
			//go->SetTag("Ladder");
			//m_LevelObjects.push_back(go);
			//m_Scene->Add(go);

			//go = new GameObject;
			//go->SetSize(glm::vec3(m_LadderSize.x, 70, m_LadderSize.z));
			//go->SetPosition(455, 310);
			//go->SetDebugDraw(true);
			//go->SetTag("Ladder");
			//m_LevelObjects.push_back(go);
			//m_Scene->Add(go);

#pragma endregion ladder

#pragma region platform

			const rapidjson::Value& platforms = level["platforms"];
			for (rapidjson::Value::ConstValueIterator it = platforms.Begin(); it != platforms.End(); it++)
			{
				const rapidjson::Value& platform = *it;


				auto go = new GameObject;
				go->SetSize(glm::vec3(platform["size"].GetFloat(), m_PlatformSize.y, m_PlatformSize.z));
				go->SetPosition(platform["x"].GetFloat(), platform["y"].GetFloat());
				go->SetDebugDraw(true);
				go->SetTag("Platform");
				m_LevelObjects.push_back(go);
				m_Scene->Add(go);

			}

			/*go = new GameObject;
			go->SetSize(glm::vec3(355, m_PlatformSize.y, m_PlatformSize.z));
			go->SetPosition(109, 105);
			go->SetDebugDraw(true);
			go->SetTag("Platform");
			m_LevelObjects.push_back(go);
			m_Scene->Add(go);*/

			/*go = new GameObject;
			go->SetSize(glm::vec3(355, m_PlatformSize.y, m_PlatformSize.z));
			go->SetPosition(109, 135);
			go->SetDebugDraw(true);
			go->SetTag("Platform");
			m_LevelObjects.push_back(go);
			m_Scene->Add(go);*/

			/*go = new GameObject;
			go->SetSize(glm::vec3(182, m_PlatformSize.y, m_PlatformSize.z));
			go->SetPosition(109, 165);
			go->SetDebugDraw(true);
			go->SetTag("Platform");
			m_LevelObjects.push_back(go);
			m_Scene->Add(go);*/

			//go = new GameObject;
			//go->SetSize(glm::vec3(355, m_PlatformSize.y, m_PlatformSize.z));
			//go->SetPosition(109, 195);
			//go->SetDebugDraw(true);
			//go->SetTag("Platform");
			//m_LevelObjects.push_back(go);
			//m_Scene->Add(go);

			//go = new GameObject;
			//go->SetSize(glm::vec3(95, m_PlatformSize.y, m_PlatformSize.z));
			//go->SetPosition(109, 310);
			//go->SetDebugDraw(true);
			//go->SetTag("Platform");
			//m_LevelObjects.push_back(go);
			//m_Scene->Add(go);

			//go = new GameObject;
			//go->SetSize(glm::vec3(95, m_PlatformSize.y, m_PlatformSize.z));
			//go->SetPosition(109, 335);
			//go->SetDebugDraw(true);
			//go->SetTag("Platform");
			//m_LevelObjects.push_back(go);
			//m_Scene->Add(go);

			/*go = new GameObject;
			go->SetSize(glm::vec3(95, m_PlatformSize.y, m_PlatformSize.z));
			go->SetPosition(109, 370);
			go->SetDebugDraw(true);
			go->SetTag("Platform");
			m_LevelObjects.push_back(go);
			m_Scene->Add(go);*/

			/*go = new GameObject;
			go->SetSize(glm::vec3(182, m_PlatformSize.y, m_PlatformSize.z));
			go->SetPosition(196, 250);
			go->SetDebugDraw(true);
			go->SetTag("Platform");
			m_LevelObjects.push_back(go);
			m_Scene->Add(go);*/

		/*	go = new GameObject;
			go->SetSize(glm::vec3(183, m_PlatformSize.y, m_PlatformSize.z));
			go->SetPosition(195, 396);
			go->SetDebugDraw(true);
			go->SetTag("Platform");
			m_LevelObjects.push_back(go);
			m_Scene->Add(go);*/

			/*go = new GameObject;
			go->SetSize(glm::vec3(183, m_PlatformSize.y, m_PlatformSize.z));
			go->SetPosition(195, 420);
			go->SetDebugDraw(true);
			go->SetTag("Platform");
			m_LevelObjects.push_back(go);
			m_Scene->Add(go);*/

		/*	go = new GameObject;
			go->SetSize(glm::vec3(96, m_PlatformSize.y, m_PlatformSize.z));
			go->SetPosition(282, 225);
			go->SetDebugDraw(true);
			go->SetTag("Platform");
			m_LevelObjects.push_back(go);
			m_Scene->Add(go);*/

			//go = new GameObject;
			//go->SetSize(glm::vec3(95, m_PlatformSize.y, m_PlatformSize.z));
			//go->SetPosition(369, 165);
			//go->SetDebugDraw(true);
			//go->SetTag("Platform");
			//m_LevelObjects.push_back(go);
			//m_Scene->Add(go);

			/*go = new GameObject;
			go->SetSize(glm::vec3(95, m_PlatformSize.y, m_PlatformSize.z));
			go->SetPosition(369, 310);
			go->SetDebugDraw(true);
			go->SetTag("Platform");
			m_LevelObjects.push_back(go);
			m_Scene->Add(go);*/

		/*	go = new GameObject;
			go->SetSize(glm::vec3(95, m_PlatformSize.y, m_PlatformSize.z));
			go->SetPosition(369, 335);
			go->SetDebugDraw(true);
			go->SetTag("Platform");
			m_LevelObjects.push_back(go);
			m_Scene->Add(go);*/

			/*go = new GameObject;
			go->SetSize(glm::vec3(95, m_PlatformSize.y, m_PlatformSize.z));
			go->SetPosition(369, 370);
			go->SetDebugDraw(true);
			go->SetTag("Platform");
			m_LevelObjects.push_back(go);
			m_Scene->Add(go);*/
#pragma endregion platform

#pragma region container

			const rapidjson::Value& containers = level["container"];
			for (rapidjson::Value::ConstValueIterator it = containers.Begin(); it != containers.End(); it++)
			{
				const rapidjson::Value& container = *it;


				auto go = new GameObject;
				go->SetSize(glm::vec3(m_ContainerSize.x, m_ContainerSize.y, m_PlatformSize.z));
				go->SetPosition(container["x"].GetFloat(), container["y"].GetFloat());
				go->SetDebugDraw(true);
				go->SetTag("Container");
				m_LevelObjects.push_back(go);
				go->AddComponent<ContainerComponent>(new ContainerComponent(container["amount"].GetInt()));
				m_Scene->Add(go);

			}

			const rapidjson::Value& containersPlatforms = level["containerPlatform"];
			for (rapidjson::Value::ConstValueIterator it = containersPlatforms.Begin(); it != containersPlatforms.End(); it++)
			{
				const rapidjson::Value& containerPlatform = *it;


				auto go = new GameObject;
				go->SetSize(glm::vec3(m_ContainerSize.x, m_PlatformSize.y, m_PlatformSize.z));
				go->SetPosition(containerPlatform["x"].GetFloat(), containerPlatform["y"].GetFloat());
				go->SetDebugDraw(true);
				go->SetTag("Platform");
				m_LevelObjects.push_back(go);
				m_Scene->Add(go);

			}
		/*	auto go = new GameObject;
			go->SetSize(glm::vec3(m_ContainerSize.x, m_PlatformSize.y, m_PlatformSize.z));
			go->SetPosition(124, 282);
			go->SetDebugDraw(true);
			go->SetTag("Platform");
			m_LevelObjects.push_back(go);
			m_Scene->Add(go);*/

		/*	go = new GameObject;
			go->SetSize(glm::vec3(m_ContainerSize.x, m_ContainerSize.y, m_PlatformSize.z));
			go->SetPosition(125, 222);
			go->SetDebugDraw(true);
			go->SetTag("Container");
			m_LevelObjects.push_back(go);
			go->AddComponent<ContainerComponent>(new ContainerComponent());
			m_Scene->Add(go);*/


			/*go = new GameObject;
			go->SetSize(glm::vec3(m_ContainerSize.x, m_PlatformSize.y, m_PlatformSize.z));
			go->SetPosition(125, 455);
			go->SetDebugDraw(true);
			go->SetTag("Platform");
			m_LevelObjects.push_back(go);
			m_Scene->Add(go);*/

			/*go = new GameObject;
			go->SetSize(glm::vec3(m_ContainerSize.x, m_ContainerSize.y, m_PlatformSize.z));
			go->SetPosition(125, 395);
			go->SetDebugDraw(true);
			go->SetTag("Container");
			m_LevelObjects.push_back(go);
			go->AddComponent<ContainerComponent>(new ContainerComponent());
			m_Scene->Add(go);*/


			//go = new GameObject;
			//go->SetSize(glm::vec3(m_ContainerSize.x, m_PlatformSize.y, m_PlatformSize.z));
			//go->SetPosition(212, 370);
			//go->SetDebugDraw(true);
			//go->SetTag("Platform");
			//m_LevelObjects.push_back(go);
			//m_Scene->Add(go);

			//go = new GameObject;
			//go->SetSize(glm::vec3(m_ContainerSize.x, m_ContainerSize.y, m_PlatformSize.z));
			//go->SetPosition(212, 310);
			//go->SetDebugDraw(true);
			//go->SetTag("Container");
			//m_LevelObjects.push_back(go);
			//go->AddComponent<ContainerComponent>(new ContainerComponent());
			//m_Scene->Add(go);


		/*	go = new GameObject;
			go->SetSize(glm::vec3(m_ContainerSize.x, m_PlatformSize.y, m_PlatformSize.z));
			go->SetPosition(298, 370);
			go->SetDebugDraw(true);
			go->SetTag("Platform");
			m_LevelObjects.push_back(go);
			m_Scene->Add(go);*/

			//go = new GameObject;
			//go->SetSize(glm::vec3(m_ContainerSize.x, m_ContainerSize.y, m_PlatformSize.z));
			//go->SetPosition(298, 310);
			//go->SetDebugDraw(true);
			//go->SetTag("Container");
			//m_LevelObjects.push_back(go);
			//go->AddComponent<ContainerComponent>(new ContainerComponent());
			//m_Scene->Add(go);

			/*go = new GameObject;
			go->SetSize(glm::vec3(m_ContainerSize.x, m_PlatformSize.y, m_PlatformSize.z));
			go->SetPosition(384, 455);
			go->SetDebugDraw(true);
			go->SetTag("Platform");
			m_LevelObjects.push_back(go);
			m_Scene->Add(go);*/

			/*go = new GameObject;
			go->SetSize(glm::vec3(m_ContainerSize.x, m_ContainerSize.y, m_PlatformSize.z));
			go->SetPosition(384, 395);
			go->SetDebugDraw(true);
			go->SetTag("Container");
			m_LevelObjects.push_back(go);
			go->AddComponent<ContainerComponent>(new ContainerComponent());
			m_Scene->Add(go);*/

			//go = new GameObject;
			//go->SetSize(glm::vec3(m_ContainerSize.x, m_PlatformSize.y, m_PlatformSize.z));
			//go->SetPosition(384, 282);
			//go->SetDebugDraw(true);
			//go->SetTag("Platform");
			//m_LevelObjects.push_back(go);
			//m_Scene->Add(go);

			/*go = new GameObject;
			go->SetSize(glm::vec3(m_ContainerSize.x, m_ContainerSize.y, m_PlatformSize.z));
			go->SetPosition(384, 222);
			go->SetDebugDraw(true);
			go->SetTag("Container");
			m_LevelObjects.push_back(go);
			go->AddComponent<ContainerComponent>(new ContainerComponent());
			m_Scene->Add(go);*/
#pragma endregion container

#pragma region ingrediens
			const rapidjson::Value& ingredients = level["ingredients"];
			for (rapidjson::Value::ConstValueIterator it = ingredients.Begin(); it != ingredients.End(); it++)
			{
				const rapidjson::Value& ingredient = *it;

				MakeIngredient(glm::vec3(ingredient["x"].GetFloat(), ingredient["y"].GetFloat(), 0), static_cast<EIngredientType>(ingredient["type"].GetInt()), m_Scene, true, m_Players);


			}

			//MakeIngredient(glm::vec3(130, 102, 0), EIngredientType::Bun, m_Scene, false, m_Players);
			//MakeIngredient(glm::vec3(130, 165, 0), EIngredientType::Patty, m_Scene, false, m_Players);
			//MakeIngredient(glm::vec3(130, 190, 0), EIngredientType::BunBottom, m_Scene, false, m_Players);


			//MakeIngredient(glm::vec3(130, 305, 0), EIngredientType::Bun, m_Scene, false, m_Players);
			//MakeIngredient(glm::vec3(130, 340, 0), EIngredientType::Tomato, m_Scene, false, m_Players);
			//MakeIngredient(glm::vec3(130, 360, 0), EIngredientType::BunBottom, m_Scene, false, m_Players);

		/*	MakeIngredient(glm::vec3(215, 102, 0), EIngredientType::Bun, m_Scene, false, m_Players);
			MakeIngredient(glm::vec3(215, 135, 0), EIngredientType::Tomato, m_Scene, false, m_Players);
			MakeIngredient(glm::vec3(215, 190, 0), EIngredientType::BunBottom, m_Scene, false, m_Players);*/

			//MakeIngredient(glm::vec3(300, 102, 0), EIngredientType::Bun, m_Scene, false, m_Players);
			//MakeIngredient(glm::vec3(300, 135, 0), EIngredientType::Patty, m_Scene, false, m_Players);
			//MakeIngredient(glm::vec3(300, 190, 0), EIngredientType::BunBottom, m_Scene, false, m_Players);

		/*	MakeIngredient(glm::vec3(387, 102, 0), EIngredientType::Bun, m_Scene, false, m_Players);
			MakeIngredient(glm::vec3(387, 165, 0), EIngredientType::Tomato, m_Scene, false, m_Players);
			MakeIngredient(glm::vec3(387, 190, 0), EIngredientType::BunBottom, m_Scene, false, m_Players);*/

		/*	MakeIngredient(glm::vec3(387, 305, 0), EIngredientType::Bun, m_Scene, false, m_Players);
			MakeIngredient(glm::vec3(387, 340, 0), EIngredientType::Patty, m_Scene, false, m_Players);
			MakeIngredient(glm::vec3(387, 360, 0), EIngredientType::BunBottom, m_Scene, false, m_Players);*/

#pragma endregion ingrediens
			
		}
#pragma endregion level3

		break;
	case 4:
		HighscoreManager::GetInstance().AddHighscore(m_Players.at(0)->GetComponent<ValuesComponent>()->GetScores());
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
	
	for(auto o: m_LevelObjects)
	{
		o->Delete();
	}
	m_LevelObjects.clear();
}

int dae::LevelManager::GetCurLevel() const
{
	return m_Level;
}

void dae::LevelManager::CheckLevelCompleted()
{
	int count{};
	std::vector<GameObject*> AllContainers;
	AllContainers = m_Scene->GetObjectsInWorldWithTag("Container");
	for(auto o : AllContainers)
	{
		if(o->GetComponent<ContainerComponent>()->GetIsFilled() == true)
		{
			count++;
		}
	}
	if(count == AllContainers.size())
	{
		std::cout << "won";
		m_Level++;
		m_LevelMade = false;
	}

	//TEST
	for(auto o:m_Players)
	{
		if(o->GetComponent<PeterPepperComponent>()->GetNextLevel())
		{
			std::cout << "won";
			m_Level++;
			m_LevelMade = false;
			o->GetComponent<PeterPepperComponent>()->SetNextLevel(false);
		}
	}
}

void dae::LevelManager::MakeIngredient(glm::vec3 pos, EIngredientType ingredientType, Scene* scene, bool debugDraw, std::vector<GameObject*>& players)
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
	//part2->SetPosition(part1->GetSize().x, 0);
	part2->SetPosition(totalSize, 0);
	totalSize += part2->GetSize().x;
	//part3->SetPosition(part1->GetSize().x * 2, 0);
	part3->SetPosition(totalSize, 0);
	totalSize += part3->GetSize().x;
	//part4->SetPosition(part1->GetSize().x * 3, 0);
	part4->SetPosition(totalSize, 0);
	totalSize += part4->GetSize().x;


	totalIngredient->SetDebugDraw(debugDraw);
	part1->SetDebugDraw(debugDraw);
	part2->SetDebugDraw(debugDraw);
	part3->SetDebugDraw(debugDraw);
	part4->SetDebugDraw(debugDraw);


	totalIngredient->SetSize(glm::vec3(totalSize, part1->GetSize().y, 0));
	totalIngredient->SetScale(1.8f, 1.8f);
	//totalIngredient->SetSize(glm::vec3(part1->GetSize().x * 4, part1->GetSize().y, 0));
	totalIngredient->SetTag("Ingredient");

	totalIngredient->SetPosition(pos.x, pos.y);
	totalIngredient->AddComponent<IngredientComponent>(new IngredientComponent);
	totalIngredient->GetComponent<IngredientComponent>()->SetPlayers(players);
	m_LevelObjects.push_back(part1);
	m_LevelObjects.push_back(part2);
	m_LevelObjects.push_back(part3);
	m_LevelObjects.push_back(part4);
	m_LevelObjects.push_back(totalIngredient);
	m_Scene->Add(totalIngredient);
}

void dae::LevelManager::MakeEnemey(glm::vec3 pos, EEnemyType type)
{
	auto HotDog = new GameObject;
	SpriteComponent* enemySprite = new SpriteComponent("PeterPepperSpriteTrans.png", 15, 11);
	//HotDog->AddComponent<SpriteComponent>(new SpriteComponent("PeterPepperSpriteTrans.png", 15, 11));
	//HotDog->AddComponent<BasicEnemyComponent>(new BasicEnemyComponent(type));
	//HotDog->GetComponent<BasicEnemyComponent>()->SetSpriteComp(HotDog->GetComponent<SpriteComponent>());
	HotDog->AddComponent(enemySprite);
	HotDog->AddComponent<BasicEnemyComponent>(new BasicEnemyComponent(EEnemyType::Hotdog, enemySprite));

	//HotDog->AddComponent<TextureComponent>(new TextureComponent("HotDog.png"));
	//HotDog->SetPosition(300, 250);
	HotDog->SetDebugDraw(true);
	HotDog->SetPosition(pos);
	HotDog->SetScale(1.5f, 1.5f);
	HotDog->GetComponent<BasicEnemyComponent>()->SetTarget(m_Players.at(0));
	HotDog->SetTag("Enemy");
	m_LevelObjects.push_back(HotDog);
	m_Scene->Add(HotDog);

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

	//Document doc;
	//doc.ParseStream(stream);
	m_Doc.ParseStream(stream);
	delete[] buffer;
	fclose(file);


}
