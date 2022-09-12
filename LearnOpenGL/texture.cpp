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

void Texture::AddTexture(const char* pcPath, TextureType eType, bool bflip /*= false*/, bool gamma /*= false*/)
{
	TextureStruct texture;
	texture.sPath = std::string(pcPath);
	texture.uiID = TextureFromFile(pcPath,bflip, gamma);
	texture.eType = eType;
	m_vecTextures.push_back(texture);
}

const std::vector<TextureStruct>& Texture::GetTexures()const
{
	return m_vecTextures;
}

unsigned int Texture::TextureFromFile(const char* pcPath, bool bflip, bool gamma)
{
	unsigned int uiID;
	glGenTextures(1, &uiID);

	int iWidth(0), iHeight(0), iComponent(0);
	stbi_set_flip_vertically_on_load(bflip);
	unsigned char* pImageData = stbi_load(pcPath, &iWidth, &iHeight, &iComponent, 0);
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

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(pImageData);
	}
	else
	{
		std::cout << "Texture failed to load at path:" << pcPath << std::endl;
		stbi_image_free(pImageData);
	}

	return uiID;
}