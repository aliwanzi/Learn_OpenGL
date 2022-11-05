#include "scene.h"
#include "gl_resource.h"
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const std::string WINDOW_NAME = "LearnOpenGL";

std::vector<Vertex> vecVertex
{
	Vertex(glm::vec3(-1.0, -1.0, -1.0),glm::vec2( 0.0, 0.0),glm::vec3(0.0f,  0.0f, -1.0f)),
	Vertex(glm::vec3( 1.0,  1.0, -1.0),glm::vec2( 1.0, 1.0),glm::vec3(0.0f,  0.0f, -1.0f)),
	Vertex(glm::vec3( 1.0, -1.0, -1.0),glm::vec2( 1.0, 0.0),glm::vec3(0.0f,  0.0f, -1.0f)),
	Vertex(glm::vec3( 1.0,  1.0, -1.0),glm::vec2( 1.0, 1.0),glm::vec3(0.0f,  0.0f, -1.0f)),
	Vertex(glm::vec3(-1.0, -1.0, -1.0),glm::vec2( 0.0, 0.0),glm::vec3(0.0f,  0.0f, -1.0f)),
	Vertex(glm::vec3(-1.0,  1.0, -1.0),glm::vec2( 0.0, 1.0),glm::vec3(0.0f,  0.0f, -1.0f)),

	Vertex(glm::vec3(-1.0, -1.0,  1.0),glm::vec2( 0.0, 0.0),glm::vec3(0.0f,  0.0f,  1.0f)),//4
	Vertex(glm::vec3( 1.0, -1.0,  1.0),glm::vec2( 1.0, 0.0),glm::vec3(0.0f,  0.0f,  1.0f)),//5
	Vertex(glm::vec3( 1.0,  1.0,  1.0),glm::vec2( 1.0, 1.0),glm::vec3(0.0f,  0.0f,  1.0f)),//6
	Vertex(glm::vec3( 1.0,  1.0,  1.0),glm::vec2( 1.0, 1.0),glm::vec3(0.0f,  0.0f,  1.0f)),//7
	Vertex(glm::vec3(-1.0,  1.0,  1.0),glm::vec2( 0.0, 1.0),glm::vec3(0.0f,  0.0f,  1.0f)),//6
	Vertex(glm::vec3(-1.0, -1.0,  1.0),glm::vec2( 0.0, 0.0),glm::vec3(0.0f,  0.0f,  1.0f)),//7

	Vertex(glm::vec3(-1.0,  1.0,  1.0),glm::vec2( 1.0, 0.0),glm::vec3(-1.0f,  0.0f,  0.0f)),
	Vertex(glm::vec3(-1.0,  1.0, -1.0),glm::vec2( 1.0, 1.0),glm::vec3(-1.0f,  0.0f,  0.0f)),
	Vertex(glm::vec3(-1.0, -1.0, -1.0),glm::vec2( 0.0, 1.0),glm::vec3(-1.0f,  0.0f,  0.0f)),
	Vertex(glm::vec3(-1.0, -1.0, -1.0),glm::vec2( 0.0, 1.0),glm::vec3(-1.0f,  0.0f,  0.0f)),
	Vertex(glm::vec3(-1.0, -1.0,  1.0),glm::vec2( 0.0, 0.0),glm::vec3(-1.0f,  0.0f,  0.0f)),
	Vertex(glm::vec3(-1.0,  1.0,  1.0),glm::vec2( 1.0, 0.0),glm::vec3(-1.0f,  0.0f,  0.0f)),

	Vertex(glm::vec3( 1.0,  1.0,  1.0),glm::vec2( 1.0, 0.0),glm::vec3(1.0f,  0.0f,  0.0f)),
	Vertex(glm::vec3( 1.0, -1.0, -1.0),glm::vec2( 0.0, 1.0),glm::vec3(1.0f,  0.0f,  0.0f)),
	Vertex(glm::vec3( 1.0,  1.0, -1.0),glm::vec2( 1.0, 1.0),glm::vec3(1.0f,  0.0f,  0.0f)),
	Vertex(glm::vec3( 1.0, -1.0, -1.0),glm::vec2( 0.0, 1.0),glm::vec3(1.0f,  0.0f,  0.0f)),
	Vertex(glm::vec3( 1.0,  1.0,  1.0),glm::vec2( 1.0, 0.0),glm::vec3(1.0f,  0.0f,  0.0f)),
	Vertex(glm::vec3( 1.0, -1.0,  1.0),glm::vec2( 0.0, 0.0),glm::vec3(1.0f,  0.0f,  0.0f)),

	Vertex(glm::vec3(-1.0, -1.0, -1.0),glm::vec2( 0.0,  1.0),glm::vec3(0.0f, -1.0f,  0.0f)),
	Vertex(glm::vec3( 1.0, -1.0, -1.0),glm::vec2( 1.0,  1.0),glm::vec3(0.0f, -1.0f,  0.0f)),
	Vertex(glm::vec3( 1.0, -1.0,  1.0),glm::vec2( 1.0,  0.0),glm::vec3(0.0f, -1.0f,  0.0f)),
	Vertex(glm::vec3( 1.0, -1.0,  1.0),glm::vec2( 1.0,  0.0),glm::vec3(0.0f, -1.0f,  0.0f)),
	Vertex(glm::vec3(-1.0, -1.0,  1.0),glm::vec2( 0.0,  0.0),glm::vec3(0.0f, -1.0f,  0.0f)),
	Vertex(glm::vec3(-1.0, -1.0, -1.0),glm::vec2( 0.0,  1.0),glm::vec3(0.0f, -1.0f,  0.0f)),

	Vertex(glm::vec3(-1.0,  1.0, -1.0),glm::vec2( 0.0,  1.0),glm::vec3(0.0f,  1.0f,  0.0f)),
	Vertex(glm::vec3( 1.0,  1.0,  1.0),glm::vec2( 1.0,  0.0),glm::vec3(0.0f,  1.0f,  0.0f)),
	Vertex(glm::vec3( 1.0,  1.0, -1.0),glm::vec2( 1.0,  1.0),glm::vec3(0.0f,  1.0f,  0.0f)),
	Vertex(glm::vec3( 1.0,  1.0,  1.0),glm::vec2( 1.0,  0.0),glm::vec3(0.0f,  1.0f,  0.0f)),
	Vertex(glm::vec3(-1.0,  1.0, -1.0),glm::vec2( 0.0,  1.0),glm::vec3(0.0f,  1.0f,  0.0f)),
	Vertex(glm::vec3(-1.0,  1.0,  1.0),glm::vec2( 0.0,  0.0),glm::vec3(0.0f,  1.0f,  0.0f))
};

