#pragma once
#include <MonoBehaviour.h>

#include "IngredientComponent.h"

namespace dae
{
	class LevelManager :
	    public MonoBehaviour
	{
	public:
		LevelManager(Scene* scene, std::vector<GameObject*> players);
		virtual void Update(float dt);
		virtual void FixedUpdate(float timestep);
		void MakeLevel(int levelCount);
		void ClearLevel();
	private:
		void CheckLevelCompleted();
		void MakeIngredient(glm::vec3 pos, IngredientType ingredientType, Scene* scene, bool debugDraw, std::vector<GameObject*>& players);
		std::vector<GameObject*> m_LevelObjects{};
		int m_Level{};
		Scene* m_Scene;
		bool m_LevelMade{};
		std::vector<GameObject*> m_Players;
		glm::vec3 m_ContainerSize;
		glm::vec3 m_PlatformSize;
		glm::vec3 m_LadderSize;
	};
}

