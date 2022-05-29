#pragma once
#include "GameObject.h"

namespace dae
{
	enum class Event
	{
		PlayerDied,
		PlayerPickup,
		HotDogKilled,
		EggKilled,
		PickleKilled,
		BurgerDropped,
		Kill,
		DoubleKill,
		TripleKill,
		QuadraKill,
		PentaKill,
		HexaKill,
		GameOver
	};

	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void Notify(const GameObject& go, Event event) = 0;
	};
	
}