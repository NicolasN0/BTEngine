#pragma once
#include "PeterPepperComponent.h"

class PeterPepperState
{
public:
	virtual ~PeterPepperState();
	virtual void Update(dae::PeterPepperComponent& peterPepper);
};

