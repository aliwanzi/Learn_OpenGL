#pragma once
#include "common.h"

enum TextureType
{
	DIFFUSE = 0,
	SPECULAR,
	NORMAL,
	HEIGHT,
	CUBEMAP
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
	void AddTexture(std::shared_ptr<TextureStruct> spTexture);
	GLuint AddTexture(const std::string& sPath, TextureType eType, bool bflip = false, bool gamma = false, bool hdr = false);
	GLuint AddTexture(std::vector<std::string>& vecCubeMap);
	GLuint AddTexture(int width, int height, void* data);
	const std::map<GLuint, std::shared_ptr<TextureStruct>>& GetTexures()const;
private:
	unsigned int TextureFromFile(const std::string& sPath, bool bflip, bool gamma,bool hdr);
	unsigned int TextureFromCube(std::vector<std::string>& vecCubeMap);
private:
	std::map<GLuint, std::shared_ptr<TextureStruct>> m_mapTextures;
};
