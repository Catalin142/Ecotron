#include "GunoiLac.h"
#include "System/Random.h"
#include "System/Input.h"
#include <GL/glew.h>
#include "Renderer/Renderer.h"
#include "MainApp.h"
#include "MainScreen.h"

void GunoiLac::onCreate()
{
	m_BackGround = TextureManager::Load("Resources/Textures/BGJoc2.png");
	m_EndScreen = TextureManager::Load("Resources/Textures/EndScreen1.png");

	m_TrashTextures.push_back(TextureManager::Load("Resources/Textures/PaperTH.png"));
	m_TrashTextures.push_back(TextureManager::Load("Resources/Textures/BidonTH.png"));
	m_TrashTextures.push_back(TextureManager::Load("Resources/Textures/PlasticTH.png"));
	m_TrashTextures.push_back(TextureManager::Load("Resources/Textures/SticlaTH.png"));
	m_TrashTextures.push_back(TextureManager::Load("Resources/Textures/DozaTH.png"));
	m_TrashTextures.push_back(TextureManager::Load("Resources/Textures/CutieTH.png"));
	m_TrashTextures.push_back(TextureManager::Load("Resources/Textures/BorcanTH.png"));
	m_TrashTextures.push_back(TextureManager::Load("Resources/Textures/PungaTH.png"));
}

void GunoiLac::onUpdate(float deltaTime)
{
	glClear(GL_COLOR_BUFFER_BIT);
	Renderer::drawQuad(m_BackGround->TextureID, { 800.0f, 450.0f }, { 1620.0f, 900.0f });

	if (Score < 40)
	{
		if (m_LastCooldown >= m_Cooldown && m_TrashStack.size() < 30)
		{
			m_LastCooldown = 0.0f;
			Trash newt = Trash(m_TrashTextures[int(Random::Float() * m_TrashTextures.size())],
				50.0f + Random::Float() * 1500.0f, 200.0f + Random::Float() * 650.0f, TrashType::Paper);
			newt.m_Size = { 10.0f, 10.0f };
			newt.m_Rotation = Random::Float() * 360.0f;
			m_TrashStack.push_back(newt);
		}
		m_LastCooldown += deltaTime;

		bool click = false;
		bool mousestate = isMouseKeyPressed(GLFW_MOUSE_BUTTON_LEFT);
		if (mousestate == true && mousestate != MouseState)
			click = true;
		MouseState = mousestate;

		auto mousePos = getMousePosition();
		for (auto& th : m_TrashStack)
		{
			if (th.m_Size.x < 100.0f)
			{
				th.m_Size.x += deltaTime * 20.0f;
				th.m_Size.y += deltaTime * 20.0f;
			}

			if (click)
			{
				if (mousePos.x > th.m_Position.x - th.m_Size.x / 2 && mousePos.x < th.m_Position.x + th.m_Size.x / 2 &&
					mousePos.y > th.m_Position.y - th.m_Size.y / 2 && mousePos.y < th.m_Position.y + th.m_Size.y / 2)
				{
					th.m_isActive = false;
					Score++;
				}
			}

			Renderer::drawQuad(th.m_Texture->TextureID, th.m_Position, th.m_Size, th.m_Rotation);
		}

		for (auto p = m_TrashStack.begin(); p != m_TrashStack.end();)
		{
			if (p->m_isActive == false)
				p = m_TrashStack.erase(p);
			else p++;
		}

		if (isKeyPressed(GLFW_KEY_ESCAPE))
			MainApp::Get()->setLayer(new MainScreen);
	}
	else
	{
		Renderer::drawQuad(m_EndScreen->TextureID, { 800.0f, 450.0f }, { 1620.0f, 900.0f });
		if (isKeyPressed(GLFW_KEY_R))
			MainApp::Get()->setLayer(new GunoiLac);
		else if (isKeyPressed(GLFW_KEY_ENTER))
			MainApp::Get()->setLayer(new MainScreen);
	}
}
