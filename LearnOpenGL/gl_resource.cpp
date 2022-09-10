#include "gl_resource.h"

namespace
{
	std::shared_ptr<Camera> camera;
	float LastX(0.f), LastY(0.f);
	bool bFirstMouse(true);
	int iHeight(0), iWidth(0);
	void MouseInput(GLFWwindow* pGLFWwindow, double dXPosIn, double dYPosIn)
	{
		float fXPos = static_cast<float>(dXPosIn);
		float fYPos = static_cast<float>(dYPosIn);
		if (bFirstMouse)
		{
			LastX = fXPos;
			LastY = fYPos;
			bFirstMouse = false;
		}
		float fXOffset = fXPos - LastX;
		float fYOffset = LastY - fYPos;

		LastX = fXPos;
		LastY = fYPos;

		camera->ProcessMouseMovement(fXOffset, fYOffset);
	}

	void ScrollInput(GLFWwindow* pGLFWwindow, double dXOffset, double dYOffset)
	{
		camera->ProcessMouseScroll(static_cast<float>(dYOffset));
	}

	void FramebufferSizeCallBack(GLFWwindow* glfwWIndow, int width, int height)
	{
		glViewport(0, 0, width, height);
		camera->SetFOV(width, height);
	}
}

GLResource::GLResource():m_pGLFWwindow(nullptr)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

GLResource::~GLResource()
{
	m_pGLFWwindow = nullptr;
}

bool GLResource::CreateGLFWWindow(unsigned int uiWidth, unsigned int uiHeight, const std::string& sWindowName)
{
	iWidth = uiWidth;
	iHeight = uiHeight;

	m_pGLFWwindow = glfwCreateWindow(uiWidth, uiHeight, sWindowName.c_str(), NULL, NULL);
	if (m_pGLFWwindow == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(m_pGLFWwindow);
	glfwSetFramebufferSizeCallback(m_pGLFWwindow, FramebufferSizeCallBack);
	glfwSetCursorPosCallback(m_pGLFWwindow, MouseInput);
	glfwSetScrollCallback(m_pGLFWwindow, ScrollInput);

	glfwSetInputMode(m_pGLFWwindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}
	return true;
}

GLFWwindow* GLResource::GetGLFWWindow() const
{
	return m_pGLFWwindow;
}

void GLResource::ResizeWindow(unsigned int uiWidth, unsigned int uiHeight)
{
	FramebufferSizeCallBack(m_pGLFWwindow, uiWidth, uiHeight);
}

std::string GLResource::GetGPUVersion() const
{
	return (const char*)glGetString(GL_RENDERER);
}

void GLResource::SetCamera(std::shared_ptr<Camera>& spCamera)
{
	camera = spCamera;
	camera->SetFOV(iWidth, iHeight);
}