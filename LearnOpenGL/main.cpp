#include "scene.h"
#include "gl_resource.h"
#include <ctime>
#include <map>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const std::string WINDOW_NAME = "LearnOpenGL";

std::vector<glm::vec3> objectPosition
{
	glm::vec3(-3.0,-0.5,-3.0),
	glm::vec3(0.0, -0.5, -3.0),
	glm::vec3(3.0,  -0.5, -3.0),
	glm::vec3(-3.0,  -0.5,  0.0),
	glm::vec3(0.0,  -0.5,  0.0),
	glm::vec3(3.0,  -0.5,  0.0),
	glm::vec3(-3.0,  -0.5,  3.0),
	glm::vec3(0.0,  -0.5,  3.0),
	glm::vec3(3.0,  -0.5,  3.0),
};

std::shared_ptr<Node> CreatLights(std::shared_ptr<RenderState> spRenderState)
{
	const unsigned int NR_LIGHTS = 32;
	std::vector<std::shared_ptr<Light>> vecLights;
	srand(13);
	for (int i = 0; i < NR_LIGHTS; i++)
	{
		float xPos = static_cast<float>(((rand() % 100) / 100.f) * 6.0 - 3.0);
		float yPos = static_cast<float>(((rand() % 100) / 100.f) * 6.0 - 4.0);
		float zPos = static_cast<float>(((rand() % 100) / 100.f) * 6.0 - 3.0);

		float rColor = static_cast<float>(((rand() % 100) / 200.f) + 0.5);
		float gColor = static_cast<float>(((rand() % 100) / 200.f) + 0.5);
		float bColor = static_cast<float>(((rand() % 100) / 200.f) + 0.5);

		auto spPointLight = std::make_shared<PointLight>();
		spPointLight->SetLightType(LightType::POINT_LIGHT);

		spPointLight->SetLightPosition(glm::vec3(xPos, yPos, zPos));
		spPointLight->SetAmbient(glm::vec3(rColor, gColor, bColor));
		spPointLight->SetDiffuse(glm::vec3(rColor, gColor, bColor));
		spPointLight->SetSpecular(glm::vec3(rColor, gColor, bColor), 16);

		const float constant = 1.0f; // note that we don't send this to the shader, we assume it is always 1.0 (in our case)
		const float linear = 0.7f;
		const float quadratic = 1.8f;

		const float maxBrightness = std::fmaxf(std::fmaxf(rColor, gColor), bColor);
		float radius = (-linear + std::sqrt(linear * linear - 4 * quadratic * (constant - (256.0f / 1.0f) * maxBrightness))) / (2.0f * quadratic);
		spPointLight->SetConstant(constant);
		spPointLight->SetLinear(linear);
		spPointLight->SetQuartic(quadratic);
		spPointLight->SetRadius(radius);

		vecLights.emplace_back(spPointLight);
	}

	spRenderState->SetLights(vecLights);

	std::vector<Vertex> vecVertex
	{
		Vertex(glm::vec3(-1.0f,  1.0f, 0.0),glm::vec2(0.0,1.0)),//0
		Vertex(glm::vec3(-1.0f, -1.0f, 0.0),glm::vec2(0.0,0.0)),//1
		Vertex(glm::vec3(1.0f,  1.0f, 0.0),glm::vec2(1.0,1.0)),//2
		Vertex(glm::vec3(1.0f, -1.0f, 0.0),glm::vec2(1.0,0.0)),//3
	};

	std::vector<unsigned int> vecIndex
	{
		0,1,2,1,3,2
	};

	auto spTransform = std::make_shared<Transform>();

	return std::make_shared<GeometryNode>(vecVertex, vecIndex, spRenderState, spTransform);
}

void CreatCubeNode(std::shared_ptr<RenderState> spRenderState,
	const std::vector<std::shared_ptr<Light>>& vecLights,
	std::vector<std::shared_ptr<Node>>& vecNode)
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

	for (int i = 0; i < vecLights.size(); i++)
	{
		auto spTransform = std::make_shared<Transform>();
		auto spPointLight = std::dynamic_pointer_cast<PointLight>(vecLights[i]);
		spTransform->SetModelPan(spPointLight->GetLightPosition());
		spTransform->SetModelScale(glm::vec3(0.125f));

		auto spNode = std::make_shared<GeometryNode>(vecVertex, vecIndex, spRenderState, spTransform);
		spNode->SetUniformColor(spPointLight->GetDiffuse(), true);
		vecNode.push_back(spNode);
	}
}


