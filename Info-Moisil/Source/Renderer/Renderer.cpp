#include "Renderer.h"

#include "Graphics/Shader.h"

#include "glm/gtc/type_ptr.hpp"

VertexArray Renderer::m_QuadVertexArray;

glm::mat4 Renderer::m_OrthographicMatrix;

#include "GL/glew.h"

void Renderer::Init()
{
    // shaders
    ShaderManager::addShader("QuadShader", "Resources/Shaders/2DRenderer_vertex.glsl", "Resources/Shaders/2DRenderer_fragment.glsl");

    initQuadArray();
}

void Renderer::beginScene(const glm::mat4& ortho)
{
    m_OrthographicMatrix = ortho;
}

void Renderer::drawQuad(unsigned int tex, const glm::vec2& position, const glm::vec2& size, float rot, const glm::vec4& color)
{
    auto& shader = ShaderManager::Shaders["QuadShader"];
    glUseProgram(shader->ShaderID);

    glBindVertexArray(m_QuadVertexArray.vertexArray);
    glBindBuffer(GL_ARRAY_BUFFER, m_QuadVertexArray.vertexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_QuadVertexArray.indexBuffer);

    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f)) * glm::rotate(glm::mat4(1.0f), rot, glm::vec3(0.0f, 0.0f, 1.0f)) * 
        glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader->ShaderID, "ortho"), 1, GL_FALSE, &m_OrthographicMatrix[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(shader->ShaderID, "model"), 1, GL_FALSE, &model[0][0]);

    glActiveTexture(GL_TEXTURE0 + 0);
    glBindTexture(GL_TEXTURE_2D, tex);

    glUniform1i(glGetUniformLocation(shader->ShaderID, "tex"), 0);
    glUniform4f(glGetUniformLocation(shader->ShaderID, "color"), color.r, color.g, color.b, color.a);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glUseProgram(0);
}

void Renderer::initQuadArray()
{
    float vert[] = {
         -1.0f, -1.0f, 0.0f, 0.0f,
          1.0f, -1.0f, 1.0f, 0.0f,
         -1.0f,  1.0f, 0.0f, 1.0f,
          1.0f,  1.0f, 1.0f, 1.0f,
    };

    unsigned int indices[] = {
        0, 1, 2,
        1, 2, 3
    };

    glGenVertexArrays(1, &m_QuadVertexArray.vertexArray);

    glGenBuffers(1, &m_QuadVertexArray.vertexBuffer);
    glGenBuffers(1, &m_QuadVertexArray.indexBuffer);

    glBindVertexArray(m_QuadVertexArray.vertexArray);

    glBindBuffer(GL_ARRAY_BUFFER, m_QuadVertexArray.vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vert), vert, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_QuadVertexArray.indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(sizeof(float) * 2));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}