#pragma once
#include "common.h"
#include "node.h"

class LutBuffer
{
public:
	LutBuffer(unsigned int uiWidth, unsigned int uiHeight, int oriWidth, int oriHeight);
	void DrawLutTexture(std::shared_ptr<Node> spNode);
	GLuint GetLutTexture() const;
private:
	int m_iWidth;
	int m_iHeight;
	int m_iOriWidth;
	int m_iOriHeight;
	GLuint m_uiFrameBuffer;
	GLuint m_uiRenderBuffer;
	GLuint m_uiLutTexture;
};

