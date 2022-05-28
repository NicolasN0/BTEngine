#pragma once
#include <MonoBehaviour.h>
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
	private:
		bool m_IsPressed;
		float m_HeightDiff;
	};
	
}

