#include "Button.h"
#include <Renderer/Renderer.h>

Button::Button(const std::shared_ptr<Texture>& tex, int x, int y, int width, int height): m_Texture(tex), m_Position(x, y), m_Size(width, height)
{
}

bool Button::isPressed(glm::vec2 mousePos)
{
	if (mousePos.x > m_Position.x - m_Size.x / 2 && mousePos.x < m_Position.x + m_Size.x / 2 &&
		mousePos.y > m_Position.y - m_Size.y / 2 && mousePos.y < m_Position.y + m_Size.y / 2)
		return true;

	return false;
}

void Button::Render()
{
	Renderer::drawQuad(m_Texture->TextureID, m_Position, m_Size);
}
