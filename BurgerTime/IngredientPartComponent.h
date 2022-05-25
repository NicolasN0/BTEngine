#pragma once
#include <MonoBehaviour.h>
namespace dae
{
	class IngredientPartComponent :
	    public MonoBehaviour
	{
	public:
		IngredientPartComponent() = default;
		void Update(float dt);
		void FixedUpdate(float timestep);
		void Render() const;

		bool GetIsPressed() const;
		void SetIsPressed(bool isPressed);
	private:
		bool m_IsPressed;
	};
	
}

