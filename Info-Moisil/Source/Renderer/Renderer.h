#pragma once
#include <memory>
#include "Graphics/Texture.h"
#include "glm/glm.hpp"

struct VertexArray
{
	unsigned int vertexArray;
	unsigned int vertexBuffer;
	unsigned int indexBuffer;
};

class Renderer
{
public:
	static void Init();

	static void beginScene(const glm::mat4& ortho);
	static void drawQuad(unsigned int tex, const glm::vec2& position, const glm::vec2& size, float rot = 0.0f, const glm::vec4& color = { 1.0f, 1.0f, 1.0f, 1.0f });

private:
	Renderer() = default;
	~Renderer() = default;

	static VertexArray m_QuadVertexArray;
	static glm::mat4 m_OrthographicMatrix;

	static void initQuadArray();
};
