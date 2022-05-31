#include "LevelManager.h"

#include <iostream>

#include "Commands.h"
#include "Scene.h"
#include "ContainerComponent.h"
#include "IngredientPartComponent.h"
#include "InputManager.h"
#include "TextureComponent.h"

dae::LevelManager::LevelManager(Scene* scene, std::vector<GameObject*> players) : m_Level{ 1 }, m_Scene{ scene },m_LevelMade{},m_Players(players)
{
	//First time make level, clear startscreen bindings and add own gameBindings
	MakeLevel(m_Level);
	//Input::GetInstance().ClearKeys();
	
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

		auto go = new GameObject;
		go->AddComponent<dae::TextureComponent>(new dae::TextureComponent("Level1.png"));
		go->SetPosition(100, 100);
		go->SetScale(1.8f, 1.8f);
		m_LevelObjects.push_back(go);
		m_Scene->Add(go);



		glm::vec3 LadderSize = glm::vec3(9, 28, 1);
		glm::vec3 PlatformSize = glm::vec3(91, 10, 1);


		go = new GameObject;
		go->SetSize(glm::vec3(LadderSize.x, LadderSize.y * 2, LadderSize.z));
		go->SetPosition(111, 120);
		go->SetDebugDraw(true);
		go->SetTag("Ladder");
		m_LevelObjects.push_back(go);
		m_Scene->Add(go);

		go = new GameObject;
		go->SetSize(glm::vec3(LadderSize.x, LadderSize.y * 5, LadderSize.z));
		go->SetPosition(111, 245);
		go->SetDebugDraw(true);
		go->SetTag("Ladder");
		m_LevelObjects.push_back(go);
		m_Scene->Add(go);

		go = new GameObject;
		go->SetSize(glm::vec3(LadderSize.x, LadderSize.y * 5, LadderSize.z));
		go->SetPosition(153, 185);
		go->SetDebugDraw(true);
		go->SetTag("Ladder");
		m_LevelObjects.push_back(go);
		m_Scene->Add(go);

		go = new GameObject;
		go->SetSize(glm::vec3(LadderSize.x, LadderSize.y * 10, LadderSize.z));
		go->SetPosition(196, 120);
		go->SetDebugDraw(true);
		go->SetTag("Ladder");
		m_LevelObjects.push_back(go);
		m_Scene->Add(go);

		go = new GameObject;
		go->SetSize(glm::vec3(LadderSize.x, LadderSize.y * 3, LadderSize.z));
		go->SetPosition(241, 120);
		go->SetDebugDraw(true);
		go->SetTag("Ladder");
		m_LevelObjects.push_back(go);
		m_Scene->Add(go);


		go = new GameObject;
		go->SetSize(glm::vec3(LadderSize.x, LadderSize.y * 10, LadderSize.z));
		go->SetPosition(283, 120);
		go->SetDebugDraw(true);
		go->SetTag("Ladder");
		m_LevelObjects.push_back(go);
		m_Scene->Add(go);

		go = new GameObject;
		go->SetSize(glm::vec3(LadderSize.x, LadderSize.y * 3, LadderSize.z));
		go->SetPosition(326, 185);
		go->SetDebugDraw(true);
		go->SetTag("Ladder");
		m_LevelObjects.push_back(go);
		m_Scene->Add(go);

		go = new GameObject;
		go->SetSize(glm::vec3(LadderSize.x, LadderSize.y * 10, LadderSize.z));
		go->SetPosition(369, 120);
		go->SetDebugDraw(true);
		go->SetTag("Ladder");
		m_LevelObjects.push_back(go);
		m_Scene->Add(go);

		go = new GameObject;
		go->SetSize(glm::vec3(LadderSize.x, LadderSize.y * 5, LadderSize.z));
		go->SetPosition(412, 242);
		go->SetDebugDraw(true);
		go->SetTag("Ladder");
		m_LevelObjects.push_back(go);
		m_Scene->Add(go);


		go = new GameObject;
		go->SetSize(glm::vec3(LadderSize.x, LadderSize.y * 4, LadderSize.z));
		go->SetPosition(456, 120);
		go->SetDebugDraw(true);
		go->SetTag("Ladder");
		m_LevelObjects.push_back(go);
		m_Scene->Add(go);

		go = new GameObject;
		go->SetSize(glm::vec3(LadderSize.x, LadderSize.y * 3, LadderSize.z));
		go->SetPosition(456, 300);
		go->SetDebugDraw(true);
		go->SetTag("Ladder");
		m_LevelObjects.push_back(go);
		m_Scene->Add(go);



		go = new GameObject;
		go->SetSize(glm::vec3(PlatformSize.x * 4, PlatformSize.y, PlatformSize.z));
		go->SetPosition(111, 120);
		go->SetDebugDraw(true);
		go->SetTag("Platform");
		m_LevelObjects.push_back(go);
		m_Scene->Add(go);

		go = new GameObject;
		go->SetSize(glm::vec3(PlatformSize.x, PlatformSize.y, PlatformSize.z));
		go->SetPosition(111, 165);
		go->SetDebugDraw(true);
		go->SetTag("Platform");
		m_LevelObjects.push_back(go);
		m_Scene->Add(go);


		go = new GameObject;
		go->SetSize(glm::vec3(PlatformSize.x * 2, PlatformSize.y, PlatformSize.z));
		go->SetPosition(283, 165);
		go->SetDebugDraw(true);
		go->SetTag("Platform");
		m_LevelObjects.push_back(go);
		m_Scene->Add(go);

		go = new GameObject;
		go->SetSize(glm::vec3(PlatformSize.x, PlatformSize.y, PlatformSize.z));
		go->SetPosition(196, 195);
		go->SetDebugDraw(true);
		go->SetTag("Platform");
		m_LevelObjects.push_back(go);
		m_Scene->Add(go);

		go = new GameObject;
		go->SetSize(glm::vec3(PlatformSize.x, PlatformSize.y, PlatformSize.z));
		go->SetPosition(111, 220);
		go->SetDebugDraw(true);
		go->SetTag("Platform");
		m_LevelObjects.push_back(go);
		m_Scene->Add(go);

		go = new GameObject;
		go->SetSize(glm::vec3(PlatformSize.x, PlatformSize.y, PlatformSize.z));
		go->SetPosition(369, 220);
		go->SetDebugDraw(true);
		go->SetTag("Platform");
		m_LevelObjects.push_back(go);
		m_Scene->Add(go);




		go = new GameObject;
		go->SetSize(glm::vec3(PlatformSize.x * 2, PlatformSize.y, PlatformSize.z));
		go->SetPosition(196, 250);
		go->SetDebugDraw(true);
		go->SetTag("Platform");
		m_LevelObjects.push_back(go);
		m_Scene->Add(go);

		go = new GameObject;
		go->SetSize(glm::vec3(PlatformSize.x, PlatformSize.y, PlatformSize.z));
		go->SetPosition(369, 280);
		go->SetDebugDraw(true);
		go->SetTag("Platform");
		m_LevelObjects.push_back(go);
		m_Scene->Add(go);

		go = new GameObject;
		go->SetSize(glm::vec3(PlatformSize.x * 3, PlatformSize.y, PlatformSize.z));
		go->SetPosition(111, 310);
		go->SetDebugDraw(true);
		go->SetTag("Platform");
		m_LevelObjects.push_back(go);
		m_Scene->Add(go);

		go = new GameObject;
		go->SetSize(glm::vec3(PlatformSize.x * 4, PlatformSize.y, PlatformSize.z));
		go->SetPosition(111, 365);
		go->SetDebugDraw(true);
		go->SetTag("Platform");
		m_LevelObjects.push_back(go);
		m_Scene->Add(go);


		float containerWidth{ 65 };
		float containerHeight{ 70 };
		go = new GameObject;
		go->SetSize(glm::vec3(containerWidth, PlatformSize.y, PlatformSize.z));
		go->SetPosition(125, 455);
		go->SetDebugDraw(true);
		go->SetTag("Platform");
		m_LevelObjects.push_back(go);
		m_Scene->Add(go);

		go = new GameObject;
		go->SetSize(glm::vec3(containerWidth, containerHeight, PlatformSize.z));
		go->SetPosition(125, 395);
		go->SetDebugDraw(true);
		go->SetTag("Container");
		m_LevelObjects.push_back(go);
		go->AddComponent<ContainerComponent>(new ContainerComponent());
		m_Scene->Add(go);


		go = new GameObject;
		go->SetSize(glm::vec3(containerWidth, PlatformSize.y, PlatformSize.z));
		go->SetPosition(212, 455);
		go->SetDebugDraw(true);
		go->SetTag("Platform");
		m_LevelObjects.push_back(go);
		m_Scene->Add(go);

		go = new GameObject;
		go->SetSize(glm::vec3(containerWidth, containerHeight, PlatformSize.z));
		go->SetPosition(212, 395);
		go->SetDebugDraw(true);
		go->SetTag("Container");
		m_LevelObjects.push_back(go);
		go->AddComponent<ContainerComponent>(new ContainerComponent());
		m_Scene->Add(go);


		go = new GameObject;
		go->SetSize(glm::vec3(containerWidth, PlatformSize.y, PlatformSize.z));
		go->SetPosition(298, 455);
		go->SetDebugDraw(true);
		go->SetTag("Platform");
		m_LevelObjects.push_back(go);
		m_Scene->Add(go);

		go = new GameObject;
		go->SetSize(glm::vec3(containerWidth, containerHeight, PlatformSize.z));
		go->SetPosition(298, 395);
		go->SetDebugDraw(true);
		go->SetTag("Container");
		m_LevelObjects.push_back(go);
		go->AddComponent<ContainerComponent>(new ContainerComponent());
		m_Scene->Add(go);

		go = new GameObject;
		go->SetSize(glm::vec3(containerWidth, PlatformSize.y, PlatformSize.z));
		go->SetPosition(384, 455);
		go->SetDebugDraw(true);
		go->SetTag("Platform");
		m_LevelObjects.push_back(go);
		m_Scene->Add(go);

		go = new GameObject;
		go->SetSize(glm::vec3(containerWidth, containerHeight, PlatformSize.z));
		go->SetPosition(384, 395);
		go->SetDebugDraw(true);
		go->SetTag("Container");
		m_LevelObjects.push_back(go);
		go->AddComponent<ContainerComponent>(new ContainerComponent());
		m_Scene->Add(go);


		MakeIngredient(glm::vec3(130, 165, 0), IngredientType::Bun, m_Scene, false, m_Players);
		MakeIngredient(glm::vec3(130, 220, 0), IngredientType::Lettuce, m_Scene, false, m_Players);
		MakeIngredient(glm::vec3(130, 305, 0), IngredientType::Patty, m_Scene, false, m_Players);
		MakeIngredient(glm::vec3(130, 360, 0), IngredientType::BunBottom, m_Scene, false, m_Players);


		MakeIngredient(glm::vec3(215, 115, 0), IngredientType::Bun, m_Scene, false, m_Players);
		MakeIngredient(glm::vec3(215, 250, 0), IngredientType::Lettuce, m_Scene, false, m_Players);
		MakeIngredient(glm::vec3(215, 305, 0), IngredientType::Patty, m_Scene, false, m_Players);
		MakeIngredient(glm::vec3(215, 360, 0), IngredientType::BunBottom, m_Scene, false, m_Players);

		MakeIngredient(glm::vec3(300, 115, 0), IngredientType::Bun, m_Scene, false, m_Players);
		MakeIngredient(glm::vec3(300, 165, 0), IngredientType::Lettuce, m_Scene, false, m_Players);
		MakeIngredient(glm::vec3(300, 250, 0), IngredientType::Patty, m_Scene, false, m_Players);
		MakeIngredient(glm::vec3(300, 360, 0), IngredientType::BunBottom, m_Scene, false, m_Players);

		MakeIngredient(glm::vec3(387, 115, 0), IngredientType::Bun, m_Scene, false, m_Players);
		MakeIngredient(glm::vec3(387, 165, 0), IngredientType::Lettuce, m_Scene, false, m_Players);
		MakeIngredient(glm::vec3(387, 220, 0), IngredientType::Patty, m_Scene, false, m_Players);
		MakeIngredient(glm::vec3(387, 280, 0), IngredientType::BunBottom, m_Scene, false, m_Players);
		}
