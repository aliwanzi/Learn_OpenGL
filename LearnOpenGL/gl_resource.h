#pragma once
#include "common.h"
#include "camera.h"

class GLResource
{
public:
	GLResource();
	~GLResource();
	bool CreateGLFWWindow(unsigned int uiWidth, unsigned int uiHeight, const std::string& sWindowName);
	GLFWwindow* GetGLFWWindow() const;
	void ResizeWindow(unsigned int uiWidth, unsigned int uiHeight);
	std::string GetGPUVersion() const;
	void SetCamera(std::shared_ptr<Camera>& spCamera);

private:
	GLFWwindow* m_pGLFWwindow;
};