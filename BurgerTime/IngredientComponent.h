#pragma once
#include <MonoBehaviour.h>

namespace dae
{
class IngredientComponent :
    public MonoBehaviour
{
public:
	IngredientComponent();
	void Update(float dt);
	void FixedUpdate(float timestep);
	void Render() const;
private:
	float m_FallSpeed;
	int m_PressedCount;
	bool m_isFalling;
	bool m_isBouncing;
	float m_curPlatformHeight;
	float m_lastPlatformHeight;
};
	
}


