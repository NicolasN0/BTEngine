#pragma once
#include <memory>
#include <string>
#include <vector>

#include "GameObject.h"
#include "Singleton.h"

namespace dae
{
	
class SceneChanger final : public dae::Singleton<SceneChanger>
{
public:
	
	void SetCurrentScene(std::string name);
	void SetControlObjects(const std::vector<dae::GameObject*>& controlObjects);
	void SetLevelManagers(const std::vector<dae::GameObject*>& levelManagers);
private:
	friend class Singleton<SceneChanger>;
	SceneChanger() = default;
	std::vector<dae::GameObject*> m_pControlObjects;
	std::vector<dae::GameObject*> m_pLevelManagers;

};
}

