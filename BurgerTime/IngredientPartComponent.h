#pragma once
#include <MonoBehaviour.h>
class Audio;

namespace dae
{
	class IngredientPartComponent final:
	    public MonoBehaviour
	{
	public:
		IngredientPartComponent();
		void Update(float dt) override;
		void FixedUpdate(float timestep) override;
		void Render() const override;

		bool GetIsPressed() const;
		void SetIsPressed(bool isPressed);

		void Reset();
		void UpdatePressed();
	private:
		bool m_IsPressed;
		float m_HeightDiff;

		Audio* m_pAudioService;
	};
	
}

