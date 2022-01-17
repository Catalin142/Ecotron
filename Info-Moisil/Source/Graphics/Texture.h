#pragma once
#include <string>
#include <unordered_map>
#include <memory>

struct Texture
{
	Texture() = default;
	Texture(const std::string& filepath);
	~Texture();
	
	unsigned int TextureID;
};

class TextureManager
{
public:
	static std::shared_ptr<Texture> Load(const std::string& filepath);
	static std::unordered_map<std::string, std::shared_ptr<Texture>> m_TextureCache;
};
