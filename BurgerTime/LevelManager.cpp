#include "LevelManager.h"

#include <iostream>

#include "Scene.h"
#include "ContainerComponent.h"
#include "TextureComponent.h"

dae::LevelManager::LevelManager(Scene* scene) : m_Level{ 1 }, m_Scene{ scene },m_LevelMade{}
{
	MakeLevel(m_Level);
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
	CheckLevelCompleted();
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
		SceneManager::GetInstance().ClearScenes();
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
