#pragma once
#include "common.h"

struct FrameBufferInfo
{
	unsigned int Width;
	unsigned int Height;
};

class FrameBuffer
{
public:
	FrameBuffer(std::shared_ptr<FrameBufferInfo> spFrameBufferInfo);
	GLuint GetFrameBuffer()const;
	GLuint GetColorAttachment() const;

private:
	GLuint m_uiFrameBuffer;
	GLuint m_uiColorAttachment;
	GLuint m_uiDepthStencilAttachment;
	GLuint m_uiFrameBufferObject;
	std::shared_ptr<FrameBufferInfo> m_spFrameBufferInfo;
};

