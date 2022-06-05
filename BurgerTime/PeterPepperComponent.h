#pragma once
#include "MonoBehaviour.h"


class Audio;

namespace dae
{
	class SpriteComponent;

	class PeterPepperComponent final:
	    public MonoBehaviour
	{
	public:
		PeterPepperComponent();

		//Core
		void Update(float dt) override;
		void FixedUpdate(float timestep) override;
		void Render() const override;
		
		//Getter
		bool GetIsOnLadder() const;
		bool GetIsOnPlatform() const;
		bool GetNextLevel() const;

		//Setter
		void SetNextLevel(bool nextLevel);
		void SetMoveSpeed(const glm::vec3& movespeed);
		void SetSpriteComp(SpriteComponent* const comp);

		//Public functions
		void UpdatePos(float dt);
		void ThrowSalt() const;

	private:
		//Initializer
		void InitializeSprite() const;
		//Private functions
		void UpdateSprite(float dt);
		void Respawn() const;

		bool m_IsOnLadder;
		bool m_IsOnPlatform;
		bool m_NextLevelTest;
		bool m_IsFlipped;
		bool m_IsFacingRight;

		glm::vec3 m_StartPos;
		glm::vec3 m_Movespeed;

		SpriteComponent* m_pSpriteComp;
		Audio* m_pAudioService;



	};
	
}

