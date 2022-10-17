#include "HDRBuffer.h"

HDRBuffer::HDRBuffer(unsigned int uiWidth, unsigned int uiHeight)
    :m_uiWidth(uiWidth),m_uiHeight(uiHeight)
{
    glGenFramebuffers(1, &m_uiHDRBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, m_uiHDRBuffer);

    glGenTextures(2, m_uiColorBuffers);
    for (unsigned int i = 0; i < 2; i++)
    {
        glBindTexture(GL_TEXTURE_2D, m_uiColorBuffers[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, uiWidth, uiHeight, 0, GL_RGBA, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, m_uiColorBuffers[i], 0);
    }

    glGenRenderbuffers(1, &m_uiDepth);
    glBindRenderbuffer(GL_RENDERBUFFER, m_uiDepth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, uiWidth, uiHeight);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_uiDepth);

    unsigned int attachments[2] = { GL_COLOR_ATTACHMENT0,GL_COLOR_ATTACHMENT1 };
    glDrawBuffers(2, attachments);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER)!=GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "Framebuffer not complete!" << std::endl;
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

GLuint HDRBuffer::GetHDRBuffer() const
{
    return m_uiHDRBuffer;
}

GLuint HDRBuffer::GetRendering() const
{
    return m_uiColorBuffers[0];
}

GLuint HDRBuffer::GetBrightness() const
{
    return m_uiColorBuffers[1];
}

GLuint HDRBuffer::GetDepth() const
{
    return m_uiDepth;
}

unsigned int HDRBuffer::GetWidth() const
{
    return m_uiWidth;
}

unsigned int HDRBuffer::GetHeight() const
{
    return m_uiHeight;
}
