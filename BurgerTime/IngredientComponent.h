#pragma once
#include <MonoBehaviour.h>

#include "Scene.h"
#include "ValuesComponent.h"


namespace dae
{
enum class EIngredientType
{
	Bun = 0,
	BunBottom = 1,
	Patty = 2,
	Cheese = 3,
	Lettuce = 4,
	Tomato = 5
};


class IngredientComponent final:
    public MonoBehaviour
{
public:
	IngredientComponent();

	//Core
	void Update(float dt) override;
	void FixedUpdate(float timestep) override;
	void Render() const override;

	//Getters
	bool GetIsFalling() const;

	//Setter
	void SetPlayers(const std::vector<GameObject*>& players);
	void SetIsFalling(bool isFalling);

	//Public functions
	void InstantLetFall();
	void CheckPressedAmount();

private:
	//Checkers
	void CheckCollisionPlayer() const;
	void CheckCollisionIngredient();
	void CheckContainerOverlap();
	void CheckCollisionPlatform();
	void CheckCollisionEnemy() const;

	//Private functions
	void ResetFalling();
	void Bounce(float dt);
	void InitializeValuesComp();
	void KillStandingEnemies();
	void SpawnStandingScoresEffect(int numberEnemies) const;

	bool m_isFalling;
	bool m_BouncingDown;
	bool m_isBouncing;
	bool m_inContainer;
	bool m_isCollected;
	bool m_HasMoved;

	float m_BounceSpeed;
	float m_MaxBounceHeight;
	float m_CurrentBounceHeight;
	float m_FallSpeed;
	float m_curPlatformHeight;
	float m_lastPlatformHeight;
	float m_PlatformSize;
	float m_IngredientSize;

	int m_PressedCount;
	int m_StandingEnemies;
	int m_TotalFallingEnemies;


	ValuesComponent* m_pValuesComp;

	std::vector<GameObject*> m_pFallingEnemies;
	std::vector<GameObject*> m_pPlayers;
};


}


