#pragma once
#include "MainApp.h"

MainApp* MainApp::m_Instance;

void MainApp::onCreate()
{
	Random::Init();
	m_Window = std::make_shared<Window>("Ecotron", 1600, 900);
	Renderer::Init();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_Camera = glm::ortho(0.0f, 1600.0f, 0.0f, 900.0f);
	m_Instance = this;
}
void MainApp::onUpdate()
{
	float firstTime = glfwGetTime();
	float last = firstTime;

	while (m_Window->isRunning && m_isRunning)
	{
		firstTime = glfwGetTime();
		deltaTime = firstTime - last;
		last = firstTime;

		Renderer::beginScene(m_Camera);

		if (m_CurrentLayer)
			m_CurrentLayer->onUpdate(deltaTime);

		m_Window->Update();
	}
}

void MainApp::onDelete()
{
	if (m_CurrentLayer)
		delete m_CurrentLayer;
}

void MainApp::setLayer(Layer* layer)
{
	if (m_CurrentLayer)
		delete m_CurrentLayer;
	m_CurrentLayer = layer;
	m_CurrentLayer->onCreate();
}

void MainApp::Close()
{
	m_isRunning = false;
}