std::vector<unsigned int> vecIndex
{
	0,1,2,3,4,5, 6,7,8,9,10,11, 12,13,14,15,16,17, 18,19,20,21,22,23, 24,25,26,27,28,29, 30,31,32,33,34,35
};

void CreatLightNode(std::shared_ptr<RenderState> spRenderState,
	std::vector<std::shared_ptr<Node>>& vecLightNode)
{
	glm::vec3 lightPos(0.5f, 1.0f, 0.3f);

	auto spTransform = std::make_shared<Transform>();
	spTransform->SetModelPan(lightPos);
	spTransform->SetModelScale(glm::vec3(0.1f));

	auto spNode = std::make_shared<GeometryNode>(vecVertex, vecIndex, spRenderState, spTransform);
	spNode->SetUniformColor(glm::vec3(1.0f));
	vecLightNode.push_back(spNode);
}

std::shared_ptr<Node> CreatWoodNode(std::shared_ptr<RenderState> spRenderState)
{
	//light
	glm::vec3 lightPos(0.5f, 1.0f, 0.3f);
	
	auto spPointLight = std::make_shared<PointLight>();
	spPointLight->SetLightType(LightType::POINT_LIGHT);

	spPointLight->SetLightPosition(lightPos);
	spPointLight->SetAmbient(glm::vec3(0.0f));
	spPointLight->SetDiffuse(glm::vec3(1.0f));
	spPointLight->SetSpecular(glm::vec3(1.0f), 32);

	std::vector<std::shared_ptr<Light>> vecLights;
	vecLights.emplace_back(spPointLight);
	spRenderState->SetLights(vecLights);

	//model
	glm::vec3 pos1(-1.0f, 1.0f, 0.0f);
	glm::vec3 pos2(-1.0f, -1.0f, 0.0f);
	glm::vec3 pos3(1.0f, -1.0f, 0.0f);
	glm::vec3 pos4(1.0f, 1.0f, 0.0f);

	glm::vec2 uv1(0.0f, 1.0f);
	glm::vec2 uv2(0.0f, 0.0f);
	glm::vec2 uv3(1.0f, 0.0f);
	glm::vec2 uv4(1.0f, 1.0f);

	glm::vec3 normal(0.0f, 0.0f, 1.0f);

	glm::vec3 tangent1, bitangent1;
	glm::vec3 tangent2, bitangent2;

	glm::vec3 edge1 = pos2 - pos1;
	glm::vec3 edge2 = pos3 - pos1;
	glm::vec2 deltaUV1 = uv2 - uv1;
	glm::vec2 deltaUV2 = uv3 - uv1;
	float f = 1 / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);
	tangent1.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
	tangent1.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
	tangent1.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);

	bitangent1.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
	bitangent1.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
	bitangent1.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);


	edge1 = pos3 - pos1;
	edge2 = pos4 - pos1;
	deltaUV1 = uv3 - uv1;
	deltaUV2 = uv4 - uv1;

	f = 1 / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

	tangent2.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
	tangent2.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
	tangent2.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);

	bitangent2.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
	bitangent2.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
	bitangent2.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);

	std::vector<Vertex> quadVertices = {
		Vertex(pos1,uv1,normal,tangent1,bitangent1),
		Vertex(pos2,uv2,normal,tangent1,bitangent1),
		Vertex(pos3,uv3,normal,tangent1,bitangent1),

		Vertex(pos1,uv1,normal,tangent2,bitangent2),
		Vertex(pos3,uv3,normal,tangent2,bitangent2),
		Vertex(pos4,uv4,normal,tangent2,bitangent2)
	};

	std::vector<unsigned int> quadIndex
	{
		0,1,2,3,4,5
	};

	auto spTransform = std::make_shared<Transform>();
	return std::make_shared<GeometryNode>(quadVertices, quadIndex, spRenderState, spTransform);
}

