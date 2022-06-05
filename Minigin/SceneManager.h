#pragma once
#include "Singleton.h"
#include <memory>
#include <vector>
namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);

		void Update(float dt);
		void FixedUpdate(float timestep);
		void Render() const;
		void SetCurrentScene(const std::string& name);
		void SetDelete(bool deleteScene);
		void ClearScenes();
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_spScenes;
		std::shared_ptr<Scene> m_spCurrentScene;
		bool m_DeleteScenes;

	};
}