int main()
{
	//初始化glfw、glad
	auto spGLResource = std::make_shared<GLResource>();
	spGLResource->CreateGLFWWindow(SCR_WIDTH, SCR_HEIGHT, WINDOW_NAME);
	std::cout << "显卡型号：" << spGLResource->GetGPUVersion() << std::endl;

	auto spCamera = std::make_shared<Camera>(glm::vec3(0.f, 0.f, 5.f));
	auto spScene = std::make_shared<Scene>(spGLResource, spCamera);

	//G-Buffer
	auto spShader = std::make_shared<Shader>("../resources/shaders/deferred/g_buffer.vs",
		"../resources/shaders/deferred/g_buffer.fs");

	auto spTexture = std::make_shared<Texture>();
	auto spRenderState = std::make_shared<RenderState>(spShader, spTexture);
	spRenderState->SetBackGround(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	spRenderState->EnableDepthTest(true);
	spRenderState->SetDrawMode(DRAW_MODE::ELEMENT_MODE);
	spRenderState->SetPrimitiveMode(PRIMITIVE_MODE::TRIANGLES_MODE);

	auto spGBuffer = std::make_shared<GBuffer>(SCR_WIDTH, SCR_HEIGHT);
	spRenderState->SetGBuffer(spGBuffer);
	spRenderState->EnableGBuffer(true);

	auto spEntity = std::make_shared<Entity>();
	auto spRenderPass = std::make_shared<RenderPass>(spEntity, spRenderState);
	spEntity->AddMeshNode("../resources/objects/backpack/backpack.obj", spRenderState);
	std::vector<std::shared_ptr<Transform>> vecTransform;
	for (int i = 0; i < objectPosition.size(); i++)
	{
		auto spTransform = std::make_shared<Transform>();
		spTransform->SetModelScale(glm::vec3(0.5));
		spTransform->SetModelPan(objectPosition[i]);
		vecTransform.emplace_back(spTransform);
	}
	spEntity->SetMultiTransform(vecTransform);
	spScene->AddRenderPass(spRenderPass);

	//作用光源
	auto spPositionInfo = std::make_shared<TextureStruct>();
	spPositionInfo->eType = TextureType::DIFFUSE;
	spPositionInfo->uiID = spGBuffer->GetPosition();
	auto spNormalInfor = std::make_shared<TextureStruct>();
	spNormalInfor->eType = TextureType::DIFFUSE;
	spNormalInfor->uiID = spGBuffer->GetNormal();
	auto spAlbedo = std::make_shared<TextureStruct>();
	spAlbedo->eType = TextureType::DIFFUSE;
	spAlbedo->uiID = spGBuffer->GetAlbedo();

	auto spLightTexture = std::make_shared<Texture>();
	spLightTexture->AddTexture(spPositionInfo);
	spLightTexture->AddTexture(spNormalInfor);
	spLightTexture->AddTexture(spAlbedo);

	auto spLightShader = std::make_shared<Shader>("../resources/shaders/deferred/deffered_shading.vs",
		"../resources/shaders/deferred/deffered_shading.fs");

	auto spLightRenderState = std::make_shared<RenderState>(spLightShader, spLightTexture);
	spLightRenderState->SetBackGround(glm::vec4(0.2f, 0.3f, 0.3f, 1.0f));
	spLightRenderState->EnableDepthTest(true);
	spLightRenderState->SetDrawMode(DRAW_MODE::ELEMENT_MODE);
	spLightRenderState->SetPrimitiveMode(PRIMITIVE_MODE::TRIANGLES_MODE);

	auto spLightNode = CreatLights(spLightRenderState);
	auto spLightEntity = std::make_shared<Entity>();
	spLightEntity->AddGeometryNode(spLightNode);

	auto spLightRenderPass = std::make_shared<RenderPass>(spLightEntity, spLightRenderState);
	spScene->AddRenderPass(spLightRenderPass);

	//深度测试绘制光源
	auto spLightBoxShader = std::make_shared<Shader>("../resources/shaders/deferred/deffered_light_box.vs",
		"../resources/shaders/deferred/deffered_light_box.fs");
	auto spLightBoxTexture = std::make_shared<Texture>();
	auto spLightBoxRenderState = std::make_shared<RenderState>(spLightBoxShader, spLightBoxTexture);
	spLightBoxRenderState->SetBackGround(glm::vec4(0.2f, 0.3f, 0.3f, 1.0f));
	spLightBoxRenderState->EnableDepthTest(true);
	spLightBoxRenderState->SetDrawMode(DRAW_MODE::ELEMENT_MODE);
	spLightBoxRenderState->SetPrimitiveMode(PRIMITIVE_MODE::TRIANGLES_MODE);
	spLightBoxRenderState->SetClearBuffer(false);
	spLightBoxRenderState->CopyGBufferDepth(true);
	spLightBoxRenderState->SetGBuffer(spGBuffer);
	std::vector<std::shared_ptr<Node>> vecLightBox;
	CreatCubeNode(spLightBoxRenderState, spLightRenderState->GetLights(), vecLightBox);
	auto spLightBoxEntity = std::make_shared<Entity>();
	for (size_t i = 0; i < vecLightBox.size(); i++)
	{
		spLightBoxEntity->AddGeometryNode(vecLightBox[i]);
	}
	auto spLightBoxRenderPass = std::make_shared<RenderPass>(spLightBoxEntity, spLightBoxRenderState);

	spScene->AddRenderPass(spLightBoxRenderPass);

	spScene->Draw();
}