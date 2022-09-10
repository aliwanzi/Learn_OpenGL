#include "scene.h"
#include "gl_resource.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const std::string WINDOW_NAME = "LearnOpenGL";

void CreatBoxNode(std::vector<std::shared_ptr<Node>>& vecNode, std::shared_ptr<RenderState> spRenderState)
{
	std::vector<Vertex> vecVertex
	{
		Vertex(glm::vec3(-0.5, -0.5, -0.5),glm::vec2(0.0, 0.0),glm::vec3(0.f,0.f,-1.f)),//0
		Vertex(glm::vec3(0.5, -0.5, -0.5),glm::vec2(1.0, 0.0),glm::vec3(0.f,0.f,-1.f)),//1
		Vertex(glm::vec3(0.5,  0.5, -0.5),glm::vec2(1.0, 1.0),glm::vec3(0.f,0.f,-1.f)),//2
		Vertex(glm::vec3(-0.5,  0.5, -0.5),glm::vec2(0.0, 1.0),glm::vec3(0.f,0.f,-1.f)),//3

		Vertex(glm::vec3(-0.5, -0.5, 0.5),glm::vec2(0.0, 0.0),glm::vec3(0.f,0.f,1.f)),//4
		Vertex(glm::vec3(0.5, -0.5, 0.5),glm::vec2(1.0, 0.0),glm::vec3(0.f,0.f,1.f)),//5
		Vertex(glm::vec3(0.5,  0.5, 0.5),glm::vec2(1.0, 1.0),glm::vec3(0.f,0.f,1.f)),//6
		Vertex(glm::vec3(-0.5,  0.5, 0.5),glm::vec2(0.0, 1.0),glm::vec3(0.f,0.f,1.f)),//7

		Vertex(glm::vec3(-0.5,  0.5,  0.5),glm::vec2(1.0, 0.0),glm::vec3(-1.f,0.f,0.f)),
		Vertex(glm::vec3(-0.5,  0.5, -0.5),glm::vec2(1.0, 1.0),glm::vec3(-1.f,0.f,0.f)),
		Vertex(glm::vec3(-0.5, -0.5, -0.5),glm::vec2(0.0, 1.0),glm::vec3(-1.f,0.f,0.f)),
		Vertex(glm::vec3(-0.5, -0.5,  0.5),glm::vec2(0.0, 0.0),glm::vec3(-1.f,0.f,0.f)),

		Vertex(glm::vec3(0.5,  0.5,  0.5),glm::vec2(1.0, 0.0),glm::vec3(1.f,0.f,0.f)),
		Vertex(glm::vec3(0.5,  0.5, -0.5),glm::vec2(1.0, 1.0),glm::vec3(1.f,0.f,0.f)),
		Vertex(glm::vec3(0.5, -0.5, -0.5),glm::vec2(0.0, 1.0),glm::vec3(1.f,0.f,0.f)),
		Vertex(glm::vec3(0.5, -0.5,  0.5),glm::vec2(0.0, 0.0),glm::vec3(1.f,0.f,0.f)),

		Vertex(glm::vec3(-0.5, -0.5, -0.5),glm::vec2(0.0, 1.0),glm::vec3(0.f,-1.f,0.f)),
		Vertex(glm::vec3(0.5, -0.5, -0.5),glm::vec2(1.0, 1.0),glm::vec3(0.f,-1.f,0.f)),
		Vertex(glm::vec3(0.5, -0.5,  0.5),glm::vec2(1.0, 0.0),glm::vec3(0.f,-1.f,0.f)),
		Vertex(glm::vec3(-0.5, -0.5,  0.5),glm::vec2(0.0, 0.0),glm::vec3(0.f,-1.f,0.f)),

		Vertex(glm::vec3(-0.5,  0.5, -0.5),glm::vec2(0.0, 1.0),glm::vec3(0.f,1.f,0.f)),
		Vertex(glm::vec3(0.5,  0.5, -0.5),glm::vec2(1.0, 1.0),glm::vec3(0.f,1.f,0.f)),
		Vertex(glm::vec3(0.5,  0.5,  0.5),glm::vec2(1.0, 0.0),glm::vec3(0.f,1.f,0.f)),
		Vertex(glm::vec3(-0.5,  0.5,  0.5),glm::vec2(0.0, 0.0),glm::vec3(0.f,1.f,0.f))
	};

	std::vector<unsigned int> vecIndex
	{
		0,1,2,2,3,0, 4,5,6,6,7,4, 8,9,10,10,11,8, 12,13,14,14,15,12, 16,17,18,18,19,16, 20,21,22,22,23,20
	};

	// world space positions of our cubes
	std::vector<glm::vec3> cubePositions = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	for (size_t i = 0; i < cubePositions.size(); i++)
	{
		auto spTransform = std::make_shared<Transform>();
		spTransform->SetModelPan(cubePositions[i]);
		spTransform->SetModelRotAixs(glm::vec3(1.0f, 0.3f, 0.5f));
		spTransform->SetModelRotAngle(static_cast<float>(20 * i));
		spTransform->SetModelRotUseTime();

		auto spNode = std::make_shared<GeometryNode>(vecVertex, vecIndex, spRenderState, spTransform);
		vecNode.push_back(spNode);
	}
}

