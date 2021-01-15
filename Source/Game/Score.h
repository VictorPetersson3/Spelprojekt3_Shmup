#pragma once

namespace Tga2D
{
	class CText;
}
namespace Studio
{
	class RenderCommand;

	class Score
	{
	public:
		Score();
		~Score();
		void Update();
		void Render();
		void AddToScore(int aValue);
		void SetScore(int aValue);

		Tga2D::CText* GetScore();

	private:
		int myScore;
		Tga2D::CText* myScoreText;

	};
}


