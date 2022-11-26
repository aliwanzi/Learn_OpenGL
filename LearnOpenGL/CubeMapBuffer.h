#pragma once
#include "common.h"
#include "node.h"
#include <memory>

class CubeMapBuffer
{
public:
	CubeMapBuffer(int width, int height, int oriWidth, int oriHeight, bool bMipMap = false);
	void DrawCubeMap(std::shared_ptr<Node> spNode);
	GLuint GetCubeMapTexture();

private:
	int m_iWidth;
	int m_iHeight;
	int m_iOriWidth;
	int m_iOriHeight;
	GLuint m_iFrameBuffer;
	GLuint m_iRenderBuffer;
	GLuint m_iTexture;
};

