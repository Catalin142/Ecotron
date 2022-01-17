#pragma once
#include "GunoiCos.h"

static float lerp(float a, float b, float t)
{
	return a + (b - a) * t;
}

class GunoiLac : public Layer
{
public:
	void onCreate() override;
	void onUpdate(float deltaTime) override;

private:
	std::shared_ptr<Texture> m_BackGround;
	std::shared_ptr<Texture> m_EndScreen;

	std::vector<Trash> m_TrashStack;
	std::vector<std::shared_ptr<Texture>> m_TrashTextures;

	glm::vec2 m_MousePosition;

	float m_Cooldown = 0.8f;
	float m_LastCooldown = m_Cooldown;

	bool MouseState = false;
	int Score = 0;
};