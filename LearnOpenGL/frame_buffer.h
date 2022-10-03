#pragma once
#include "common.h"

class FrameBuffer
{
public:
	FrameBuffer();
	void CreateFrameBuffer(unsigned int uiWidth, unsigned int uiHeight);
	void CreateMultiSampleFrameBuffer(unsigned int uiWidth, unsigned int uiHeight, unsigned int uiSamples);
	GLuint GetFrameBuffer()const;
	GLuint GetColorAttachment() const;

private:
	GLuint m_uiFrameBuffer;
	GLuint m_uiColorAttachment;
	GLuint m_uiDepthStencilAttachment;
	GLuint m_uiFrameBufferObject;
};

