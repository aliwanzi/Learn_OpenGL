#include "ssao.h"

SSAOBuffer::SSAOBuffer(unsigned int uiWidth, unsigned int uiHeight)
{
	glGenFramebuffers(1, &m_uiSsaoBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, m_uiSsaoBuffer);
	glGenTextures(1, &m_uiSsaoColor);
	glBindTexture(GL_TEXTURE_2D, m_uiSsaoColor);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, uiWidth, uiHeight, 0, GL_RED, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_uiSsaoColor, 0);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "SSAO Framebuffer not complete!" << std::endl;
	}
}

GLuint SSAOBuffer::GetSsaoBuffer() const
{
	return m_uiSsaoBuffer;
}

GLuint SSAOBuffer::GetSsaoColor() const
{
	return m_uiSsaoColor;
}
