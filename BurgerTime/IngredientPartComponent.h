#pragma once
#include <MonoBehaviour.h>
class Audio;

namespace dae
{
	class IngredientPartComponent :
	    public MonoBehaviour
	{
	public:
		IngredientPartComponent();
		void Update(float dt);
		void FixedUpdate(float timestep);
		void Render() const;

		bool GetIsPressed() const;
		void SetIsPressed(bool isPressed);

		void Reset();
		void UpdatePressed();
	private:
		bool m_IsPressed;
		float m_HeightDiff;

		Audio* m_AudioService;
	};
	
}

