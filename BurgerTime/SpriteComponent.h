#pragma once
#include <MonoBehaviour.h>

namespace dae
{
	class SpriteComponent :
	    public MonoBehaviour
	{
	public:
		SpriteComponent(const std::string& filename,int spritesW, int spritesH);
		virtual void Update(float dt);
		virtual void FixedUpdate(float timestep);
		virtual void Render() const;

		void SetNumberOfFrames(int number);
		void SetFrameRow(int row);
		void SetFramesPerRow(std::vector<int> framesPerRow);
		void SetStartFrame(int number);
		void SetPaused(bool pause);
		void SetFlip(bool flip);
	private:
		std::shared_ptr<Texture2D> m_Texture{};

		float m_NrFramesPerSec;
		float m_AnimTime;
		int m_AnimFrame;
		int m_NrOfFrames;
		int m_Framerow;
		std::vector<int> m_FramesPerRow;
		int m_StartFrame;

		bool m_Paused;
		bool m_Flip;
		bool m_IsFlipped;

		int m_SpritesW;
		int m_SpritesH;
	};
}

