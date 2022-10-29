#include "DepthBuffer.h"

DepthBuffer::DepthBuffer(int width, int height,bool bCube):
	m_iWidth(width),m_iHeight(height),m_iOriWidth(0),m_iOriHeight(0)
{
	glGenFramebuffers(1, &m_uiFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, m_uiFBO);
	glGenTextures(1, &m_uiDepthMap);
	if (bCube)
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_uiDepthMap);
		for (GLuint i = 0; i < 6; i++)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, 
				m_iWidth, m_iHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_uiDepthMap, 0);
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, m_uiDepthMap);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, m_iWidth, m_iHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_uiDepthMap, 0);
	}

	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void DepthBuffer::SetOriWidthAndHeight(int width, int height)
{
	m_iOriWidth = width;
	m_iOriHeight = height;
}

void DepthBuffer::GetOriWidthAndHeight(int& width, int& height)const
{
	width = m_iOriWidth;
	height = m_iOriHeight;
}

GLuint DepthBuffer::GetDepthMap() const
{
	return m_uiDepthMap;
}

void DepthBuffer::Bind()
{
	glViewport(0, 0, m_iWidth, m_iHeight);
	glBindFramebuffer(GL_FRAMEBUFFER, m_uiFBO);
}


