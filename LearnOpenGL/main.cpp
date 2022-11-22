#include "scene.h"
#include "gl_resource.h"
#include "CubeMapBuffer.h"
#include <random>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const std::string WINDOW_NAME = "LearnOpenGL";

std::vector<Vertex> vecVertex
{
	Vertex(glm::vec3(-1.0, -1.0, -1.0),glm::vec2(0.0, 0.0),glm::vec3(0.0f,  0.0f, -1.0f)),
	Vertex(glm::vec3(1.0,  1.0, -1.0),glm::vec2(1.0, 1.0),glm::vec3(0.0f,  0.0f, -1.0f)),
	Vertex(glm::vec3(1.0, -1.0, -1.0),glm::vec2(1.0, 0.0),glm::vec3(0.0f,  0.0f, -1.0f)),
	Vertex(glm::vec3(1.0,  1.0, -1.0),glm::vec2(1.0, 1.0),glm::vec3(0.0f,  0.0f, -1.0f)),
	Vertex(glm::vec3(-1.0, -1.0, -1.0),glm::vec2(0.0, 0.0),glm::vec3(0.0f,  0.0f, -1.0f)),
	Vertex(glm::vec3(-1.0,  1.0, -1.0),glm::vec2(0.0, 1.0),glm::vec3(0.0f,  0.0f, -1.0f)),

	Vertex(glm::vec3(-1.0, -1.0,  1.0),glm::vec2(0.0, 0.0),glm::vec3(0.0f,  0.0f,  1.0f)),//4
	Vertex(glm::vec3(1.0, -1.0,  1.0),glm::vec2(1.0, 0.0),glm::vec3(0.0f,  0.0f,  1.0f)),//5
	Vertex(glm::vec3(1.0,  1.0,  1.0),glm::vec2(1.0, 1.0),glm::vec3(0.0f,  0.0f,  1.0f)),//6
	Vertex(glm::vec3(1.0,  1.0,  1.0),glm::vec2(1.0, 1.0),glm::vec3(0.0f,  0.0f,  1.0f)),//7
	Vertex(glm::vec3(-1.0,  1.0,  1.0),glm::vec2(0.0, 1.0),glm::vec3(0.0f,  0.0f,  1.0f)),//6
	Vertex(glm::vec3(-1.0, -1.0,  1.0),glm::vec2(0.0, 0.0),glm::vec3(0.0f,  0.0f,  1.0f)),//7

	Vertex(glm::vec3(-1.0,  1.0,  1.0),glm::vec2(1.0, 0.0),glm::vec3(-1.0f,  0.0f,  0.0f)),
	Vertex(glm::vec3(-1.0,  1.0, -1.0),glm::vec2(1.0, 1.0),glm::vec3(-1.0f,  0.0f,  0.0f)),
	Vertex(glm::vec3(-1.0, -1.0, -1.0),glm::vec2(0.0, 1.0),glm::vec3(-1.0f,  0.0f,  0.0f)),
	Vertex(glm::vec3(-1.0, -1.0, -1.0),glm::vec2(0.0, 1.0),glm::vec3(-1.0f,  0.0f,  0.0f)),
	Vertex(glm::vec3(-1.0, -1.0,  1.0),glm::vec2(0.0, 0.0),glm::vec3(-1.0f,  0.0f,  0.0f)),
	Vertex(glm::vec3(-1.0,  1.0,  1.0),glm::vec2(1.0, 0.0),glm::vec3(-1.0f,  0.0f,  0.0f)),

	Vertex(glm::vec3(1.0,  1.0,  1.0),glm::vec2(1.0, 0.0),glm::vec3(1.0f,  0.0f,  0.0f)),
	Vertex(glm::vec3(1.0, -1.0, -1.0),glm::vec2(0.0, 1.0),glm::vec3(1.0f,  0.0f,  0.0f)),
	Vertex(glm::vec3(1.0,  1.0, -1.0),glm::vec2(1.0, 1.0),glm::vec3(1.0f,  0.0f,  0.0f)),
	Vertex(glm::vec3(1.0, -1.0, -1.0),glm::vec2(0.0, 1.0),glm::vec3(1.0f,  0.0f,  0.0f)),
	Vertex(glm::vec3(1.0,  1.0,  1.0),glm::vec2(1.0, 0.0),glm::vec3(1.0f,  0.0f,  0.0f)),
	Vertex(glm::vec3(1.0, -1.0,  1.0),glm::vec2(0.0, 0.0),glm::vec3(1.0f,  0.0f,  0.0f)),

	Vertex(glm::vec3(-1.0, -1.0, -1.0),glm::vec2(0.0,  1.0),glm::vec3(0.0f, -1.0f,  0.0f)),
	Vertex(glm::vec3(1.0, -1.0, -1.0),glm::vec2(1.0,  1.0),glm::vec3(0.0f, -1.0f,  0.0f)),
	Vertex(glm::vec3(1.0, -1.0,  1.0),glm::vec2(1.0,  0.0),glm::vec3(0.0f, -1.0f,  0.0f)),
	Vertex(glm::vec3(1.0, -1.0,  1.0),glm::vec2(1.0,  0.0),glm::vec3(0.0f, -1.0f,  0.0f)),
	Vertex(glm::vec3(-1.0, -1.0,  1.0),glm::vec2(0.0,  0.0),glm::vec3(0.0f, -1.0f,  0.0f)),
	Vertex(glm::vec3(-1.0, -1.0, -1.0),glm::vec2(0.0,  1.0),glm::vec3(0.0f, -1.0f,  0.0f)),

	Vertex(glm::vec3(-1.0,  1.0, -1.0),glm::vec2(0.0,  1.0),glm::vec3(0.0f,  1.0f,  0.0f)),
	Vertex(glm::vec3(1.0,  1.0,  1.0),glm::vec2(1.0,  0.0),glm::vec3(0.0f,  1.0f,  0.0f)),
	Vertex(glm::vec3(1.0,  1.0, -1.0),glm::vec2(1.0,  1.0),glm::vec3(0.0f,  1.0f,  0.0f)),
	Vertex(glm::vec3(1.0,  1.0,  1.0),glm::vec2(1.0,  0.0),glm::vec3(0.0f,  1.0f,  0.0f)),
	Vertex(glm::vec3(-1.0,  1.0, -1.0),glm::vec2(0.0,  1.0),glm::vec3(0.0f,  1.0f,  0.0f)),
	Vertex(glm::vec3(-1.0,  1.0,  1.0),glm::vec2(0.0,  0.0),glm::vec3(0.0f,  1.0f,  0.0f))
};

