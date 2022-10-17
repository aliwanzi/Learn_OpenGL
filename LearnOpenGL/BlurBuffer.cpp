#include "BlurBuffer.h"

BlurBuffer::BlurBuffer(unsigned int uiWidth, unsigned int uiHeight):
    m_uiWidth(uiWidth),m_uiHeight(uiHeight)
{
    glGenFramebuffers(2, m_uiBlurBuffer);
    glGenTextures(2, m_uiColorTexture);
    for (int i = 0; i < 2; i++)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_uiBlurBuffer[i]);
        glBindTexture(GL_TEXTURE_2D, m_uiColorTexture[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, uiWidth, uiHeight, 0, GL_RGBA, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_uiColorTexture[i], 0);
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        {
            std::cout << "Framebuffer not complete!" << std::endl;
        }
    }
}

const GLuint* BlurBuffer::GetBlurBuffer()const
{
    return m_uiBlurBuffer;
}

const GLuint* BlurBuffer::GetRendering()const
{
    return m_uiColorTexture;
}

unsigned int BlurBuffer::GetWidth() const
{
    return m_uiWidth;
}

unsigned int BlurBuffer::GetHeight() const
{
    return m_uiHeight;
}
