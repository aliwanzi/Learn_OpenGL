#include "scene.h"
#include "gl_resource.h"
#include <ctime>
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

std::shared_ptr<Node> CreateTriangleInstance(std::shared_ptr<RenderState> spRenderState)
{
	std::vector<glm::vec2> vecOffset;
	int iIndex(0);
	float offset(0.1f);
	for (int y = -10; y < 10; y += 2)
	{
		for (int x = -10; x < 10; x += 2)
		{
			glm::vec2 translation;
			translation.x = (float)x / 10.0f + offset;
			translation.y = (float)y / 10.0f + offset;
			vecOffset.emplace_back(translation);
		}
	}

	std::vector<Vertex> vecVertex
	{
		Vertex(glm::vec3(-0.05,  0.05, 0.0),glm::vec2(0.0,0.0),glm::vec3(1.0,0.0,0.0)),//0
		Vertex(glm::vec3( 0.05, -0.05, 0.0),glm::vec2(0.0,0.0),glm::vec3(0.0,1.0,0.0)),//1
		Vertex(glm::vec3(-0.05, -0.05, 0.0),glm::vec2(0.0,0.0),glm::vec3(0.0,0.0,1.0)),//2
		Vertex(glm::vec3( 0.05,  0.05, 0.0),glm::vec2(0.0,0.0),glm::vec3(0.0,1.0,1.0)),//3
	};

	std::vector<unsigned int> vecIndex
	{
		0,1,2,0,1,3
	};


	auto spTransform = std::make_shared<Transform>();

	auto spGeometryNode = std::make_shared<GeometryNode>(vecVertex, vecIndex, spRenderState, spTransform);
	spGeometryNode->SetInstanceOffset(vecOffset);

	return spGeometryNode;
}

void CrateRockInstance(std::shared_ptr<Entity> spEntity)
{
	srand(unsigned(time(0)));
	const size_t amount(10000);

	std::vector<glm::mat4> vecOffset;
	vecOffset.resize(amount);
	float radius(50), offset(25.0);
	for (int i = 0; i < amount; i++)
	{
		glm::mat4 model = glm::mat4(1.0f);
		// 1. translation: displace along circle with 'radius' in range [-offset, offset]
		float angle = (float)i / (float)amount * 360.0f;
		float displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
		float x = sin(angle) * radius + displacement;
		displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
		float y = displacement * 0.4f; // keep height of asteroid field smaller compared to width of x and z
		displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
		float z = cos(angle) * radius + displacement;
		model = glm::translate(model, glm::vec3(x, y, z));

		// 2. scale: Scale between 0.05 and 0.25f
		float scale = static_cast<float>((rand() % 20) / 100.0 + 0.05);
		model = glm::scale(model, glm::vec3(scale));

		// 3. rotation: add random rotation around a (semi)randomly picked rotation axis vector
		float rotAngle = static_cast<float>((rand() % 360));
		model = glm::rotate(model, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));

		vecOffset[i] = model;
	}
	spEntity->SetInstanceOffset(vecOffset);
}

//#define CASE1
#define environment_map
//#define explode_face
//#define explode_vertex
#define view_normal

#define CASE2
//#define triangle_instance
#define rock_instance

