#include "MainScreen.h"
#include "GL/glew.h"
#include "Renderer/Renderer.h"
#include "System/Random.h"
#include "System/Input.h"
#include "MiniGames/GunoiLac.h"
#include "MainApp.h"

void MainScreen::onCreate()
{
	m_Background = TextureManager::Load("Resources/Textures/BGtitle.png");
	m_InfoTab = TextureManager::Load("Resources/Textures/InfoTab.png");
	m_Logo = TextureManager::Load("Resources/Textures/Titlescr.png");

	m_Game1 = std::make_shared<Button>(TextureManager::Load("Resources/Textures/StartStrada.png"), 800, 500, 500, 100);
	m_Game2 = std::make_shared<Button>(TextureManager::Load("Resources/Textures/StartRau.png"), 800, 390, 500, 100);
	m_Exit = std::make_shared<Button>(TextureManager::Load("Resources/Textures/Iesire.png"), 800, 200, 300, 80);

	m_TrashStack.push_back(std::make_pair(Trash(TextureManager::Load("Resources/Textures/PaperTH.png"), Random::Float() * 1600.0f, 1000.0f, TrashType::Glass), 100.0f + Random::Float() * 200.0f));
	m_TrashStack.push_back(std::make_pair(Trash(TextureManager::Load("Resources/Textures/BidonTH.png"), Random::Float() * 1600.0f, 1000.0f, TrashType::Glass), 100.0f + Random::Float() * 200.0f));
	m_TrashStack.push_back(std::make_pair(Trash(TextureManager::Load("Resources/Textures/PlasticTH.png"), Random::Float() * 1600.0f, 1000.0f, TrashType::Glass), 100.0f + Random::Float() * 200.0f));
	m_TrashStack.push_back(std::make_pair(Trash(TextureManager::Load("Resources/Textures/DozaTH.png"), Random::Float() * 1600.0f, 1000.0f, TrashType::Glass), 100.0f + Random::Float() * 200.0f));
	m_TrashStack.push_back(std::make_pair(Trash(TextureManager::Load("Resources/Textures/CutieTH.png"), Random::Float() * 1600.0f, 1000.0f, TrashType::Glass), 100.0f + Random::Float() * 200.0f));
	m_TrashStack.push_back(std::make_pair(Trash(TextureManager::Load("Resources/Textures/SticlaTH.png"), Random::Float() * 1600.0f, 1000.0f, TrashType::Glass), 100.0f + Random::Float() * 200.0f));
	m_TrashStack.push_back(std::make_pair(Trash(TextureManager::Load("Resources/Textures/BorcanTH.png"), Random::Float() * 1600.0f, 1000.0f, TrashType::Glass), 100.0f + Random::Float() * 200.0f));
	m_TrashStack.push_back(std::make_pair(Trash(TextureManager::Load("Resources/Textures/PungaTH.png"), Random::Float() * 1600.0f, 1000.0f, TrashType::Glass), 100.0f + Random::Float() * 200.0f));
}

void MainScreen::onUpdate(float deltaTime)
{
	glClear(GL_COLOR_BUFFER_BIT);

	Renderer::drawQuad(m_Background->TextureID, { 800.0f, 450.0f }, { 1600.0f, 900.0f });

	bool tab = isKeyPressed(GLFW_KEY_TAB);

	if (tab)
		Renderer::drawQuad(m_InfoTab->TextureID, { 800.0f, 450.0f }, { 1600.0f, 900.0f });
	else
	{
		for (auto& th : m_TrashStack)
		{
			th.first.m_Position.y -= th.second * deltaTime;
			if (th.first.m_Position.y < -50.0f)
			{
				th.first.m_Position.y = 1000.0f;
				th.first.m_Position.x = Random::Float() * 1600.0f;
				th.first.m_Rotation = th.second / 200.0f * 360.0f;
				th.second = 100.0f + Random::Float() * 200.0f;
			}

			Renderer::drawQuad(th.first.m_Texture->TextureID, th.first.m_Position, th.first.m_Size, th.first.m_Rotation);
		}

		Renderer::drawQuad(m_Logo->TextureID, { 800.0f, 450.0f }, { 1600.0f, 900.0f });

		m_Game1->Render();
		m_Game2->Render();
		m_Exit->Render();

		auto mousePos = getMousePosition();
		if (isMouseKeyPressed(GLFW_MOUSE_BUTTON_LEFT))
		{
			if (m_Game1->isPressed(mousePos))
				MainApp::Get()->setLayer(new GunoiCos);

			else if (m_Game2->isPressed(mousePos))
				MainApp::Get()->setLayer(new GunoiLac);

			else if (m_Exit->isPressed(mousePos))
				MainApp::Get()->Close();
		}
	}
}
