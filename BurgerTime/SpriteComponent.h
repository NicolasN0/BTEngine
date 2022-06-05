#pragma once
#include <MonoBehaviour.h>

namespace dae
{
	class SpriteComponent final:
	    public MonoBehaviour
	{
	public:
		SpriteComponent(const std::string& filename,int spritesW, int spritesH);

		//Core
		virtual void Update(float dt) override;
		virtual void FixedUpdate(float timestep) override;
		virtual void Render() const override;

		//Setters
		void SetNumberOfFrames(int number);
		void SetFrameRow(int row);
		void SetFramesPerRow(const std::vector<int>& framesPerRow);
		void SetStartFrame(int number);
		void SetPaused(bool pause);
		void SetFlip(bool flip);
	private:
		bool m_Paused;
		bool m_Flip;

		float m_NrFramesPerSec;
		float m_AnimTime;

		int m_AnimFrame;
		int m_NrOfFrames;
		int m_Framerow;
		int m_StartFrame;
		int m_SpritesW;
		int m_SpritesH;

		std::vector<int> m_FramesPerRow;
		std::shared_ptr<Texture2D> m_spTexture;

	};
}

