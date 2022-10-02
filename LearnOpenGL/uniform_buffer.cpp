#include "uniform_buffer.h"

UniformBuffer::UniformBuffer(int count, GLuint size, int iBlockBinding)
{
	glGenBuffers(1, &m_uiUniformBuffer);

	glBindBuffer(GL_UNIFORM_BUFFER, m_uiUniformBuffer);
	glBufferData(GL_UNIFORM_BUFFER, count * size, NULL, GL_STATIC_DRAW);
	glBindBufferRange(GL_UNIFORM_BUFFER, iBlockBinding, m_uiUniformBuffer, 0, count * size);

	glBindBuffer(GL_UNIFORM_BUFFER, 0);


}

GLuint UniformBuffer::GetUniformBuffer() const
{
	return m_uiUniformBuffer;
}
