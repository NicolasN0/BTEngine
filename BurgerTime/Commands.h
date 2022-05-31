#pragma once
#include <iostream>

#include "Command.h"
#include "PeterPepperComponent.h"
#include "SelectorComponent.h"
#include "SceneManager.h"
#include <memory>
namespace dae
{
	



	/*class Fire : public Command
	{
	public:
		void Execute(float dt) override
		{
			std::cout << "Fire";
		};
	};

	class Duck : public Command
	{
	public:
		void Execute(float dt) override
		{
			std::cout << "Duck";
		};
	};

	class Crouch : public Command
	{
	public:
		void Execute(float dt) override
		{
			std::cout << "Crouch";
		};
	};

	class Fart : public Command
	{
	public:
		void Execute(float dt) override
		{
			std::cout << "Fart";
		};
	};*/
	class Selector : public  Command
	{
	public:
		Selector(SelectorComponent* selectorComp,bool goNext,int maxModes) : m_SelectorComponent(selectorComp), m_GoNext(goNext), m_MaxModes(maxModes) {}
		void Execute(float dt) override
		{
			std::cout << "verander";
			if(m_GoNext)
			{
				
				if(m_SelectorComponent->GetSelected() < m_MaxModes-1)
				{
					m_SelectorComponent->NextGameMode();
					GameObject* parent = m_SelectorComponent->GetParent();
					parent->SetPosition(parent->GetPosition().x, parent->GetPosition().y + 40);
				}
			} else
			{
				if (m_SelectorComponent->GetSelected() > 0)
				{
					m_SelectorComponent->PreviousGameMode();
					GameObject* parent = m_SelectorComponent->GetParent();
					parent->SetPosition(parent->GetPosition().x, parent->GetPosition().y - 40);
				}
			
			}
		}
	private:
		SelectorComponent* m_SelectorComponent;
		int m_MaxModes;
		bool m_GoNext;
	};

	class Continue : public  Command
	{
	public:
		Continue(SelectorComponent* selectorComp) : m_SelectorComponent(selectorComp) {}
		void Execute(float dt) override
		{
			std::cout << "continue?";
			switch(m_SelectorComponent->GetSelected())
			{
			case 0:
				SceneManager::GetInstance().SetCurrentScene("game");
				break;

			case 1:
				break;

			case 2:
				break;
			}
		}
	private:
		SelectorComponent* m_SelectorComponent;
		
	};

#pragma region movement
	class Move : public Command
	{
	public:
		Move(PeterPepperComponent* object, glm::vec3 moveSpeed) : m_pObject(object), m_MoveSpeed(moveSpeed) {};
		void Execute(float dt) override
		{
			if(m_MoveSpeed.y > 0 || m_MoveSpeed.y < 0)
			{
				if(m_pObject->GetIsOnLadder() == true)
				{
					glm::vec3 curPos = m_pObject->GetParent()->GetTransform().GetPosition();
					glm::vec3 furPos = glm::vec3(curPos.x + (m_MoveSpeed.x * dt), curPos.y + (m_MoveSpeed.y * dt),1);


					m_pObject->GetParent()->SetPosition(furPos.x, furPos.y);

					if (m_pObject->GetParent()->IsCenterOverlappingAnyWithTag("Ladder") == false)
					{
						m_pObject->GetParent()->SetPosition(curPos.x, curPos.y);
					}
				}

			}
			
			if(m_MoveSpeed.x > 0 || m_MoveSpeed.x < 0)
			{
				if (m_pObject->GetIsOnPlatform() == true)
				{
					glm::vec3 curPos = m_pObject->GetParent()->GetTransform().GetPosition();
					glm::vec3 furPos = glm::vec3(curPos.x + (m_MoveSpeed.x * dt), curPos.y + (m_MoveSpeed.y * dt), 1);
					m_pObject->GetParent()->SetPosition(furPos.x, furPos.y);

					if (m_pObject->GetParent()->IsCenterOverlappingAnyWithTag("Platform") == false)
					{
						m_pObject->GetParent()->SetPosition(curPos.x, curPos.y);
						
					}

				}
			}


		};

		PeterPepperComponent* m_pObject;
		glm::vec3 m_MoveSpeed;
	};

	
#pragma endregion movement end
}