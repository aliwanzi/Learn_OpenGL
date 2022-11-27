#include "lut_buffer.h"
namespace
{
	glm::mat4 matProjection = glm::perspective(glm::radians(45.f), 1280.f/720.f, 0.1f, 10.0f);
}

LutBuffer::LutBuffer(unsigned int uiWidth, unsigned int uiHeight, int oriWidth, int oriHeight):
	m_iWidth(uiWidth), m_iHeight(uiHeight), m_iOriWidth(oriWidth), m_iOriHeight(oriHeight)
{
	glGenFramebuffers(1, &m_uiFrameBuffer);
	glGenTextures(1, &m_uiLutTexture);
	glGenRenderbuffers(1, &m_uiRenderBuffer);

	glBindFramebuffer(GL_FRAMEBUFFER, m_uiFrameBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, m_uiRenderBuffer);
	glBindTexture(GL_TEXTURE_2D, m_uiLutTexture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RG16F, uiWidth, uiHeight, 0, GL_RG, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, uiWidth, uiHeight);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_uiLutTexture, 0);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "Framebuffer not complete!" << std::endl;
	}
	unsigned int attachments[1] = { GL_COLOR_ATTACHMENT0};
	glDrawBuffers(1, attachments);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void LutBuffer::DrawLutTexture(std::shared_ptr<Node> spNode)
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_uiFrameBuffer);

	glViewport(0, 0, m_iWidth, m_iHeight);

	auto spRenderState = spNode->GetRenderState();
	auto spShader = spRenderState->GetShader();

	spShader->Use();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	spNode->Draw();

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, m_iOriWidth, m_iOriHeight);
}

GLuint LutBuffer::GetLutTexture() const
{
	return m_uiLutTexture;
}