void CreatLightsNode(std::vector<std::shared_ptr<Node>>& vecNode,
	std::shared_ptr<RenderState> spRenderState, std::vector<std::shared_ptr<Light>>& vecLights)
{
	std::vector<Vertex> vecVertex
	{
		Vertex(glm::vec3(-0.5, -0.5, -0.5)),//0
		Vertex(glm::vec3(0.5, -0.5, -0.5)),//1
		Vertex(glm::vec3(0.5,  0.5, -0.5)),//2
		Vertex(glm::vec3(-0.5,  0.5, -0.5)),//3

		Vertex(glm::vec3(-0.5, -0.5, 0.5)),//4
		Vertex(glm::vec3(0.5, -0.5, 0.5)),//5
		Vertex(glm::vec3(0.5,  0.5, 0.5)),//6
		Vertex(glm::vec3(-0.5,  0.5, 0.5)),//7

		Vertex(glm::vec3(-0.5,  0.5,  0.5)),
		Vertex(glm::vec3(-0.5,  0.5, -0.5)),
		Vertex(glm::vec3(-0.5, -0.5, -0.5)),
		Vertex(glm::vec3(-0.5, -0.5,  0.5)),

		Vertex(glm::vec3(0.5,  0.5,  0.5)),
		Vertex(glm::vec3(0.5,  0.5, -0.5)),
		Vertex(glm::vec3(0.5, -0.5, -0.5)),
		Vertex(glm::vec3(0.5, -0.5,  0.5)),

		Vertex(glm::vec3(-0.5, -0.5, -0.5)),
		Vertex(glm::vec3(0.5, -0.5, -0.5)),
		Vertex(glm::vec3(0.5, -0.5,  0.5)),
		Vertex(glm::vec3(-0.5, -0.5,  0.5)),

		Vertex(glm::vec3(-0.5,  0.5, -0.5)),
		Vertex(glm::vec3(0.5,  0.5, -0.5)),
		Vertex(glm::vec3(0.5,  0.5,  0.5)),
		Vertex(glm::vec3(-0.5,  0.5,  0.5))
	};

	std::vector<unsigned int> vecIndex
	{
		0,1,2,2,3,0, 4,5,6,6,7,4, 8,9,10,10,11,8, 12,13,14,14,15,12, 16,17,18,18,19,16, 20,21,22,22,23,20
	};


	std::vector<glm::vec3> pointLightPositions = {
		glm::vec3(0.7f,0.2f,2.0f),
		glm::vec3(2.3f,-3.3f,-4.0f),
		glm::vec3(-4.f,2.f,-12.f),
		glm::vec3(0.f,0.f,-3.f)
	};

	for (size_t i = 0; i < pointLightPositions.size(); i++)
	{
		auto spTransform = std::make_shared<Transform>();
		spTransform->SetModelPan(pointLightPositions[i]);
		spTransform->SetModelScale(glm::vec3(0.2f));
		auto spNode = std::make_shared<GeometryNode>(vecVertex, vecIndex, spRenderState, spTransform);
		vecNode.push_back(spNode);

		auto spPointLight = std::make_shared<PointLight>();
		spPointLight->SetLightPosition(pointLightPositions[i]);
		spPointLight->SetAmbient(glm::vec3(0.05f));
		spPointLight->SetDiffuse(glm::vec3(0.8f));
		spPointLight->SetSpecular(glm::vec3(1.f), 32.f);
		spPointLight->SetLightType(LightType::POINT_LIGHT);
		vecLights.push_back(spPointLight);
	}

	auto spDirLight = std::make_shared<DirLight>();
	spDirLight->SetLightDirection(glm::vec3(-0.2f, -1.0f, -0.3f));
	spDirLight->SetAmbient(glm::vec3(0.05f));
	spDirLight->SetDiffuse(glm::vec4(0.4f));
	spDirLight->SetSpecular(glm::vec3(0.5f), 32.f);
	spDirLight->SetLightType(LightType::DIR_LIGHT);
	vecLights.push_back(spDirLight);

	auto spSpotLight = std::make_shared<SpotLight>();
	spSpotLight->SetAmbient(glm::vec3(0.f));
	spSpotLight->SetDiffuse(glm::vec3(1.0f));
	spSpotLight->SetSpecular(glm::vec3(1.f), 32.f);
	spSpotLight->SetLightType(LightType::SPOT_LIGHT);
	vecLights.push_back(spSpotLight);
}