std::vector<unsigned int> vecIndex
{
	0,1,2,3,4,5, 6,7,8,9,10,11, 12,13,14,15,16,17, 18,19,20,21,22,23, 24,25,26,27,28,29, 30,31,32,33,34,35
};

std::shared_ptr<GeometryNode> CreatBoxNode(std::shared_ptr<RenderState> spRenderState)
{
	auto spTransform = std::make_shared<Transform>();
	spTransform->SetModelPan(glm::vec3(0.f));
	return std::make_shared<GeometryNode>(vecVertex, vecIndex, spRenderState, spTransform);
}

#define CASE1

int main()
{
	//≥ı ºªØglfw°¢glad
	auto spGLResource = std::make_shared<GLResource>();
	spGLResource->CreateGLFWWindow(SCR_WIDTH, SCR_HEIGHT, WINDOW_NAME);
	std::cout << "œ‘ø®–Õ∫≈£∫" << spGLResource->GetGPUVersion() << std::endl;

	auto spCamera = std::make_shared<Camera>(glm::vec3(0.f, 0.f, 5.f));
	auto spScene = std::make_shared<Scene>(spGLResource, spCamera);
	
#ifdef CASE1
	//DrawBuffer
	auto spCubeMapShader = std::make_shared<Shader>("../resources/shaders/IBL/cubemap.vs",
		"../resources/shaders/IBL/cubemap.fs");

	auto spCubeMapTexture = std::make_shared<Texture>();
	spCubeMapTexture->AddTexture("../resources/textures/newport_loft.hdr", TextureType::DIFFUSE, true, false, true);

	auto spCubeMapRenderState = std::make_shared<RenderState>(spCubeMapShader, spCubeMapTexture);
	spCubeMapRenderState->SetBackGround(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	spCubeMapRenderState->EnableDepthTest(true);
	spCubeMapRenderState->SetDrawMode(DRAW_MODE::ELEMENT_MODE);
	spCubeMapRenderState->SetPrimitiveMode(PRIMITIVE_MODE::TRIANGLES_MODE);

	auto spCubeMapNode = CreatBoxNode(spCubeMapRenderState);
	auto spCubeMapBuffer = std::make_shared<CubeMapBuffer>(512, 512, SCR_WIDTH, SCR_HEIGHT);
	spCubeMapBuffer->DrawCubeMap(spCubeMapNode);

	//DrawCubeMapInScene
	auto spCubeMapEntity = std::make_shared<Entity>();
	spCubeMapEntity->AddGeometryNode(CreatBoxNode(spCubeMapRenderState));
	auto spCubeMapRenderPass = std::make_shared<RenderPass>(spCubeMapEntity, spCubeMapRenderState);
	//spScene->AddRenderPass(spCubeMapRenderPass);

	//Draw Environment
	auto spEnvShader = std::make_shared<Shader>("../resources/shaders/IBL/background.vs",
		"../resources/shaders/IBL/background.fs");

	auto spEnvTexture = std::make_shared<Texture>();
	auto spEnvTexStr = std::make_shared<TextureStruct>();
	spEnvTexStr->eType = TextureType::CUBEMAP;
	spEnvTexStr->uiID = spCubeMapBuffer->GetCubeMapTexture();
	spEnvTexture->AddTexture(spEnvTexStr);

	auto spEnvRenderState = std::make_shared<RenderState>(spEnvShader, spEnvTexture);
	spEnvRenderState->SetBackGround(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
	spEnvRenderState->EnableDepthTest(true);
	spEnvRenderState->SetDepthFunc(GL_LEQUAL);
	spEnvRenderState->SetDrawMode(DRAW_MODE::ELEMENT_MODE);
	spEnvRenderState->SetPrimitiveMode(PRIMITIVE_MODE::TRIANGLES_MODE);

	auto spEnvEntity = std::make_shared<Entity>();
	spEnvEntity->AddGeometryNode(CreatBoxNode(spEnvRenderState));
	auto spEnvRenderPass = std::make_shared<RenderPass>(spEnvEntity, spEnvRenderState);
	spScene->AddRenderPass(spEnvRenderPass);

	spScene->Draw();
#endif // !CASE1
}