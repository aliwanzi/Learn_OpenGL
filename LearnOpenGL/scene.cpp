#include "scene.h"
namespace
{
	float DeltaFrame(0.f);
	float LastFrame(0.f);
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
		if (spRenderState->GetUseBloom())
		{
			auto bloomKeyPressed = spRenderState->GetBloomPressed();
			if (glfwGetKey(pGLFWwindow, GLFW_KEY_Z) == GLFW_PRESS && !bloomKeyPressed)
			{
				auto bloom = spRenderState->GetBloom();
				spRenderState->SetBloom(!bloom);
				spRenderState->SetBloomPressed(true);
			}
			if (glfwGetKey(pGLFWwindow, GLFW_KEY_Z) == GLFW_RELEASE)
			{
				spRenderState->SetBloomPressed(false);
			}
		}
		if (spRenderState->GetUseGamma())
		{
			auto gammaKeyPressed = spRenderState->GetGammaPressed();
			if (glfwGetKey(pGLFWwindow, GLFW_KEY_C) == GLFW_PRESS && !gammaKeyPressed)
			{
				auto gamma = spRenderState->GetGamma();
				spRenderState->SetGamma(!gamma);
				spRenderState->SetGammaPressed(true);
			}
			if (glfwGetKey(pGLFWwindow, GLFW_KEY_C) == GLFW_RELEASE)
			{
				spRenderState->SetGammaPressed(false);
			}
		}
		if (spRenderState->GetUseExpusure())
		{
			auto exposure = spRenderState->GetExposure();
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
		if (spRenderState->GetUseHightScale())
		{
			auto heightScale = spRenderState->GetHightScale();
			if (glfwGetKey(pGLFWwindow, GLFW_KEY_Q) == GLFW_PRESS)
			{
				if (heightScale > 0.0f)
					heightScale -= 0.0005f;
				else
					heightScale = 0.0f;
			}
			else if (glfwGetKey(pGLFWwindow, GLFW_KEY_E) == GLFW_PRESS)
			{
				if (heightScale < 1.0f)
					heightScale += 0.0005f;
				else
					heightScale = 1.0f;
			}
			spRenderState->SetHightScale(heightScale);
		}

		if (spRenderState->GetUseBlinn())
		{
			auto blinnKeyPressed = spRenderState->GetBlinnPressed();
			if (glfwGetKey(pGLFWwindow, GLFW_KEY_X) == GLFW_PRESS && !blinnKeyPressed)
			{
				auto blinn = spRenderState->GetBlinn();
				spRenderState->SetBlinn(!blinn);
				spRenderState->SetBlinnPressed(true);
			}
			if (glfwGetKey(pGLFWwindow, GLFW_KEY_X) == GLFW_RELEASE)
			{
				spRenderState->SetBlinnPressed(false);
			}
		}
		if (spRenderState->GetUseShadow())
		{
			auto bShadowKeyPressed = spRenderState->GetShadowPressed();
			if (glfwGetKey(pGLFWwindow, GLFW_KEY_SPACE) == GLFW_PRESS && !bShadowKeyPressed)
			{
				auto bShadow = spRenderState->GetShadow();
				spRenderState->SetShadow(!bShadow);
				spRenderState->SetShadowPressed(true);
			}
			if (glfwGetKey(pGLFWwindow, GLFW_KEY_SPACE) == GLFW_RELEASE)
			{
				spRenderState->SetShadowPressed(false);
			}
		}
		if (spRenderState->GetUseSSAO())
		{
			auto bSSAOKeyPressed = spRenderState->GetSSAOPressed();
			if (glfwGetKey(pGLFWwindow, GLFW_KEY_SPACE) == GLFW_PRESS && !bSSAOKeyPressed)
			{
				auto bSSAO = spRenderState->GetSSAO();
				spRenderState->SetSSAO(!bSSAO);
				spRenderState->SetSSAOPressed(true);
			}
			if (glfwGetKey(pGLFWwindow, GLFW_KEY_SPACE) == GLFW_RELEASE)
			{
				spRenderState->SetSSAOPressed(false);
			}
		}
	}
}