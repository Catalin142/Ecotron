#pragma once
#include "GunoiCos.h"
#include "UI/Button.h"

class MainScreen : public Layer
{
public:
	void onCreate() override;
	void onUpdate(float deltaTime) override;

private:
	std::shared_ptr<Texture> m_Background;
	std::shared_ptr<Texture> m_InfoTab;
	std::shared_ptr<Texture> m_Logo;

	std::shared_ptr<Button> m_Game1;
	std::shared_ptr<Button> m_Game2;
	std::shared_ptr<Button> m_Exit;

	std::vector<std::pair<Trash, float>> m_TrashStack;
};