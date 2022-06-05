#pragma once
#include <MonoBehaviour.h>
namespace dae
{
	class ContainerComponent final :
	    public MonoBehaviour
	{
	public:
		ContainerComponent(int maxIngredient = 4);
		virtual void Update(float dt) override;
		virtual void FixedUpdate(float timestep) override;
		bool GetIsFilled() const;
	private:
		bool m_IsFilled;
		int m_MaxIngredient;
	};
	
}

