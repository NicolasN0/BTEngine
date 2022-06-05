#pragma once
#include <string>
#include <vector>

#include "Singleton.h"

namespace dae
{
	class GameObject;

class SceneChanger final : public dae::Singleton<SceneChanger>
{
public:
	//Setters
	void SetCurrentScene(const std::string& name);
	void SetControlObjects(const std::vector<dae::GameObject*>& controlObjects);
	void SetLevelManagers(const std::vector<dae::GameObject*>& levelManagers);
private:
	friend class Singleton<SceneChanger>;
	SceneChanger() = default;
	std::vector<dae::GameObject*> m_pControlObjects;
	std::vector<dae::GameObject*> m_pLevelManagers;

};
}