#pragma endregion level1
		break;
	case 2:
		ClearLevel();
		std::cout << "level2";
		break;
	case 3:
		break;
	case 4:
		SceneManager::GetInstance().SetCurrentScene("highscore");
		break;
	default:
		std::cout << "no levelcounter";
		break;
	}

	m_LevelMade = true;
	
}

void dae::LevelManager::ClearLevel()
{
	for(auto o: m_LevelObjects)
	{
		//o->Delete();
		o->~GameObject();
	}
	m_LevelObjects.clear();
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
}

void dae::LevelManager::MakeIngredient(glm::vec3 pos, IngredientType ingredientType, Scene* scene, bool debugDraw, std::vector<GameObject*>& players)
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
		case IngredientType::Bun:
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
		case IngredientType::Cheese:
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
		case IngredientType::Lettuce:
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
		case IngredientType::Tomato:
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
		case IngredientType::Patty:
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
		case IngredientType::BunBottom:
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



	part1->SetPosition(0, 0);
	part2->SetPosition(part1->GetSize().x, 0);
	part3->SetPosition(part1->GetSize().x * 2, 0);
	part4->SetPosition(part1->GetSize().x * 3, 0);


	totalIngredient->SetDebugDraw(debugDraw);
	part1->SetDebugDraw(debugDraw);
	part2->SetDebugDraw(debugDraw);
	part3->SetDebugDraw(debugDraw);
	part4->SetDebugDraw(debugDraw);

	totalIngredient->SetScale(1.8f, 1.8f);
	totalIngredient->SetSize(glm::vec3(part1->GetSize().x * 4, part1->GetSize().y, 0));
	totalIngredient->SetTag("Ingredient");

	totalIngredient->SetPosition(pos.x, pos.y);
	totalIngredient->AddComponent<IngredientComponent>(new IngredientComponent);
	totalIngredient->GetComponent<IngredientComponent>()->SetPlayers(players);
	m_Scene->Add(totalIngredient);
}
