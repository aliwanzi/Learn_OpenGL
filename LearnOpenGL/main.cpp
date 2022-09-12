#include "scene.h"
#include "gl_resource.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const std::string WINDOW_NAME = "LearnOpenGL";

int main()
{
	//≥ı ºªØglfw°¢glad
	auto spGLResource = std::make_shared<GLResource>();
	spGLResource->CreateGLFWWindow(SCR_WIDTH, SCR_HEIGHT, WINDOW_NAME);
	std::cout << "œ‘ø®–Õ∫≈£∫" << spGLResource->GetGPUVersion() << std::endl;

	auto spCamera = std::make_shared<Camera>(glm::vec3(0.f, 0.f, 3.f));
	auto spScene = std::make_shared<Scene>(spGLResource, spCamera);
	spScene->SetBackGround(glm::vec4(0.2f, 0.3f, 0.3f, 1.0f));

	auto spShader = std::make_shared<Shader>("../resources/shaders/model/vertex.vs", "../resources/shaders/model/fragment.fs");
	auto spTexture = std::make_shared<Texture>();
	auto spRenderState = std::make_shared<RenderState>(spShader, spTexture);
	spRenderState->SetDepthTest(true);
	spRenderState->SetDrawMode(DRAW_MODE::ELEMENT_MODE);
	spRenderState->SetPrimitiveMode(PRIMITIVE_MODE::TRIANGLES_MODE);

	auto spEntity = std::make_shared<Entity>();
	auto spLightingRenderPass = std::make_shared<RenderPass>(spEntity, spRenderState);
	spEntity->AddMeshNode("../resources/objects/backpack/backpack.obj", spRenderState);

	spScene->AddRenderPass(spLightingRenderPass);

	spScene->Draw();
}

