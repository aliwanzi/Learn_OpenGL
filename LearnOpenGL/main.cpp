#include "scene.h"
#include "gl_resource.h"
#include "CubeMapBuffer.h"
#include <random>

const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;
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

std::vector<glm::vec3> lightPositions{
	glm::vec3(-10.0f, 10.0f,10.0f),
	glm::vec3(10.0f, 10.0f,10.0f),
	glm::vec3(-10.0f,-10.0f,10.0f),
	glm::vec3(10.0f,-10.0f,10.0f),
};

std::shared_ptr<GeometryNode> CreatBoxNode(std::shared_ptr<RenderState> spRenderState)
{
	auto spTransform = std::make_shared<Transform>();
	return std::make_shared<GeometryNode>(vecVertex, vecIndex, spRenderState, spTransform);
}

void CreatSphere(std::vector<Vertex>& vecVertex, std::vector<unsigned int>& vecIndices)
{
	const unsigned int X_SEGMENTS = 64;
	const unsigned int Y_SEGMENTS = 64;

	vecVertex.clear();
	vecVertex.reserve(64 * 64);
	for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
	{
		for (unsigned int y = 0; y <= Y_SEGMENTS; ++y)
		{
			float xSegment = float(x) / float(X_SEGMENTS);
			float ySegment = float(y) / float(Y_SEGMENTS);
			float xPos = std::cos(xSegment * 2.0f * std::_Pi) * std::sin(ySegment * std::_Pi);
			float yPos = std::cos(ySegment * std::_Pi);
			float zPos = std::sin(xSegment * 2.0f * std::_Pi) * std::sin(ySegment * std::_Pi);

			Vertex vertex(glm::vec3(xPos, yPos, zPos), glm::vec2(xSegment, ySegment), glm::vec3(xPos, yPos, zPos));
			vecVertex.push_back(vertex);
		}
	}

	vecIndices.clear();
	vecIndices.reserve(X_SEGMENTS * Y_SEGMENTS);
	bool oddRow(false);
	for (unsigned int y = 0; y < Y_SEGMENTS; y++)
	{
		if (!oddRow)
		{
		for (unsigned int x = 0; x <= X_SEGMENTS; x++)
		{
			vecIndices.push_back(y * (X_SEGMENTS + 1) + x);
			vecIndices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
		}
		}
		else
		{
			for (int x = X_SEGMENTS; x >= 0; --x)
			{
				vecIndices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
				vecIndices.push_back(y * (X_SEGMENTS + 1) + x);
			}
		}
		oddRow = !oddRow;
	}
}


void CreateSphereNode(std::shared_ptr<RenderState> spRenderState, std::vector<std::shared_ptr<Node>>& vecNode,
	std::vector<Vertex>& vecVertex, std::vector<unsigned int>& vecIndices)
{
	const int nrRows = 7;
	const int nrColumns = 7;
	const float spacing = 2.5;
	for (int row = 0; row < nrRows; row++)
	{
		for (int col = 0; col < nrColumns; col++)
		{
			auto spTransform = std::make_shared<Transform>();
			spTransform->SetModelPan(glm::vec3(
				(col - (nrColumns / 2)) * spacing,
				(row - (nrRows / 2)) * spacing,
				0.0f));

			auto spNode = std::make_shared<GeometryNode>(vecVertex, vecIndices, spRenderState, spTransform);
			spNode->SetUniformAlbedo(glm::vec3(0.5f, 0.0, 0.0));
			spNode->SetUniformAo(1.0f);
			spNode->SetUniformRouthness(glm::clamp((float)col / (float)nrColumns, 0.05f, 1.0f));
			spNode->SetUniformMetallic((float)row / (float)nrRows);
			vecNode.push_back(spNode);
		}
	}

	std::vector<std::shared_ptr<Light>> vecLights;
	for (int i = 0; i < lightPositions.size(); i++)
	{
		auto spPointLight = std::make_shared<PointLight>();
		spPointLight->SetLightType(LightType::POINT_LIGHT);

		spPointLight->SetLightPosition(lightPositions[i]);
		spPointLight->SetDiffuse(glm::vec3(300.f));

		vecLights.emplace_back(spPointLight);
	}
	spRenderState->SetLights(vecLights);
}

void CreateLightNode(std::shared_ptr<RenderState> spRenderState, std::vector<std::shared_ptr<Node>>& vecNode,
	std::vector<Vertex>& vecVertex, std::vector<unsigned int>& vecIndices)
{
	for (int i = 0; i < lightPositions.size(); i++)
	{
		auto spTransform = std::make_shared<Transform>();
		spTransform->SetModelPan(lightPositions[i]);

		auto spNode = std::make_shared<GeometryNode>(vecVertex, vecIndices, spRenderState, spTransform);
		vecNode.push_back(spNode);
	}
}

#define CASE1
#define IRRADIANCE

