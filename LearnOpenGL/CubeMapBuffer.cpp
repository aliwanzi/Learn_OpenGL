#include "CubeMapBuffer.h"
namespace
{
	glm::mat4 matProjection = glm::perspective(glm::radians(90.f), 1.0f, 0.1f, 10.0f);
	std::vector<glm::mat4> matView
	{
		glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
		glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
		glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  1.0f,  0.0f), glm::vec3(0.0f,  0.0f,  1.0f)),
		glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f,  0.0f), glm::vec3(0.0f,  0.0f, -1.0f)),
		glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  0.0f,  1.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
		glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  0.0f, -1.0f), glm::vec3(0.0f, -1.0f,  0.0f))
	};
}

CubeMapBuffer::CubeMapBuffer(int width, int height, int oriWidth, int oriHeight):
	m_iWidth(width),m_iHeight(height),m_iOriWidth(oriWidth),m_iOriHeight(oriHeight),
	m_iFrameBuffer(0),m_iRenderBuffer(0),m_iTexture(0)
{
	glGenFramebuffers(1, &m_iFrameBuffer);
	glGenRenderbuffers(1, &m_iRenderBuffer);

	glBindFramebuffer(GL_FRAMEBUFFER, m_iFrameBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, m_iRenderBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_iRenderBuffer);

	glGenTextures(1, &m_iTexture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_iTexture);
	for (GLuint i = 0; i < 6; i++)
	{
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F,
			width, height, 0, GL_RGB, GL_FLOAT, nullptr);
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_iTexture, 0);

	assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete");

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void CubeMapBuffer::DrawCubeMap(std::shared_ptr<Node> spNode)
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_iFrameBuffer);

	glViewport(0, 0, m_iWidth, m_iHeight);

	auto spRenderState = spNode->GetRenderState();
	auto spShader = spRenderState->GetShader();

	spShader->Use();
	spShader->SetMat4("matProjection", matProjection);
	for (GLuint i = 0; i < 6; i++)
	{
		spShader->SetMat4("matView", matView[i]);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, m_iTexture, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		spNode->Draw();
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, m_iOriWidth, m_iOriHeight);
}

GLuint CubeMapBuffer::GetCubeMapTexture()
{
	return m_iTexture;
}