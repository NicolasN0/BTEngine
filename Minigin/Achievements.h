#pragma once
#include "Observer.h"
namespace dae
{
	class Achievements final:
	    public Observer
	{
	public:
		void Notify(const GameObject& go, Event event) override;
	};
	
}

