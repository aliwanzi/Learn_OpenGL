#pragma once
#include "common.h"

class DepthBuffer
{
public:
	DepthBuffer(int width,int height);
	void SetOriWidthAndHeight(int width, int height);
	void GetOriWidthAndHeight(int& width, int& height) const;
	GLuint GetDepthMap()const;
	void Bind();

private:
	int m_iWidth;
	int m_iHeight;
	int m_iOriWidth;
	int m_iOriHeight;
	GLuint m_uiFBO;
	GLuint m_uiDepthMap;
};

