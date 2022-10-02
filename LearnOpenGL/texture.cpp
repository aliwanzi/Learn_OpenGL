#include "texture.h"
#include "glad/glad.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture()
{

}

Texture::~Texture()
{

}

void Texture::AddTexture(const TextureStruct& texture)
{
	m_vecTextures.push_back(texture);
}

void Texture::AddTexture(const std::string& sPath, TextureType eType, bool bflip /*= false*/, bool gamma /*= false*/)
{
	TextureStruct texture;
	texture.sPath = sPath;
	texture.uiID = TextureFromFile(sPath,bflip, gamma);
	texture.eType = eType;
	m_vecTextures.push_back(texture);
}

void Texture::AddTexture(std::vector<std::string>& vecCubeMap)
{
	TextureStruct texture;
	texture.sPath = "";
	texture.uiID = TextureFromCube(vecCubeMap);
	texture.eType = TextureType::CUBEMAP;
	m_vecTextures.push_back(texture);
}

const std::vector<TextureStruct>& Texture::GetTexures()const
{
	return m_vecTextures;
}

unsigned int Texture::TextureFromFile(const std::string& sPath, bool bflip, bool gamma)
{
	unsigned int uiID;
	glGenTextures(1, &uiID);

	int iWidth(0), iHeight(0), iComponent(0);
	stbi_set_flip_vertically_on_load(bflip);
	unsigned char* pImageData = stbi_load(sPath.c_str(), &iWidth, &iHeight, &iComponent, 0);
	if (pImageData != nullptr)
	{
		GLenum eFormat(GL_RED);
		switch (iComponent)
		{
		case 1:
		{
			eFormat = GL_RED;
			break;
		}
		case 3:
		{
			eFormat = GL_RGB;
			break;
		}
		case 4:
		{
			eFormat = GL_RGBA;
			break;
		}
		default:
			break;
		}

		glBindTexture(GL_TEXTURE_2D, uiID);
		glTexImage2D(GL_TEXTURE_2D, 0, eFormat, iWidth, iHeight, 0, eFormat, GL_UNSIGNED_BYTE, pImageData);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, eFormat == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, eFormat == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(pImageData);
	}
	else
	{
		std::cout << "Texture failed to load at path:" << sPath << std::endl;
		stbi_image_free(pImageData);
	}

	return uiID;
}

unsigned int Texture::TextureFromCube(std::vector<std::string>& vecCubeMap)
{
	unsigned int uiID;
	glGenTextures(1, &uiID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, uiID);

	int iWidth(0), iHeight(0), iComponent(0);
	for (unsigned int i = 0; i < vecCubeMap.size(); i++)
	{
		unsigned char* pImageData = stbi_load(vecCubeMap[i].c_str(), &iWidth, &iHeight, &iComponent, 0);
		if (pImageData)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, iWidth, iHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, pImageData);
		}
		else
		{
			std::cout << "Texture failed to load at path:" << vecCubeMap[i] << std::endl;
			stbi_image_free(pImageData);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	return uiID;
}
