#pragma once
#include "common.h"

class GBuffer
{
public:
	GBuffer(unsigned int uiWidth, unsigned int uiHeight);
	GLuint GetGBuffer()const;
	GLuint GetPosition()const;
	GLuint GetNormal()const;
	GLuint GetAlbedo()const;
	GLuint GetDepth()const;
	unsigned int GetWidth()const;
	unsigned int GetHeight()const;
private:
	GLuint m_uiGBuffer;
	GLuint m_gPosition;
	GLuint m_gNomal;
	GLuint m_gAlbedoSpec;
	GLuint m_rboDepth;
	unsigned int m_uiWidth;
	unsigned int m_uiHeight;
};

