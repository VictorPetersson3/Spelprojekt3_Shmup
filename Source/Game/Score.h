#pragma once
#include "MenuObject.h"
#include "MenuManagerSingleton.h"
#include "MenuManager.h"
#include "TextElement.h"


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

	private:
		int myScore;
		Tga2D::CText* myScoreText;
		TextElement* myTextElement;
	};
}


