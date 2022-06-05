#pragma once
#include "MonoBehaviour.h"

namespace dae
{
	class FPSComponent final : public MonoBehaviour
	{
	public:
		void Update(float dt) override;
		void FixedUpdate(float timestep) override;
		int GetFPS() const;
	private:
		void DisplayText();

		int m_Frames;
		int m_FPS;
		float m_Gametime;
	};

}

