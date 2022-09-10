#pragma once
#include "gl_resource.h"
#include "render_pass.h"
#include "camera.h"

class Scene
{
public:
	Scene(std::shared_ptr<GLResource> spGLResource, std::shared_ptr<Camera> spCamera);
	~Scene();
	void AddRenderPass(std::shared_ptr<RenderPass> spRenerPass);

	void SetBackGround(const glm::vec4& vec4BackGround);
	void Draw();

private:
	void ProcessInput();
	void ProcessMatrix();

private:
	glm::vec4 m_vec4BackGround;
	std::vector<std::shared_ptr<RenderPass>> m_vecRenderPass;
	std::shared_ptr<GLResource> m_spGLResource;
	std::shared_ptr<Camera> m_spCamera;
};