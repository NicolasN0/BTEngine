#pragma once
#include "SceneManager.h"


namespace dae
{
	class GameObject;
	class Scene final
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		void Add(GameObject* const object);


		void Update(float dt);
		void FixedUpdate(float timestep);
		void Render() const;

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		const std::vector < GameObject*>& GetAllObjectsInWorld() const;
		std::vector < GameObject*> GetObjectsInWorldWithTag(const std::string& tag) const;

		bool IsPointInRectangle(const glm::vec3& point, const glm::vec3& posRectangle, const glm::vec3& sizeRectangle) const;

		const std::string& GetName() const;
	private: 
		explicit Scene(const std::string& name);

		std::string m_Name;
		std::vector <GameObject*> m_pObjects;
		
		
	};

}
