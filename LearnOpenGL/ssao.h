#pragma once
#include "common.h"

class SSAOBuffer
{
public:
	SSAOBuffer(unsigned int uiWidth, unsigned int uiHeight);
	GLuint GetSsaoBuffer()const;
	GLuint GetSsaoColor()const;
private:
	GLuint m_uiSsaoBuffer;
	GLuint m_uiSsaoColor;
};

