#pragma once
#include <memory>
#include "System/Random.h"
#include "System/Window.h"
#include "System/Layer.h"

#include "Renderer/Renderer.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "glm/gtc/type_ptr.hpp"
class MainApp
{
public:
	void onCreate();
	void onUpdate();
	void onDelete();

	void setLayer(Layer* layer);

	void Close();
	static MainApp* Get() { return m_Instance; }

private:
	std::shared_ptr<Window> m_Window;
	glm::mat4 m_Camera;
	Layer* m_CurrentLayer;

	float deltaTime;

	static MainApp* m_Instance;
	bool m_isRunning = true;
};
