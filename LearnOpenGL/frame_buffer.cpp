#include "frame_buffer.h"

FrameBuffer::FrameBuffer():
	m_uiFrameBuffer(0),
	m_uiColorAttachment(0),
	m_uiDepthStencilAttachment(0)
{

}

void FrameBuffer::CreateFrameBuffer(unsigned int uiWidth, unsigned int uiHeight)
{
	glGenFramebuffers(1, &m_uiFrameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, m_uiFrameBuffer);

	glGenTextures(1, &m_uiColorAttachment);
	glBindTexture(GL_TEXTURE_2D, m_uiColorAttachment);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, uiWidth, uiHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_uiColorAttachment, 0);

	//glGenTextures(1, &m_uiDepthStencilAttachment);
	//glBindTexture(GL_TEXTURE_2D, m_uiDepthStencilAttachment);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, m_spFrameBufferInfo->Width, m_spFrameBufferInfo->Height, 0,
	//	GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
	//glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_uiDepthStencilAttachment, 0);

	glGenRenderbuffers(1, &m_uiFrameBufferObject);
	glBindRenderbuffer(GL_RENDERBUFFER, m_uiFrameBufferObject);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, uiWidth, uiHeight);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_uiFrameBufferObject);

	assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete");

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void FrameBuffer::CreateMultiSampleFrameBuffer(unsigned int uiWidth, unsigned int uiHeight, unsigned int uiSamples)
{
	glGenFramebuffers(1, &m_uiFrameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, m_uiFrameBuffer);
	// create a multisampled color attachment texture

	glGenTextures(1, &m_uiColorAttachment);
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, m_uiColorAttachment);
	glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_RGB, uiWidth, uiHeight, GL_TRUE);
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, m_uiColorAttachment, 0);
	// create a (also multisampled) renderbuffer object for depth and stencil attachments

	glGenRenderbuffers(1, &m_uiFrameBufferObject);
	glBindRenderbuffer(GL_RENDERBUFFER, m_uiFrameBufferObject);
	glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_DEPTH24_STENCIL8, uiWidth, uiHeight);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_uiFrameBufferObject);

	assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete");

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

GLuint FrameBuffer::GetFrameBuffer() const
{
	return m_uiFrameBuffer;
}

GLuint FrameBuffer::GetColorAttachment() const
{
	return m_uiColorAttachment;
}