#pragma once
#include "common.h"

class BlurBuffer
{
public:
	BlurBuffer(unsigned int uiWidth, unsigned int uiHeight);
	const GLuint* GetBlurBuffer() const;
	const GLuint* GetRendering()const;
	unsigned int GetWidth()const;
	unsigned int GetHeight()const;
private:
	GLuint m_uiBlurBuffer[2];
	GLuint m_uiColorTexture[2];
	unsigned int m_uiWidth;
	unsigned int m_uiHeight;
};

