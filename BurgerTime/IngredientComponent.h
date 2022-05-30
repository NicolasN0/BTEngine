#pragma once
#include <iostream>
#include <MonoBehaviour.h>

#include "Scene.h"
#include "ValuesComponent.h"

enum class IngredientType
{
	Bun,
	BunBottom,
	Patty,
	Cheese,
	Lettuce,
	Tomato
};

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

	void CheckPressedAmount();
	void SetPlayers(std::vector<GameObject*>& players);
private:
	void CheckCollisionPlayer();
	void CheckCollisionIngredient();
	void CheckContainerOverlap();
	void ResetFalling();
	void CheckCollisionPlatform();
	void CheckCollisionEnemy();
	void Bounce(float dt);
	void InitializeValuesComp();
	void KillStandingEnemies();

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
	int m_TotalFallingEnemies;
	bool m_HasMoved;

	ValuesComponent* m_ValuesComp;

	std::vector<GameObject*> m_Players;
};


}


