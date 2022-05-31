#pragma once
#include <MonoBehaviour.h>
namespace dae
{
	class SelectorComponent :
	    public MonoBehaviour
	{
	public:
		virtual void Update(float dt);
		virtual void FixedUpdate(float timestep);
		void NextGameMode();
		void PreviousGameMode();
		int GetSelected();
	private:
		std::vector<bool> m_GamemodeSelected;
		int m_Selected;
	};
	
}

