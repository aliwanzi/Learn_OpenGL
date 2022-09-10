#pragma once
#include <iostream>
#include <string>
#include <vector>
enum TextureType
{
	DIFFUSE = 0,
	SPECULAR,
	NORMAL,
	HEIGHT
};

struct TextureStruct
{
	unsigned int uiID;
	TextureType eType;
	std::string sPath;
};

class Texture
{
public:
	Texture();
	~Texture();
	void AddTexture(const char* pcPath, TextureType eType, bool bflip = false, bool gamma = false);
	const std::vector<TextureStruct>& GetTexures()const;
private:
	unsigned int TextureFromFile(const char* pcPath, bool bflip, bool gamma);
private:
	std::vector<TextureStruct> m_vecTextures;
};
