#pragma once
#include <MonoBehaviour.h>
namespace dae
{
	class ContainerComponent :
	    public MonoBehaviour
	{
	public:
		ContainerComponent(int maxIngredient = 4);
		virtual void Update(float dt);
		virtual void FixedUpdate(float timestep);
		bool GetIsFilled() const;
	private:
		bool m_IsFilled;
		int m_MaxIngredient;
	};
	
}