#define CASE1
//#define CASE2

int main()
{
	//初始化glfw、glad
	auto spGLResource = std::make_shared<GLResource>();
	spGLResource->CreateGLFWWindow(SCR_WIDTH, SCR_HEIGHT, WINDOW_NAME);
	std::cout << "显卡型号：" << spGLResource->GetGPUVersion() << std::endl;

	auto spCamera = std::make_shared<Camera>(glm::vec3(0.f, 0.f, 3.f));
	auto spScene = std::make_shared<Scene>(spGLResource, spCamera);

#ifdef CASE1
	auto spRenderShader = std::make_shared<Shader>("../resources/shaders/normalmapping/normal_mapping/normal_mapping.vs",
		"../resources/shaders/normalmapping/normal_mapping/normal_mapping.fs");

	auto spTexture = std::make_shared<Texture>();
	spTexture->AddTexture("../resources/textures/brickwall.jpg", TextureType::DIFFUSE);
	spTexture->AddTexture("../resources/textures/brickwall_normal.jpg", TextureType::DIFFUSE);

	auto spRenderState = std::make_shared<RenderState>(spRenderShader, spTexture);
	spRenderState->SetBackGround(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	spRenderState->EnableDepthTest(true);
	spRenderState->SetDrawMode(DRAW_MODE::ELEMENT_MODE);
	spRenderState->SetPrimitiveMode(PRIMITIVE_MODE::TRIANGLES_MODE);
	spRenderState->EnableUseShadow(true);
	auto spRenderEntity = std::make_shared<Entity>();
	auto spRenderPass = std::make_shared<RenderPass>(spRenderEntity, spRenderState);

	auto spWallNode = CreatWoodNode(spRenderState);
	spRenderEntity->AddGeometryNode(spWallNode);
	spScene->AddRenderPass(spRenderPass);
#endif // CASE1

#ifdef CASE2
	auto spRenderShader = std::make_shared<Shader>("../resources/shaders/normalmapping/normal_mapping/normal_mapping.vs",
		"../resources/shaders/normalmapping/normal_mapping/parallax_mapping.fs");

	auto spTexture = std::make_shared<Texture>();
	spTexture->AddTexture("../resources/textures/bricks2.jpg", TextureType::DIFFUSE);
	spTexture->AddTexture("../resources/textures/bricks2_normal.jpg", TextureType::DIFFUSE);
	spTexture->AddTexture("../resources/textures/bricks2_disp.jpg", TextureType::DIFFUSE);

	auto spRenderState = std::make_shared<RenderState>(spRenderShader, spTexture);
	spRenderState->SetBackGround(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	spRenderState->EnableDepthTest(true);
	spRenderState->SetDrawMode(DRAW_MODE::ELEMENT_MODE);
	spRenderState->SetPrimitiveMode(PRIMITIVE_MODE::TRIANGLES_MODE);
	spRenderState->EnabelUseHightScale(true);
	spRenderState->EnableUseShadow(true);
	auto spRenderEntity = std::make_shared<Entity>();
	auto spRenderPass = std::make_shared<RenderPass>(spRenderEntity, spRenderState);

	auto spWallNode = CreatWoodNode(spRenderState);
	spRenderEntity->AddGeometryNode(spWallNode);
	spScene->AddRenderPass(spRenderPass);
#endif // CASE2

	//光源
	auto spLightShader = std::make_shared<Shader>("../resources/shaders/bloom/vertex.vs",
		"../resources/shaders/bloom/light.fs");
	auto spLightTexture = std::make_shared<Texture>();
	auto spLightRenderState = std::make_shared<RenderState>(spLightShader, spLightTexture);
	spLightRenderState->SetBackGround(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	spLightRenderState->EnableDepthTest(true);
	spLightRenderState->SetDrawMode(DRAW_MODE::ELEMENT_MODE);
	spLightRenderState->SetPrimitiveMode(PRIMITIVE_MODE::TRIANGLES_MODE);
	spLightRenderState->SetClearBuffer(false);

	auto spLightEntity = std::make_shared<Entity>();
	auto spLightRenderPass = std::make_shared<RenderPass>(spLightEntity, spLightRenderState);
	std::vector<std::shared_ptr<Node>> vecLightNode;
	CreatLightNode(spLightRenderState, vecLightNode);
	for (auto i = 0; i < vecLightNode.size(); i++)
	{
		spLightEntity->AddGeometryNode(vecLightNode[i]);
	}
	spScene->AddRenderPass(spLightRenderPass);

	spScene->Draw();
}

