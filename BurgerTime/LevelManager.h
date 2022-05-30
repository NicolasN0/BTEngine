#pragma once
#include <MonoBehaviour.h>
namespace dae
{
	class LevelManager :
	    public MonoBehaviour
	{
	public:
		LevelManager(Scene* scene);
		virtual void Update(float dt);
		virtual void FixedUpdate(float timestep);
		void MakeLevel(int levelCount);
		void ClearLevel();
	private:
		void CheckLevelCompleted();
		std::vector<GameObject*> m_LevelObjects{};
		int m_Level{};
		Scene* m_Scene;
		bool m_LevelMade{};
	};
}

