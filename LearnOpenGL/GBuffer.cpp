#include "GBuffer.h"

GBuffer::GBuffer(unsigned int uiWidth, unsigned int uiHeight):
	m_uiWidth(uiWidth),m_uiHeight(uiHeight)
{
	glGenFramebuffers(1, &m_uiGBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, m_uiGBuffer);
	
	glGenTextures(1, &m_gPosition);
	glBindTexture(GL_TEXTURE_2D, m_gPosition);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, uiWidth, uiHeight, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_gPosition, 0);

	glGenTextures(1, &m_gNomal);
	glBindTexture(GL_TEXTURE_2D, m_gNomal);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, uiWidth, uiHeight, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, m_gNomal, 0);

	glGenTextures(1, &m_gAlbedoSpec);
	glBindTexture(GL_TEXTURE_2D, m_gAlbedoSpec);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, uiWidth, uiHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, m_gAlbedoSpec, 0);

	GLuint attachments[3] = { GL_COLOR_ATTACHMENT0,GL_COLOR_ATTACHMENT1,GL_COLOR_ATTACHMENT2 };
	glDrawBuffers(3, attachments);

	glGenRenderbuffers(1, &m_rboDepth);
	glBindRenderbuffer(GL_RENDERBUFFER, m_rboDepth);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, uiWidth, uiHeight);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_rboDepth);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "Framebuffer not complete!" << std::endl;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

GLuint GBuffer::GetGBuffer() const
{
	return m_uiGBuffer;
}

GLuint GBuffer::GetPosition() const
{
	return m_gPosition;
}

GLuint GBuffer::GetNormal() const
{
	return m_gNomal;
}

GLuint GBuffer::GetAlbedo() const
{
	return m_gAlbedoSpec;
}

GLuint GBuffer::GetDepth() const
{
	return m_rboDepth;
}

unsigned int GBuffer::GetWidth() const
{
	return m_uiWidth;
}

unsigned int GBuffer::GetHeight() const
{
	return m_uiHeight;
}