int main()
{
	//≥ı ºªØglfw°¢glad
	auto spGLResource = std::make_shared<GLResource>();
	spGLResource->CreateGLFWWindow(SCR_WIDTH, SCR_HEIGHT, WINDOW_NAME);
	std::cout << "œ‘ø®–Õ∫≈£∫" << spGLResource->GetGPUVersion() << std::endl;

	auto spCamera = std::make_shared<Camera>(glm::vec3(0.f, 0.f, 3.f));
	auto spScene = std::make_shared<Scene>(spGLResource, spCamera);
	
	std::vector<Vertex> vecVertex;
	std::vector<unsigned int> vecIndices;
	CreatSphere(vecVertex, vecIndices);
#ifdef CASE1
	//DrawBuffer envCubemap
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

#ifdef IRRADIANCE
		//DrawBuffer irradiance
	auto spIrradianceShader = std::make_shared<Shader>("../resources/shaders/IBL/cubemap.vs",
		"../resources/shaders/IBL/irradiance.fs");

	auto spIrradianceTexture = std::make_shared<Texture>();
	auto spIrrTex = std::make_shared<TextureStruct>();
	spIrrTex->eType = TextureType::CUBEMAP;
	spIrrTex->uiID = spCubeMapBuffer->GetCubeMapTexture();
	spIrradianceTexture->AddTexture(spIrrTex);

	auto spIrradianceRenderState = std::make_shared<RenderState>(spIrradianceShader, spIrradianceTexture);
	spIrradianceRenderState->SetBackGround(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	spIrradianceRenderState->EnableDepthTest(true);
	spIrradianceRenderState->SetDrawMode(DRAW_MODE::ELEMENT_MODE);
	spIrradianceRenderState->SetPrimitiveMode(PRIMITIVE_MODE::TRIANGLES_MODE);

	auto spIrradianceNode = CreatBoxNode(spIrradianceRenderState);
	auto spIrradianceBuffer = std::make_shared<CubeMapBuffer>(32, 32, SCR_WIDTH, SCR_HEIGHT);
	spIrradianceBuffer->DrawCubeMap(spIrradianceNode);
#endif // IRRADIANCE

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
	//spScene->AddRenderPass(spEnvRenderPass);

	//draw sphere
	auto spSphereShader = std::make_shared<Shader>("../resources/shaders/IBL/pbr.vs",
		"../resources/shaders/IBL/pbr.fs");
	//auto spSphereShader = std::make_shared<Shader>("../resources/shaders/IBL/pbr.vs",
	//	"../resources/shaders/IBL/irradiance_pbr.fs");
	auto spSphereTexture = std::make_shared<Texture>();
	auto spIrrTexStr = std::make_shared<TextureStruct>();
	spIrrTexStr->eType = TextureType::CUBEMAP;
	spIrrTexStr->uiID = spIrradianceBuffer->GetCubeMapTexture();
	spSphereTexture->AddTexture(spIrrTexStr);

	auto spSphereState = std::make_shared<RenderState>(spSphereShader, spSphereTexture);
	spSphereState->SetBackGround(glm::vec4(0.2f, 0.3f, 0.3f, 1.0f));
	spSphereState->SetClearBuffer(true);
	spSphereState->EnableDepthTest(true);
	spSphereState->SetDrawMode(DRAW_MODE::ELEMENT_MODE);
	spSphereState->SetPrimitiveMode(PRIMITIVE_MODE::TRIANGLES_STRIP_MODE);

	auto spSphereEntity = std::make_shared<Entity>();
	std::vector<std::shared_ptr<Node>> vecNode;
	CreateSphereNode(spSphereState, vecNode, vecVertex, vecIndices);
	for (int i = 0; i < vecNode.size(); ++i)
	{
		spSphereEntity->AddGeometryNode(vecNode[i]);
	}
	auto spSphereRenderPass = std::make_shared<RenderPass>(spSphereEntity, spSphereState);
	spScene->AddRenderPass(spSphereRenderPass);

	//draw light
	auto spLightShader = std::make_shared<Shader>("../resources/shaders/IBL/pbr.vs",
		"../resources/shaders/IBL/light.fs");
	auto spLightTexture = std::make_shared<Texture>();
	auto spLightState = std::make_shared<RenderState>(spLightShader, spLightTexture);
	spLightState->SetBackGround(glm::vec4(0.2f, 0.3f, 0.3f, 1.0f));
	spLightState->SetClearBuffer(false);
	spLightState->EnableDepthTest(true);
	spLightState->SetDrawMode(DRAW_MODE::ELEMENT_MODE);
	spLightState->SetPrimitiveMode(PRIMITIVE_MODE::TRIANGLES_STRIP_MODE);

	auto spLightEntity = std::make_shared<Entity>();
	std::vector<std::shared_ptr<Node>> vecLightNode;
	CreateLightNode(spLightState, vecLightNode, vecVertex, vecIndices);
	for (int i = 0; i < vecLightNode.size(); ++i)
	{
		spLightEntity->AddGeometryNode(vecLightNode[i]);
	}
	auto spLightRenderPass = std::make_shared<RenderPass>(spLightEntity, spLightState);
	//spScene->AddRenderPass(spLightRenderPass);

	spScene->Draw();
#endif // !CASE1
}