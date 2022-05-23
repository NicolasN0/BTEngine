#pragma once
#include "MonoBehaviour.h"
namespace dae
{
	class PlayerInputComponent :
	    public MonoBehaviour
	{
	public:
		void Update(float dt) override;
		void FixedUpdate(float timestep) override;
	private:
		int m_PlayerIndex;

	};
	
}

