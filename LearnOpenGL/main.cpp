#include "scene.h"
#include "gl_resource.h"
#include <map>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const std::string WINDOW_NAME = "LearnOpenGL";

std::shared_ptr<Node> CreatCubeNode(std::shared_ptr<RenderState> spRenderState)
{
	std::vector<Vertex> vecVertex
	{
		Vertex(glm::vec3(-1.0, 1.0, -1.0)),//0
		Vertex(glm::vec3(-1.0, -1.0, -1.0)),//1
		Vertex(glm::vec3(1.0,  -1.0, -1.0)),//2
		Vertex(glm::vec3(1.0,  1.0, -1.0)),//3

		Vertex(glm::vec3(-1.0, -1.0, 1.0)),//4
		Vertex(glm::vec3(-1.0, -1.0, -1.0)),//5
		Vertex(glm::vec3(-1.0,  1.0, -1.0)),//6
		Vertex(glm::vec3(-1.0,  1.0, 1.0)),//7

		Vertex(glm::vec3(1.0,  -1.0,  -1.0)),
		Vertex(glm::vec3(1.0,  -1.0, 1.0)),
		Vertex(glm::vec3(1.0, 1.0, 1.0)),
		Vertex(glm::vec3(1.0, 1.0,  -1.0)),

		Vertex(glm::vec3(-1.0,  -1.0,  1.0)),
		Vertex(glm::vec3(-1.0,  1.0, 1.0)),
		Vertex(glm::vec3(1.0, 1.0, 1.0)),
		Vertex(glm::vec3(1.0, -1.0,  1.0)),

		Vertex(glm::vec3(-1.0, 1.0, -1.0)),
		Vertex(glm::vec3(1.0, 1.0, -1.0)),
		Vertex(glm::vec3(1.0, 1.0,  1.0)),
		Vertex(glm::vec3(-1.0, 1.0,  1.0)),

		Vertex(glm::vec3(-1.0,  -1.0, -1.0)),
		Vertex(glm::vec3(-1.0,  -1.0, 1.0)),
		Vertex(glm::vec3(1.0,  -1.0,  -1.0)),
		Vertex(glm::vec3(-1.0,  -1.0,  1.0)),
		Vertex(glm::vec3(1.0,  -1.0,  1.0)),
	};

	std::vector<unsigned int> vecIndex
	{
		0,1,2,2,3,0, 4,5,6,6,7,4, 8,9,10,10,11,8, 12,13,14,14,15,12, 16,17,18,18,19,16, 20,21,22,22,23,24
	};

	auto spTransform = std::make_shared<Transform>();

	return std::make_shared<GeometryNode>(vecVertex, vecIndex, spRenderState, spTransform);
}

