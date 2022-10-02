#pragma once
#include "common.h"

class UniformBuffer
{
public:
	UniformBuffer(int count, GLuint size, int iBlockBinding);
	GLuint GetUniformBuffer()const;
private:
	GLuint m_uiUniformBuffer;

};

