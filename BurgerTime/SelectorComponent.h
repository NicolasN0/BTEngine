#pragma once
#include <MonoBehaviour.h>
namespace dae
{
	class SelectorComponent :
	    public MonoBehaviour
	{
	public:
		//Core
		SelectorComponent();
		virtual void Update(float dt);
		virtual void FixedUpdate(float timestep);

		//Getter
		int GetSelected();

		//Public
		void NextGameMode();
		void PreviousGameMode();
	private:
		std::vector<bool> m_GamemodeSelected;
		int m_Selected;
	};
	
}

