#include "scene.h"
namespace
{
	float DeltaFrame(0.f);
	float LastFrame(0.f);
	float exposure(1.f);
	bool bloomKeyPressed(false);
	bool gammaKeyPressed(false);
	bool blinnKeyPressed(false);
}

Scene::Scene(std::shared_ptr<GLResource> spGLResource,std::shared_ptr<Camera> spCamera)
	:m_spGLResource(spGLResource),m_spCamera(spCamera)
{
	spGLResource->SetCamera(spCamera);
}

void Scene::AddRenderPass(std::shared_ptr<RenderPass> spRenerPass)
{
	m_vecRenderPass.push_back(spRenerPass);
}

Scene::~Scene()
{

}

void Scene::Draw()
{
	auto pGLFWwindow = m_spGLResource->GetGLFWWindow();

	while (!glfwWindowShouldClose(pGLFWwindow))
	{
		ProcessInput();
		ProcessMatrix();
		for (auto& iter : m_vecRenderPass)
		{
			(*iter).Apply(m_spCamera);
		}
		glfwSwapBuffers(pGLFWwindow);
		glfwPollEvents();
	}
	glfwTerminate();
}

void Scene::ProcessMatrix()
{
	if (m_spCamera->GetViewUseTime())
	{
		float fRadius = 10.0f;
		float camX = static_cast<float>(sin(glfwGetTime()) * fRadius);
		float camZ = static_cast<float>(cos(glfwGetTime()) * fRadius);
		m_spCamera->SetEye(glm::vec3(camX, 0, camZ));
	}
}

void Scene::ProcessInput()
{
	float fCurrentFrame = glfwGetTime();
	DeltaFrame = fCurrentFrame - LastFrame;
	LastFrame = fCurrentFrame;

	auto pGLFWwindow = m_spGLResource->GetGLFWWindow();

	if (glfwGetKey(pGLFWwindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(pGLFWwindow, true);
	if (glfwGetKey(pGLFWwindow, GLFW_KEY_W) == GLFW_PRESS)
		m_spCamera->ProcessKeyboard(Movement::FORWARD, DeltaFrame);
	if (glfwGetKey(pGLFWwindow, GLFW_KEY_S) == GLFW_PRESS)
		m_spCamera->ProcessKeyboard(Movement::BACKWARD, DeltaFrame);
	if (glfwGetKey(pGLFWwindow, GLFW_KEY_A) == GLFW_PRESS)
		m_spCamera->ProcessKeyboard(Movement::LEFT, DeltaFrame);
	if (glfwGetKey(pGLFWwindow, GLFW_KEY_D) == GLFW_PRESS)
		m_spCamera->ProcessKeyboard(Movement::RIGHT, DeltaFrame);

	for (auto& iter : m_vecRenderPass)
	{
		auto spRenderState = iter->GetRenderState();
		if (spRenderState->GetExpusure())
		{
			if (glfwGetKey(pGLFWwindow, GLFW_KEY_Z) == GLFW_PRESS && !bloomKeyPressed)
			{
  				auto bloom = spRenderState->GetBloom();
				spRenderState->EnableBloom(!bloom);
				bloomKeyPressed = true;
			}
			if (glfwGetKey(pGLFWwindow, GLFW_KEY_Z) == GLFW_RELEASE)
			{
 				bloomKeyPressed = false;
			}

			if (glfwGetKey(pGLFWwindow, GLFW_KEY_C) == GLFW_PRESS && !gammaKeyPressed)
			{
				auto gamma = spRenderState->GetGamma();
				spRenderState->EnableGamma(!gamma);
				gammaKeyPressed = true;
			}
			if (glfwGetKey(pGLFWwindow, GLFW_KEY_C) == GLFW_RELEASE)
			{
				gammaKeyPressed = false;
			}

			if (glfwGetKey(pGLFWwindow, GLFW_KEY_Q) == GLFW_PRESS)
			{
				if (exposure > 0.0f)
					exposure -= 0.01f;
				else
					exposure = 0.0f;
			}
			else if (glfwGetKey(pGLFWwindow, GLFW_KEY_E) == GLFW_PRESS)
			{
				exposure += 0.01f;
			}
			spRenderState->SetExposure(exposure);
		}
		if (spRenderState->GetUseBlinn())
		{
			if (glfwGetKey(pGLFWwindow, GLFW_KEY_X) == GLFW_PRESS && !blinnKeyPressed)
			{
				auto blinn = spRenderState->GetBlinn();
				spRenderState->SetBlinn(!blinn);
				blinnKeyPressed = true;
			}
			if (glfwGetKey(pGLFWwindow, GLFW_KEY_X) == GLFW_RELEASE)
			{
				blinnKeyPressed = false;
			}
		}
	}
}