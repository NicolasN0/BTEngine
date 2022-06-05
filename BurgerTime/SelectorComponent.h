#pragma once
#include <MonoBehaviour.h>
namespace dae
{
	class SelectorComponent final :
	    public MonoBehaviour
	{
	public:
		//Core
		SelectorComponent();
		virtual void Update(float dt) override;
		virtual void FixedUpdate(float timestep) override;

		//Getter
		int GetSelected() const;

		//Public
		void NextGameMode();
		void PreviousGameMode();
	private:
		std::vector<bool> m_GamemodeSelected;
		int m_Selected;
	};
	
}

