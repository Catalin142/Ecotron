#pragma once
#include <memory>
#include <vector>
#include <array>
#include "System/Layer.h"
#include "Graphics/Texture.h"
#include <glm/glm.hpp>

namespace glm
{
	static bool operator >(const glm::vec2& left, const glm::vec2& right)
	{
		return (left.x > right.x && left.y > right.y);
	}
	static bool operator <(const glm::vec2& left, const glm::vec2& right)
	{
		return (left.x < right.x && left.y < right.y);
	}
}

static bool AABB(glm::vec2 pos1, glm::vec2 size1, glm::vec2 pos2, glm::vec2 size2)
{
	glm::vec2 min1 = { pos1.x - size1.x / 2, pos1.y - size1.y / 2 };
	glm::vec2 max1 = { pos1.x + size1.x / 2, pos1.y + size1.y / 2 };
	glm::vec2 min2 = { pos2.x - size2.x / 2, pos2.y - size2.y / 2 };
	glm::vec2 max2 = { pos2.x + size2.x / 2, pos2.y + size2.y / 2 };

	return (max1 > min2 && min1 < max2) || (max1 < min2 && min1 > max2);
}

static glm::vec2 moveTowards(const glm::vec2& current, const glm::vec2& target, float distanceDelta)
{
	glm::vec2 tract = target - current;
	float remainingDistance = glm::length(tract);
	if (remainingDistance <= distanceDelta || remainingDistance == 0.0f)
		return target;
	else return (current + tract / remainingDistance * distanceDelta);
}

enum class TrashType
{
	Paper,
	Glass,
	Plastic,
};

struct Trash
{
	Trash() = default;
	std::shared_ptr<Texture> m_Texture;

	glm::vec2 m_Position;
	glm::vec2 m_Size = { 100.0f, 100.0f };
	TrashType m_Type;
	bool m_isFlying = false;
	bool m_isActive = true;
	float m_Rotation = 0.0f;

	Trash(const std::shared_ptr<Texture>& tes, int x, int y, TrashType type) : m_Texture(tes), m_Position(x, y), m_Type(type) { }
};

struct TrashBin
{
	TrashBin() = default;

	TrashType m_Type;
	glm::vec2 m_Position;
	glm::vec2 m_Size = {250.0f, 90.0f};

	std::shared_ptr<Texture> m_Texture;

	TrashBin(const std::shared_ptr<Texture>& tes, int x, int y, TrashType type) : m_Texture(tes), m_Position(x, y), m_Type(type) { }
};

class GunoiCos : public Layer
{
public:
	void onCreate() override;
	void onUpdate(float deltaTime) override;

private:
	std::shared_ptr<Texture> m_BackGround;
	std::shared_ptr<Texture> m_EndScreen;

	std::vector<Trash> m_TrashStack;
	std::vector<std::pair<std::shared_ptr<Texture>, TrashType>> m_TrashTextures;

	std::shared_ptr<Texture> m_Trash;
	std::array<TrashBin, 3> m_TrashBins;

	Trash m_MainTrash;
	bool m_TrashActive = false;
	bool m_isSelected = false;

	glm::vec2 m_MousePosition;
};