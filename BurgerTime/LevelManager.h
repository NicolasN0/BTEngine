#pragma once
#include <MonoBehaviour.h>

#include "BasicEnemyComponent.h"
#include "IngredientComponent.h"

namespace dae
{
	class LevelManager :
	    public MonoBehaviour
	{
	public:
		LevelManager(Scene* scene, std::vector<GameObject*> players, std::vector<GameObject*> enemeyPlayers,std::vector<GameObject*>& lvlBackground);
		virtual void Update(float dt);
		virtual void FixedUpdate(float timestep);
		void MakeLevel(int levelCount);
		void ClearLevel();
	private:
		void CheckLevelCompleted();
		void MakeIngredient(glm::vec3 pos, EIngredientType ingredientType, Scene* scene, bool debugDraw, std::vector<GameObject*>& players);
		void MakeEnemey(glm::vec3 pos, EEnemyType type);
		std::vector<GameObject*> m_LevelObjects{};
		int m_Level{};
		Scene* m_Scene;
		bool m_LevelMade{};
		std::vector<GameObject*> m_Players;
		std::vector<GameObject*> m_EnemyPlayers;
		std::vector<GameObject*> m_LvlBackground;
		glm::vec3 m_ContainerSize;
		glm::vec3 m_PlatformSize;
		glm::vec3 m_LadderSize;

		float m_SpawnTimer;
		float m_SpawnMax;
		int m_CurrentEnemies;
		std::vector<int> m_MaxEnemies;
		std::vector<glm::vec3> m_EnemyPosLevel1;
		std::vector<glm::vec3> m_EnemyPosLevel2;
		std::vector<glm::vec3> m_EnemyPosLevel3;

	};
}

