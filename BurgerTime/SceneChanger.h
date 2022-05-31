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
	void SetControlObjects(std::vector<dae::GameObject*>);
private:
	friend class Singleton<SceneChanger>;
	SceneChanger() = default;
	std::vector<dae::GameObject*> m_ControlObjects;
	

};
}