#define environment_map
//#define explode_face
//#define explode_vertex
#define view_normal
int main()
{
	//≥ı ºªØglfw°¢glad
	auto spGLResource = std::make_shared<GLResource>();
	spGLResource->CreateGLFWWindow(SCR_WIDTH, SCR_HEIGHT, WINDOW_NAME);
	std::cout << "œ‘ø®–Õ∫≈£∫" << spGLResource->GetGPUVersion() << std::endl;

	auto spCamera = std::make_shared<Camera>(glm::vec3(0.f, 10.f, 20.f));
	auto spScene = std::make_shared<Scene>(spGLResource, spCamera);

#ifdef environment_map
	auto spShader = std::make_shared<Shader>("../resources/shaders/skybox/environment_mapping/vertex.vs",
		"../resources/shaders/skybox/environment_mapping/fragment.fs");
#endif // environment_map

#ifdef explode_face
	auto spShader = std::make_shared<Shader>("../resources/shaders/skybox/explode_face/vertex.vs",
		"../resources/shaders/skybox/explode_face/fragment.fs",
		"../resources/shaders/skybox/explode_face/geometry_face.gs");
#endif // 

#ifdef explode_vertex
	auto spShader = std::make_shared<Shader>("../resources/shaders/skybox/explode_vertex/vertex.vs",
		"../resources/shaders/skybox/explode_vertex/fragment.fs",
		"../resources/shaders/skybox/explode_vertex/geometry_vertex.gs");
#endif // 

	std::vector<std::string> vecSkyPath
	{
		"../resources/textures/skybox/right.jpg",
		"../resources/textures/skybox/left.jpg",
		"../resources/textures/skybox/top.jpg",
		"../resources/textures/skybox/bottom.jpg",
		"../resources/textures/skybox/front.jpg",
		"../resources/textures/skybox/back.jpg",
	};
	auto spTexture = std::make_shared<Texture>();
	auto glTexture = spTexture->AddTexture(vecSkyPath);
	auto spRenderState = std::make_shared<RenderState>(spShader, spTexture);
	spRenderState->SetBackGround(glm::vec4(0.2f, 0.3f, 0.3f, 1.0f));
	spRenderState->EnableDepthTest(true);
	spRenderState->SetExplode(true);
	spRenderState->SetDrawMode(DRAW_MODE::ELEMENT_MODE);
	spRenderState->SetPrimitiveMode(PRIMITIVE_MODE::TRIANGLES_MODE);

	auto spEntity = std::make_shared<Entity>();
	auto spRenderPass = std::make_shared<RenderPass>(spEntity, spRenderState);
	spEntity->AddMeshNode("../resources/objects/nanosuit/nanosuit.obj", spRenderState);

	spScene->AddRenderPass(spRenderPass);

#ifdef view_normal
	auto spNormalShader = std::make_shared<Shader>("../resources/shaders/skybox/view_normal/vertex.vs",
		"../resources/shaders/skybox/view_normal/fragment.fs",
		"../resources/shaders/skybox/view_normal/geometry_normal.gs");
#endif
	auto spNormalRenderState = std::make_shared<RenderState>(spNormalShader);
	spNormalRenderState->SetBackGround(glm::vec4(0.2f, 0.3f, 0.3f, 1.0f));
	spNormalRenderState->EnableDepthTest(true);
	spNormalRenderState->SetDrawMode(DRAW_MODE::ELEMENT_MODE);
	spNormalRenderState->SetPrimitiveMode(PRIMITIVE_MODE::TRIANGLES_MODE);
	spNormalRenderState->SetClearBuffer(false);

	auto spNormalRenderPass = std::make_shared<RenderPass>(spEntity, spNormalRenderState);
	spScene->AddRenderPass(spNormalRenderPass);


	auto spSkyTexture = std::make_shared<Texture>();
	auto spTextureStruct = std::make_shared<TextureStruct>();
	spTextureStruct->eType = TextureType::CUBEMAP;
	spTextureStruct->sPath = "";
	spTextureStruct->uiID = glTexture;
	spSkyTexture->AddTexture(spTextureStruct);

	auto spSkyShader = std::make_shared<Shader>("../resources/shaders/skybox/skybox/skyvertex.vs", "../resources/shaders/skybox/skybox/skyfragment.fs");
	auto spSkyRenderState = std::make_shared<RenderState>(spSkyShader, spSkyTexture);
	spSkyRenderState->SetBackGround(glm::vec4(0.2f, 0.3f, 0.3f, 1.0f));
	spSkyRenderState->EnableDepthTest(true);
	spSkyRenderState->SetDepthFunc(GL_LEQUAL);
	spSkyRenderState->SetDrawMode(DRAW_MODE::ELEMENT_MODE);
	spSkyRenderState->SetPrimitiveMode(PRIMITIVE_MODE::TRIANGLES_MODE);
	spSkyRenderState->SetClearBuffer(false);
	spSkyRenderState->SetDrawSkyBox(true);

	auto spSkyEntity = std::make_shared<Entity>();
	spSkyEntity->AddGeometryNode(CreatCubeNode(spSkyRenderState));
	auto spSkyRenderPass = std::make_shared<RenderPass>(spSkyEntity, spSkyRenderState);
	spScene->AddRenderPass(spSkyRenderPass);

	spScene->Draw();
}

