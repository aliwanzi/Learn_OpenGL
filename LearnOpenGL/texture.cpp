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

void Texture::AddTexture(std::shared_ptr<TextureStruct> spTexture)
{
	m_mapTextures[spTexture->uiID] = spTexture;
}

GLuint Texture::AddTexture(const std::string& sPath, TextureType eType, bool bflip /*= false*/, bool gamma /*= false*/)
{
	auto spTexture = std::make_shared<TextureStruct>();
	spTexture->sPath = sPath;
	spTexture->uiID = TextureFromFile(sPath, bflip, gamma);
	spTexture->eType = eType;
	m_mapTextures[spTexture->uiID] = spTexture;
	return spTexture->uiID;
}

GLuint Texture::AddTexture(std::vector<std::string>& vecCubeMap)
{
	auto spTexture = std::make_shared<TextureStruct>();
	spTexture->sPath = "";
	spTexture->uiID = TextureFromCube(vecCubeMap);
	spTexture->eType = TextureType::CUBEMAP;
	m_mapTextures[spTexture->uiID] = spTexture;
	return spTexture->uiID;
}

const std::map<GLuint, std::shared_ptr<TextureStruct>>& Texture::GetTexures()const
{
	return m_mapTextures;
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
		GLenum internalFormat(GL_RED);
		GLenum dataFormat(GL_RED);
		switch (iComponent)
		{
		case 1:
		{
			dataFormat = GL_RED;
			internalFormat = GL_RED;
			break;
		}
		case 3:
		{
			dataFormat = GL_RGB;
			internalFormat = gamma ? GL_SRGB : GL_RGB;
			break;
		}
		case 4:
		{
			dataFormat = GL_RGBA;
			internalFormat = gamma ? GL_SRGB_ALPHA : GL_RGBA;
			break;
		}
		default:
			break;
		}

		glBindTexture(GL_TEXTURE_2D, uiID);
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, iWidth, iHeight, 0, dataFormat, GL_UNSIGNED_BYTE, pImageData);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, dataFormat == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, dataFormat == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
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

		if (pImageData)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, eFormat, iWidth, iHeight, 0, eFormat, GL_UNSIGNED_BYTE, pImageData);
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
