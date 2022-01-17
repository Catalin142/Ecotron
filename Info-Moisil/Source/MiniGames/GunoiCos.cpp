#include "GunoiCos.h"
#include "System/Input.h"
#include "GL/glew.h"
#include "Renderer/Renderer.h"
#include <iostream>
#include "System/Random.h"
#include "MainApp.h"
#include "MainScreen.h"

void GunoiCos::onCreate()
{
	m_BackGround = TextureManager::Load("Resources/Textures/BGJoc1.png");
	m_EndScreen = TextureManager::Load("Resources/Textures/EndScreen1.png");
	m_Trash = TextureManager::Load("Resources/Textures/Bins.png");

	m_TrashBins[0] = TrashBin(TextureManager::Load("Resources/Textures/Hartie.png"), 525.0f, 590.0f, TrashType::Paper);
	m_TrashBins[1] = TrashBin(TextureManager::Load("Resources/Textures/Sticla.png"), 800.0f, 590.0f, TrashType::Glass);
	m_TrashBins[2] = TrashBin(TextureManager::Load("Resources/Textures/Plastic.png"), 1070.0f, 590.0f, TrashType::Plastic);

	m_TrashTextures.push_back(std::make_pair(TextureManager::Load("Resources/Textures/PaperTH.png"), TrashType::Paper));
	m_TrashTextures.push_back(std::make_pair(TextureManager::Load("Resources/Textures/BidonTH.png"), TrashType::Plastic));
	m_TrashTextures.push_back(std::make_pair(TextureManager::Load("Resources/Textures/PlasticTH.png"), TrashType::Plastic));
	m_TrashTextures.push_back(std::make_pair(TextureManager::Load("Resources/Textures/SticlaTH.png"), TrashType::Glass));
	m_TrashTextures.push_back(std::make_pair(TextureManager::Load("Resources/Textures/DozaTH.png"), TrashType::Plastic));
	m_TrashTextures.push_back(std::make_pair(TextureManager::Load("Resources/Textures/CutieTH.png"), TrashType::Paper));
	m_TrashTextures.push_back(std::make_pair(TextureManager::Load("Resources/Textures/BorcanTH.png"), TrashType::Glass));
	m_TrashTextures.push_back(std::make_pair(TextureManager::Load("Resources/Textures/PungaTH.png"), TrashType::Paper));

	for (int i = 0; i < 35; i++)
	{
		auto type = m_TrashTextures[i % m_TrashTextures.size()];
		Trash newt(type.first, 50.0f + Random::Float() * 1500.0f, 50.0f + Random::Float() * 150.0f, type.second);
		newt.m_Rotation = Random::Float() * 360.0f;
		m_TrashStack.push_back(newt);
	}
}

void GunoiCos::onUpdate(float deltaTime)
{
	glClear(GL_COLOR_BUFFER_BIT);
	Renderer::drawQuad(m_BackGround->TextureID, { 800.0f, 450.0f }, { 1620.0f, 900.0f });
	Renderer::drawQuad(m_Trash->TextureID, { 800.0f, 450.0f }, { 1620.0f, 900.0f });

	for (int i = 0; i < 3; i++)
		Renderer::drawQuad(m_TrashBins[i].m_Texture->TextureID, m_TrashBins[i].m_Position, m_TrashBins[i].m_Size);

	if (!m_TrashStack.empty())
	{
		auto mousePos = getMousePosition();
		for (auto& it = m_TrashStack.begin(); it != m_TrashStack.end(); it++)
		{
			auto& th = *it;
			if (th.m_isActive == true)
				Renderer::drawQuad(th.m_Texture->TextureID, th.m_Position, th.m_Size, th.m_Rotation);

			if (isMouseKeyPressed(GLFW_MOUSE_BUTTON_LEFT) && m_TrashActive == false)
				if (mousePos.x > th.m_Position.x - th.m_Size.x / 2 && mousePos.x < th.m_Position.x + th.m_Size.x / 2 &&
					mousePos.y > th.m_Position.y - th.m_Size.y / 2 && mousePos.y < th.m_Position.y + th.m_Size.y / 2)
				{
					m_TrashActive = true;
					m_MainTrash = th;
					m_MainTrash.m_Position = { 800.0f, 220.0f };
					m_MainTrash.m_Rotation = 0.0f;
					m_MainTrash.m_isFlying = false;

					th.m_isActive = false;
					m_isSelected = true;
				}
		}

		for (auto p = m_TrashStack.begin(); p != m_TrashStack.end();)
		{
			if (p->m_isActive == false && !m_TrashActive)
				p = m_TrashStack.erase(p);
			else p++;
		}

		if (m_isSelected && isMouseKeyReleased(GLFW_MOUSE_BUTTON_LEFT))
			m_isSelected = false;

		if (!m_isSelected)
			if (isMouseKeyPressed(GLFW_MOUSE_BUTTON_LEFT))
			{
				if (m_MainTrash.m_isFlying == false)
				{
					m_MousePosition = getMousePosition();
					m_MainTrash.m_isFlying = true;
				}
			}

		if (m_TrashActive && m_MainTrash.m_Position == m_MousePosition)
		{
			m_MainTrash.m_Position = { 800.0f, 220.0f };
			m_MainTrash.m_Rotation = 0.0f;
			m_MainTrash.m_isFlying = false;
		}

		if (m_TrashActive && m_MainTrash.m_isFlying == true)
		{
			m_MainTrash.m_Position = moveTowards(m_MainTrash.m_Position, m_MousePosition, deltaTime * 500.0f);
			m_MainTrash.m_Rotation += deltaTime * 5.0f;

			for (int i = 0; i < 3; i++)
				if (AABB(m_MainTrash.m_Position, m_MainTrash.m_Size, m_TrashBins[i].m_Position, m_TrashBins[i].m_Size))
				{
					if (m_MainTrash.m_Type == m_TrashBins[i].m_Type)
						m_TrashActive = false;
					else
					{
						m_MainTrash.m_Position = { 800.0f, 220.0f };
						m_MainTrash.m_Rotation = 0.0f;
						m_MainTrash.m_isFlying = false;
					}
				}

		}

		//if (AABB(m_MainTrash->m_Position, m_MainTrash->m_Size, m_SecondTrash->m_Position, m_SecondTrash->m_Size))
		//	std::cout << "a";

		if (m_TrashActive)
			Renderer::drawQuad(m_MainTrash.m_Texture->TextureID, m_MainTrash.m_Position, m_MainTrash.m_Size, m_MainTrash.m_Rotation);

		if (isKeyPressed(GLFW_KEY_ESCAPE))
			MainApp::Get()->setLayer(new MainScreen);
	}

	else
	{
		Renderer::drawQuad(m_EndScreen->TextureID, { 800.0f, 450.0f }, { 1620.0f, 900.0f });
		if (isKeyPressed(GLFW_KEY_R))
			MainApp::Get()->setLayer(new GunoiCos);
		else if (isKeyPressed(GLFW_KEY_ENTER))
			MainApp::Get()->setLayer(new MainScreen);
	}
}
