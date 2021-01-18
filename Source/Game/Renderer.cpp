#include "stdafx.h"
#include "Renderer.h"

void Renderer::Init()
{
	myReadFromBuffer = &myRenderBuffers[1];
	myWriteToBuffer = &myRenderBuffers[0];
}
/// <summary>
/// Add a game object to the render buffer
/// </summary>
void Renderer::RenderRenderCommand(Studio::RenderCommand aRenderCommand)
{
	GetWriteToBuffer().push_back(aRenderCommand);
}

void Renderer::Render(Studio::GameObject& aGameObject)
{
	GetWriteToBuffer().push_back(aGameObject.GetRenderCommand());
}

void Renderer::SwapBuffers()
{
	std::vector<Studio::RenderCommand>* temp_buffer_pointer = &(*myWriteToBuffer);
	myWriteToBuffer = &(*myReadFromBuffer);
	myReadFromBuffer = &(*temp_buffer_pointer);
	myWriteToBuffer->clear();
}

void Renderer::Render()
{
	//Render the CSprite on the render commands
	for (int i = static_cast<int>(myReadFromBuffer->size()); i-- > 0;)
	{
		GetReadFromBuffer()[i].Render();
	}
}

//void Renderer::RenderRenderCommand(const Studio::RenderCommand& aRenderCommand)
//{
//	GetWriteToBuffer().push_back(aRenderCommand);
//}

std::vector<Studio::RenderCommand>& Renderer::GetReadFromBuffer() const
{
	return (*myReadFromBuffer);
}

std::vector<Studio::RenderCommand>& Renderer::GetWriteToBuffer()
{
	return (*myWriteToBuffer);
}