int main()
{
	//≥ı ºªØglfw°¢glad
	auto spGLResource = std::make_shared<GLResource>();
	spGLResource->CreateGLFWWindow(SCR_WIDTH, SCR_HEIGHT, WINDOW_NAME);
	std::cout << "œ‘ø®–Õ∫≈£∫" << spGLResource->GetGPUVersion() << std::endl;

#ifdef CASE1
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
#endif // CASE1

#ifdef CASE2
#ifdef triangle_instance
	auto spTexture = std::make_shared<Texture>();
	auto spShader = std::make_shared<Shader>("../resources/shaders/instance/vertex.vs",
		"../resources/shaders/instance/fragment.fs");

	auto spRenderState = std::make_shared<RenderState>(spShader, spTexture);
	spRenderState->SetBackGround(glm::vec4(0.2f, 0.3f, 0.3f, 1.0f));
	spRenderState->EnableDepthTest(true);
	spRenderState->SetDrawMode(DRAW_MODE::ELEMENT_INSTANCE_MODE);

	spRenderState->SetPrimitiveMode(PRIMITIVE_MODE::TRIANGLES_MODE);

	auto spEntity = std::make_shared<Entity>();

	spEntity->AddGeometryNode(CreateTriangleInstance(spRenderState));
	auto spRenderPass = std::make_shared<RenderPass>(spEntity, spRenderState);
	spScene->AddRenderPass(spRenderPass);
#endif // triangle_instance

#ifdef rock_instance

	auto spCamera = std::make_shared<Camera>(glm::vec3(0.f, 0.f, 115.f));
	auto spScene = std::make_shared<Scene>(spGLResource, spCamera);
	spCamera->SetNearAndFar(0.1, 1000);

	auto spPlanetTexture = std::make_shared<Texture>();
	auto spPlanetShader = std::make_shared<Shader>("../resources/shaders/model/vertex.vs",
		"../resources/shaders/model/fragment.fs");
	auto spPlanetRenderState = std::make_shared<RenderState>(spPlanetShader, spPlanetTexture);
	spPlanetRenderState->SetBackGround(glm::vec4(0.2f, 0.3f, 0.3f, 1.0f));
	spPlanetRenderState->EnableDepthTest(true);
	spPlanetRenderState->SetDrawMode(DRAW_MODE::ELEMENT_MODE);
	spPlanetRenderState->SetPrimitiveMode(PRIMITIVE_MODE::TRIANGLES_MODE);

	auto spPlanetEntity = std::make_shared<Entity>();
	auto spPlanetRenderPass = std::make_shared<RenderPass>(spPlanetEntity, spPlanetRenderState);
	spPlanetEntity->AddMeshNode("../resources/objects/planet/planet.obj", spPlanetRenderState);
	auto spTransform = std::make_shared<Transform>();
	spTransform->SetModelPan(glm::vec3(0.0, -3.0f, 0.0f));
	spTransform->SetModelScale(glm::vec3(4.0f));
	spPlanetEntity->SetTransform(spTransform);

	spScene->AddRenderPass(spPlanetRenderPass);

	auto spRockTexture = std::make_shared<Texture>();
	auto spRockShader = std::make_shared<Shader>("../resources/shaders/instance/rock_vertex.vs",
		"../resources/shaders/instance/rock_fragment.fs");
	auto spRockRenderState = std::make_shared<RenderState>(spRockShader, spRockTexture);
	spRockRenderState->SetBackGround(glm::vec4(0.2f, 0.3f, 0.3f, 1.0f));
	spRockRenderState->EnableDepthTest(true);
	spRockRenderState->SetClearBuffer(false);
	spRockRenderState->SetDrawMode(DRAW_MODE::ELEMENT_INSTANCE_MODE);
	spRockRenderState->SetPrimitiveMode(PRIMITIVE_MODE::TRIANGLES_MODE);

	auto spRockEntity = std::make_shared<Entity>();
	auto spRockRenderPass = std::make_shared<RenderPass>(spRockEntity, spRockRenderState);
	spRockEntity->AddMeshNode("../resources/objects/rock/rock.obj", spRockRenderState);
	CrateRockInstance(spRockEntity);

	spScene->AddRenderPass(spRockRenderPass);


	std::vector<std::string> vecSkyPath
	{
		"../resources/textures/skybox/right.jpg",
		"../resources/textures/skybox/left.jpg",
		"../resources/textures/skybox/top.jpg",
		"../resources/textures/skybox/bottom.jpg",
		"../resources/textures/skybox/front.jpg",
		"../resources/textures/skybox/back.jpg",
	};

	auto spSkyTexture = std::make_shared<Texture>();
	spSkyTexture->AddTexture(vecSkyPath);

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

#endif // rock_instance

#endif // !CASE2

	spScene->Draw();
}

