#pragma once
#include <glm/glm.hpp>
#include <memory>
#include <Graphics/Texture.h>

class Button
{
public:
	Button(const std::shared_ptr<Texture>& tex, int x, int y, int width, int height);
	bool isPressed(glm::vec2 mousePos);

	void Render();

private:
	glm::vec2 m_Position;
	glm::vec2 m_Size;
	std::shared_ptr<Texture> m_Texture;

};