#pragma once
#include "Singleton.h"
#include <memory>
namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);

		void Update(float dt);
		void FixedUpdate(float timestep);
		void Render();
		void SetCurrentScene(std::string name);
		void ClearScenes();
		void SetDelete(bool deleteScene);
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_Scenes;
		std::shared_ptr<Scene> m_CurrentScene;
		bool m_DeleteScenes;

	};
}
