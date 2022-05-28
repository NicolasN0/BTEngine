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

	bool GetIsFalling() const;
	void SetIsFalling(bool isFalling);
	void InstantLetFall();
private:
	void CheckCollisionIngredient();
	void CheckContainerOverlap();
	void ResetFalling();
	void CheckCollisionPlatform();
	void CheckCollisionEnemy();
	void Bounce(float dt);

	float m_CurrentBounceHeight;
	float m_MaxBounceHeight;
	float m_BounceSpeed;
	bool m_BouncingDown;

	float m_FallSpeed;
	int m_PressedCount;
	bool m_isFalling;
	bool m_isBouncing;
	bool m_inContainer;
	bool m_isCollected;
	float m_curPlatformHeight;
	float m_lastPlatformHeight;
	float m_PlatformSize;
	float m_IngredientSize;
	std::vector<GameObject*> m_FallingEnemies;
	int m_StandingEnemies;
	bool m_HasMoved;
};
	
}


