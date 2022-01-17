#pragma once

#include "GLFW/glfw3.h"
#include "Window.h"
#include "glm/glm.hpp"

static glm::vec2 getMousePosition()
{
	double x, y;
	glfwGetCursorPos(Window::Get()->GLWindow, &x, &y);
	y = 900 - y;
	return { x, y };
}

static float getMouseX()
{
	return getMousePosition().x;
}

static float getMouseY()
{
	return getMousePosition().y;
}

static bool isKeyPressed(unsigned int key)
{
	if (glfwGetKey(Window::Get()->GLWindow, key) == GLFW_PRESS)
		return true;
	return false;
}

static bool isKeyReleased(unsigned int key)
{
	if (glfwGetKey(Window::Get()->GLWindow, key) == GLFW_RELEASE)
		return true;
	return false;
}

static bool isMouseKeyPressed(unsigned int key)
{
	if (glfwGetMouseButton(Window::Get()->GLWindow, key) == GLFW_PRESS)
		return true;
	return false;
}

static bool isMouseKeyReleased(unsigned int key)
{
	if (glfwGetMouseButton(Window::Get()->GLWindow, key) == GLFW_RELEASE)
		return true;
	return false;
}