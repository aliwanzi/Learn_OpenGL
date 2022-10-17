#pragma once
#include "common.h"

class HDRBuffer
{
public:
	HDRBuffer(unsigned int uiWidth, unsigned int uiHeight);
	GLuint GetHDRBuffer()const;
	GLuint GetRendering()const;
	GLuint GetBrightness()const;
	GLuint GetDepth()const;
	unsigned int GetWidth()const;
	unsigned int GetHeight()const;
private:
	GLuint m_uiHDRBuffer;
	GLuint m_uiColorBuffers[2];
	GLuint m_uiDepth;
	unsigned int m_uiWidth;
	unsigned int m_uiHeight;
};

