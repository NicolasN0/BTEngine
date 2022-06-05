#pragma once
#include <iostream>

#include "Command.h"
#include "PeterPepperComponent.h"
#include "SelectorComponent.h"
#include "SceneManager.h"
#include <memory>

#include "SceneChanger.h"
#include "BasicEnemyComponent.h"

namespace dae
{
	

	class Selector : public  Command
	{
	public:
		Selector(SelectorComponent* selectorComp,bool goNext,int maxModes) : m_pSelectorComponent(selectorComp), m_GoNext(goNext), m_MaxModes(maxModes) {}
		void Execute(float ) override
		{
		
			if(m_GoNext)
			{
				
				if(m_pSelectorComponent->GetSelected() < m_MaxModes-1)
				{
					m_pSelectorComponent->NextGameMode();
					GameObject* parent = m_pSelectorComponent->GetParent();
					parent->SetPosition(parent->GetPosition().x, parent->GetPosition().y + 40);
				}
			} else
			{
				if (m_pSelectorComponent->GetSelected() > 0)
				{
					m_pSelectorComponent->PreviousGameMode();
					GameObject* parent = m_pSelectorComponent->GetParent();
					parent->SetPosition(parent->GetPosition().x, parent->GetPosition().y - 40);
				}
			
			}
		}
	private:
		SelectorComponent* m_pSelectorComponent;
		int m_MaxModes;
		bool m_GoNext;
	};

	class Continue : public  Command
	{
	public:
		Continue(SelectorComponent* selectorComp) : m_pSelectorComponent(selectorComp) {}
		void Execute(float ) override
		{
		
			switch(m_pSelectorComponent->GetSelected())
			{
			case 0:
				SceneChanger::GetInstance().SetCurrentScene("game");
				break;

			case 1:
				SceneChanger::GetInstance().SetCurrentScene("coop");
				break;

			case 2:
				SceneChanger::GetInstance().SetCurrentScene("pvp");
				break;
			}
		}
	private:
		SelectorComponent* m_pSelectorComponent;
		
	};

	class Replay : public  Command
	{
	public:
		Replay() {}
		void Execute(float ) override
		{
		
			SceneChanger::GetInstance().SetCurrentScene("start");
		}
	private:
		

	};

	class Throw : public Command
	{
	public:
		Throw(PeterPepperComponent* object) : m_pObject(object){}
		void Execute(float ) override
		{
			//Throw salt
			m_pObject->ThrowSalt();

		};

		PeterPepperComponent* m_pObject;
		
	};

#pragma region movement
	class Move : public Command
	{
	public:
		Move(PeterPepperComponent* object, const glm::vec3& moveSpeed) : m_pObject(object), m_MoveSpeed(moveSpeed) {}
		void Execute(float ) override
		{
		
			m_pObject->SetMoveSpeed(m_MoveSpeed);

		}

		PeterPepperComponent* m_pObject;
		glm::vec3 m_MoveSpeed;
	};

	class StopMove : public Command
	{
	public:
		StopMove(PeterPepperComponent* object) : m_pObject(object){};
		void Execute(float ) override
		{
			
			m_pObject->SetMoveSpeed(glm::vec3(0,0,0));

		};

		PeterPepperComponent* m_pObject;
	};

	class MoveHotdog : public Command
	{
	public:
		MoveHotdog(BasicEnemyComponent* object,const glm::vec3& moveSpeed) : m_pObject(object), m_MoveSpeed(moveSpeed) {}
		void Execute(float ) override
		{

			m_pObject->SetDirection(m_MoveSpeed);
			
		};

		BasicEnemyComponent* m_pObject;
		glm::vec3 m_MoveSpeed;
	};

	class StopMoveHotdog : public Command
	{
	public:
		StopMoveHotdog(BasicEnemyComponent* object) : m_pObject(object){}
		void Execute(float ) override
		{

			
			m_pObject->SetDirection(glm::vec3(0,0,0));

		};

		BasicEnemyComponent* m_pObject;
		
	};

	class NextLevel : public Command
	{
	public:
		NextLevel(PeterPepperComponent* object) : m_pObject(object){};
		void Execute(float ) override
		{

			m_pObject->SetNextLevel(true);

		};

		PeterPepperComponent* m_pObject;
		
	};
	
#pragma endregion movement end
}