int main()
{
	//初始化glfw、glad
	auto spGLResource = std::make_shared<GLResource>();
	spGLResource->CreateGLFWWindow(SCR_WIDTH, SCR_HEIGHT, WINDOW_NAME);
	std::cout << "显卡型号：" << spGLResource->GetGPUVersion() << std::endl;

	auto spCamera = std::make_shared<Camera>(glm::vec3(0.f, 0.f, 3.f));
	auto spScene = std::make_shared<Scene>(spGLResource, spCamera);
	spScene->SetBackGround(glm::vec4(0.1, 0.1, 0.1, 1.0));

	//绘制立方体
	auto spLightingShader = std::make_shared<Shader>("../resources/shaders/light/light.vs", "../resources/shaders/light/light.fs");
	auto spTexture = std::make_shared<Texture>();
	spTexture->AddTexture("../resources/textures/container2.png", DIFFUSE);
	spTexture->AddTexture("../resources/textures/container2_specular.png", SPECULAR);
	auto spLightingRenderState = std::make_shared<RenderState>(spLightingShader, spTexture);
	spLightingRenderState->SetDepthTest(true);
	spLightingRenderState->SetDrawMode(DRAW_MODE::ELEMENT_MODE);
	spLightingRenderState->SetPrimitiveMode(PRIMITIVE_MODE::TRIANGLES_MODE);

	auto spLightingEntity = std::make_shared<Entity>();
	std::vector<std::shared_ptr<Node>> vecNodeLighting;
	CreatBoxNode(vecNodeLighting, spLightingRenderState);
	for (size_t i = 0; i < vecNodeLighting.size(); i++)
	{
		spLightingEntity->AddNode(vecNodeLighting[i]);
	}
	auto spLightingRenderPass = std::make_shared<RenderPass>(spLightingEntity, spLightingRenderState);
	spScene->AddRenderPass(spLightingRenderPass);

	auto spLightCubeShader = std::make_shared<Shader>("../resources/shaders/light/light_cube.vs", "../resources/shaders/light/light_cube.fs");
	auto spLightCubeRenderState = std::make_shared<RenderState>(spLightCubeShader, nullptr);
	spLightCubeRenderState->SetDrawMode(DRAW_MODE::ELEMENT_MODE);
	spLightCubeRenderState->SetPrimitiveMode(PRIMITIVE_MODE::TRIANGLES_MODE);

	auto spLightCubeEntity = std::make_shared<Entity>();
	std::vector<std::shared_ptr<Node>> vecNodeLightCube;
	std::vector<std::shared_ptr<Light>> vecLights;
	CreatLightsNode(vecNodeLightCube, spLightCubeRenderState, vecLights);
	for (size_t i = 0; i < vecNodeLightCube.size(); i++)
	{
		spLightCubeEntity->AddNode(vecNodeLightCube[i]);
	}
	//设置光源
	spLightingRenderState->SetLights(vecLights);

	auto spLightCubeRenderPass = std::make_shared<RenderPass>(spLightCubeEntity, spLightCubeRenderState);
	spScene->AddRenderPass(spLightCubeRenderPass);

	spScene->Draw();
}

