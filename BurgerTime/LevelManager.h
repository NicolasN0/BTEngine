#pragma once
#include <MonoBehaviour.h>

#include "BasicEnemyComponent.h"
#include "IngredientComponent.h"
#include "document.h"

namespace dae
{
	class LevelManager :
	    public MonoBehaviour
	{
	public:
		LevelManager(Scene* scene,const std::vector<GameObject*>& players,const  std::vector<GameObject*>& enemeyPlayers,const std::vector<GameObject*>& lvlBackground, const std::wstring& levelFile);

		//Core
		virtual void Update(float dt);
		virtual void FixedUpdate(float timestep);

		//Getter
		int GetCurLevel() const;

		//Public
		void MakeLevel(int levelCount);
		void ClearLevel();
	private:
		void CheckLevelCompleted();
		void MakeIngredient(const glm::vec3& pos, EIngredientType ingredientType, Scene* scene, bool debugDraw, const std::vector<GameObject*>& players);
		void MakeEnemey(const glm::vec3& pos, EEnemyType type);
		void ReadInLevel(const std::wstring& filename);


		bool m_LevelMade;

		int m_Level;
		int m_CurrentEnemies;
		int m_SpawnCount;

		float m_SpawnTimer;
		float m_SpawnMax;

		glm::vec3 m_ContainerSize;
		glm::vec3 m_LadderSize;
		glm::vec3 m_PlatformSize;

		rapidjson::Document m_Doc;

		Scene* m_Scene;

		std::vector<int> m_MaxEnemies;

		std::vector<glm::vec3> m_EnemyPosLevel1;
		std::vector<glm::vec3> m_EnemyPosLevel2;
		std::vector<glm::vec3> m_EnemyPosLevel3;

		std::vector<GameObject*> m_pLevelObjects;
		std::vector<GameObject*> m_pPlayers;
		std::vector<GameObject*> m_pEnemyPlayers;
		std::vector<GameObject*> m_pLvlBackground;


	};
}

