#pragma once
#include "PeterPepperState.h"
class MovingState :
    public PeterPepperState
{
    virtual void Update(dae::PeterPepperComponent& peterPepper);
};

