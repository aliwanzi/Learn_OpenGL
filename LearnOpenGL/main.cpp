#include "scene.h"
#include "gl_resource.h"
#include <ctime>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const std::string WINDOW_NAME = "LearnOpenGL";

std::vector<glm::vec3> objectPosition
{
	glm::vec3( 0.0, -1.0, 0.0),
	glm::vec3( 0.0,  1.5, 0.0),
	glm::vec3( 2.0,  0.0, 1.0),
	glm::vec3(-1.0, -1.0, 2.0),
	glm::vec3( 0.0,  2.7, 4.0),
	glm::vec3(-2.0,  1.0, -3.0),
	glm::vec3(-3.0,  0.0, 0.0),
};

std::vector<glm::vec3> objectScale
{
	glm::vec3(12.5,0.5,12.5),
	glm::vec3(0.5),
	glm::vec3(0.5),
	glm::vec3(1.0),
	glm::vec3(1.25),
	glm::vec3(1.0),
	glm::vec3(0.5)
};

std::vector<glm::vec3> objectRotateAxis
{
	glm::vec3(0.0, 0.0, 1.0),
	glm::vec3(0.0, 0.0, 1.0),
	glm::vec3(0.0, 0.0, 1.0),
	glm::vec3(1.0, 0.0, 1.0),
	glm::vec3(1.0, 0.0, 1.0),
	glm::vec3(1.0, 0.0, 1.0),
	glm::vec3(0.0, 0.0, 1.0),
};

std::vector<float> objectRotateAngle
{
	0.0,
	0.0,
	0.0,
	60.0,
	23.0,
	124.0,
	0.0
};

std::vector<glm::vec3> lightPosition
{
	glm::vec3(0.0f,0.5f,1.5f),
	glm::vec3(-4.0f,0.5f,-3.0f),
	glm::vec3(3.0f,0.5f,1.0f),
	glm::vec3(-0.8f,2.4f,-1.0f)
};

std::vector<glm::vec3> lightColor
{
	glm::vec3(5.0f,5.0f,5.0f),
	glm::vec3(10.0f,0.0f,0.0f),
	glm::vec3(0.0f,0.0f,15.0f),
	glm::vec3(0.0f,5.0f,0.0f)
};

std::vector<Vertex> vecVertex
{
	Vertex(glm::vec3(-1.0, -1.0, -1.0),glm::vec2(0.0, 0.0),glm::vec3(0.f,0.f,-1.f)),//0
	Vertex(glm::vec3(1.0, -1.0, -1.0),glm::vec2(1.0, 0.0),glm::vec3(0.f,0.f,-1.f)),//1
	Vertex(glm::vec3(1.0,  1.0, -1.0),glm::vec2(1.0, 1.0),glm::vec3(0.f,0.f,-1.f)),//2
	Vertex(glm::vec3(-1.0,  1.0, -1.0),glm::vec2(0.0, 1.0),glm::vec3(0.f,0.f,-1.f)),//3

	Vertex(glm::vec3(-1.0, -1.0, 1.0),glm::vec2(0.0, 0.0),glm::vec3(0.f,0.f,1.f)),//4
	Vertex(glm::vec3(1.0, -1.0, 1.0),glm::vec2(1.0, 0.0),glm::vec3(0.f,0.f,1.f)),//5
	Vertex(glm::vec3(1.0,  1.0, 1.0),glm::vec2(1.0, 1.0),glm::vec3(0.f,0.f,1.f)),//6
	Vertex(glm::vec3(-1.0,  1.0, 1.0),glm::vec2(0.0, 1.0),glm::vec3(0.f,0.f,1.f)),//7

	Vertex(glm::vec3(-1.0,  1.0,  1.0),glm::vec2(1.0, 0.0),glm::vec3(-1.f,0.f,0.f)),
	Vertex(glm::vec3(-1.0,  1.0, -1.0),glm::vec2(1.0, 1.0),glm::vec3(-1.f,0.f,0.f)),
	Vertex(glm::vec3(-1.0, -1.0, -1.0),glm::vec2(0.0, 1.0),glm::vec3(-1.f,0.f,0.f)),
	Vertex(glm::vec3(-1.0, -1.0,  1.0),glm::vec2(0.0, 0.0),glm::vec3(-1.f,0.f,0.f)),

	Vertex(glm::vec3(1.0,  1.0,  1.0),glm::vec2(1.0, 0.0),glm::vec3(1.f,0.f,0.f)),
	Vertex(glm::vec3(1.0,  1.0, -1.0),glm::vec2(1.0, 1.0),glm::vec3(1.f,0.f,0.f)),
	Vertex(glm::vec3(1.0, -1.0, -1.0),glm::vec2(0.0, 1.0),glm::vec3(1.f,0.f,0.f)),
	Vertex(glm::vec3(1.0, -1.0,  1.0),glm::vec2(0.0, 0.0),glm::vec3(1.f,0.f,0.f)),

	Vertex(glm::vec3(-1.0, -1.0, -1.0),glm::vec2(0.0, 1.0),glm::vec3(0.f,-1.f,0.f)),
	Vertex(glm::vec3(1.0, -1.0, -1.0),glm::vec2(1.0, 1.0),glm::vec3(0.f,-1.f,0.f)),
	Vertex(glm::vec3(1.0, -1.0,  1.0),glm::vec2(1.0, 0.0),glm::vec3(0.f,-1.f,0.f)),
	Vertex(glm::vec3(-1.0, -1.0,  1.0),glm::vec2(0.0, 0.0),glm::vec3(0.f,-1.f,0.f)),

	Vertex(glm::vec3(-1.0,  1.0, -1.0),glm::vec2(0.0, 1.0),glm::vec3(0.f,1.f,0.f)),
	Vertex(glm::vec3(1.0,  1.0, -1.0),glm::vec2(1.0, 1.0),glm::vec3(0.f,1.f,0.f)),
	Vertex(glm::vec3(1.0,  1.0,  1.0),glm::vec2(1.0, 0.0),glm::vec3(0.f,1.f,0.f)),
	Vertex(glm::vec3(-1.0,  1.0,  1.0),glm::vec2(0.0, 0.0),glm::vec3(0.f,1.f,0.f))
};

std::vector<unsigned int> vecIndex
{
	0,1,2,2,3,0, 4,5,6,6,7,4, 8,9,10,10,11,8, 12,13,14,14,15,12, 16,17,18,18,19,16, 20,21,22,22,23,20
};


void CreatBoxNode(std::shared_ptr<RenderState> spRenderState,
	std::vector<std::shared_ptr<Node>>& vecBoxNode)
{
	for (int i = 1; i < objectPosition.size(); i++)
	{
		auto spTransform = std::make_shared<Transform>();
		spTransform->SetModelPan(objectPosition[i]);
		spTransform->SetModelScale(objectScale[i]);
		spTransform->SetModelRotAngle(objectRotateAngle[i]);
		spTransform->SetModelRotAixs(objectRotateAxis[i]);

		auto spNode = std::make_shared<GeometryNode>(vecVertex, vecIndex, spRenderState, spTransform);
		vecBoxNode.push_back(spNode);
	}

	std::vector<std::shared_ptr<Light>> vecLights;
	for (int i = 0; i < lightPosition.size(); i++)
	{
		auto spPointLight = std::make_shared<PointLight>();
		spPointLight->SetLightType(LightType::POINT_LIGHT);

		spPointLight->SetLightPosition(lightPosition[i]);
		spPointLight->SetAmbient(glm::vec3(0.05f));
		spPointLight->SetDiffuse(lightColor[i]);
		spPointLight->SetSpecular(glm::vec3(1.0), 32);
		vecLights.emplace_back(spPointLight);
	}

	spRenderState->SetLights(vecLights);
}

std::shared_ptr<Node> CreatWoodNode(std::shared_ptr<RenderState> spRenderState)
{
	auto spTransform = std::make_shared<Transform>();
	spTransform->SetModelPan(objectPosition[0]);
	spTransform->SetModelScale(objectScale[0]);
	spTransform->SetModelRotAngle(objectRotateAngle[0]);
	spTransform->SetModelRotAixs(objectRotateAxis[0]);

	std::vector<std::shared_ptr<Light>> vecLights;
	for (int i = 0; i < lightPosition.size(); i++)
	{
		auto spPointLight = std::make_shared<PointLight>();
		spPointLight->SetLightType(LightType::POINT_LIGHT);

		spPointLight->SetLightPosition(lightPosition[i]);
		spPointLight->SetAmbient(glm::vec3(0.05f));
		spPointLight->SetDiffuse(lightColor[i]);
		spPointLight->SetSpecular(glm::vec3(1.0), 32);
		vecLights.emplace_back(spPointLight);
	}

	spRenderState->SetLights(vecLights);
	return std::make_shared<GeometryNode>(vecVertex, vecIndex, spRenderState, spTransform);
}

void CreatLightNode(std::shared_ptr<RenderState> spRenderState,
	std::vector<std::shared_ptr<Node>>& vecLightNode)
{
	std::vector<std::shared_ptr<Light>> vecLights;
	for (int i = 0; i < lightPosition.size(); i++)
	{
		auto spTransform = std::make_shared<Transform>();
		spTransform->SetModelPan(lightPosition[i]);
		spTransform->SetModelScale(glm::vec3(0.25f));

		auto spNode = std::make_shared<GeometryNode>(vecVertex, vecIndex, spRenderState, spTransform);
		spNode->SetUniformColor(lightColor[i]);
		vecLightNode.push_back(spNode);
	}
}

std::shared_ptr<Node> CreateBlurNode(std::shared_ptr<RenderState> spRenderState)
{
	std::vector<Vertex> quarVertices
	{
		Vertex(glm::vec3(-1.0,  1.0, 0.0),glm::vec2(0.0, 1.0)),
		Vertex(glm::vec3(-1.0, -1.0, 0.0),glm::vec2(0.0, 0.0)),
		Vertex(glm::vec3(1.0,  1.0, 0.0),glm::vec2(1.0, 1.0)),
		Vertex(glm::vec3(1.0, -1.0, 0.0),glm::vec2(1.0, 0.0))
	};
	std::vector<unsigned int> quardIndex
	{
		0,1,2, 1,3,2
	};


	auto spTransform = std::make_shared<Transform>();
	return std::make_shared<GeometryNode>(quarVertices, quardIndex, spRenderState, spTransform);
}


int main()
{
	//≥ı ºªØglfw°¢glad
	auto spGLResource = std::make_shared<GLResource>();
	spGLResource->CreateGLFWWindow(SCR_WIDTH, SCR_HEIGHT, WINDOW_NAME);
	std::cout << "œ‘ø®–Õ∫≈£∫" << spGLResource->GetGPUVersion() << std::endl;

	auto spCamera = std::make_shared<Camera>(glm::vec3(0.f, 0.f, 5.f));
	auto spScene = std::make_shared<Scene>(spGLResource, spCamera);

	auto spHDRBuffer = std::make_shared<HDRBuffer>(SCR_WIDTH, SCR_HEIGHT);

	auto spBoxShader = std::make_shared<Shader>("../resources/shaders/bloom/vertex.vs",
		"../resources/shaders/bloom/box.fs");
	auto spBoxTexture = std::make_shared<Texture>();
	spBoxTexture->AddTexture("../resources/textures/container2.png", TextureType::DIFFUSE, true, true);
	spBoxTexture->AddTexture("../resources/textures/container2_specular.png", TextureType::SPECULAR, true, true);
	auto spBoxRenderState = std::make_shared<RenderState>(spBoxShader, spBoxTexture);
	spBoxRenderState->SetBackGround(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	spBoxRenderState->EnableDepthTest(true);
	spBoxRenderState->SetDrawMode(DRAW_MODE::ELEMENT_MODE);
	spBoxRenderState->SetPrimitiveMode(PRIMITIVE_MODE::TRIANGLES_MODE);
	spBoxRenderState->SetHDRBuffer(spHDRBuffer);
	spBoxRenderState->EnabelHDRBuffer(true);
	spBoxRenderState->EnableUseBlinn(true);
	spBoxRenderState->EnableUseGamma(true);
	auto spBoxEntity = std::make_shared<Entity>();
	auto spBoxRenderPass = std::make_shared<RenderPass>(spBoxEntity, spBoxRenderState);
	std::vector<std::shared_ptr<Node>> vecBoxNode;
	CreatBoxNode(spBoxRenderState, vecBoxNode);
	for (auto i = 0; i < vecBoxNode.size(); i++)
	{
		spBoxEntity->AddGeometryNode(vecBoxNode[i]);
	}
	spScene->AddRenderPass(spBoxRenderPass);


	auto spWoodShader = std::make_shared<Shader>("../resources/shaders/bloom/vertex.vs",
		"../resources/shaders/bloom/wood.fs");
	auto spWoodTexture = std::make_shared<Texture>();
	spWoodTexture->AddTexture("../resources/textures/wood.png", TextureType::DIFFUSE, true, true);
	auto spWoodRenderState = std::make_shared<RenderState>(spWoodShader, spWoodTexture);
	spWoodRenderState->SetBackGround(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	spWoodRenderState->EnableDepthTest(true);
	spWoodRenderState->SetDrawMode(DRAW_MODE::ELEMENT_MODE);
	spWoodRenderState->SetPrimitiveMode(PRIMITIVE_MODE::TRIANGLES_MODE);
	spWoodRenderState->SetClearBuffer(false);
	spWoodRenderState->SetHDRBuffer(spHDRBuffer);
	spWoodRenderState->EnabelHDRBuffer(true);
	spWoodRenderState->EnableUseBlinn(true);
	spWoodRenderState->EnableUseGamma(true);
	auto spWoodEntity = std::make_shared<Entity>();
	auto spWoodRenderPass = std::make_shared<RenderPass>(spWoodEntity, spWoodRenderState);
	spWoodEntity->AddGeometryNode(CreatWoodNode(spWoodRenderState));
	spScene->AddRenderPass(spWoodRenderPass);


	auto spLightShader = std::make_shared<Shader>("../resources/shaders/bloom/vertex.vs",
		"../resources/shaders/bloom/light.fs");
	auto spLightTexture = std::make_shared<Texture>();
	auto spLightRenderState = std::make_shared<RenderState>(spLightShader, spLightTexture);
	spLightRenderState->SetBackGround(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	spLightRenderState->EnableDepthTest(true);
	spLightRenderState->SetDrawMode(DRAW_MODE::ELEMENT_MODE);
	spLightRenderState->SetPrimitiveMode(PRIMITIVE_MODE::TRIANGLES_MODE);
	spLightRenderState->SetClearBuffer(false);
	spLightRenderState->SetHDRBuffer(spHDRBuffer);
	spLightRenderState->EnabelHDRBuffer(true);
	auto spLightEntity = std::make_shared<Entity>();
	auto spLightRenderPass = std::make_shared<RenderPass>(spLightEntity, spLightRenderState);
	std::vector<std::shared_ptr<Node>> vecLightNode;
	CreatLightNode(spLightRenderState, vecLightNode);
	for (auto i = 0; i < vecLightNode.size(); i++)
	{
		spLightEntity->AddGeometryNode(vecLightNode[i]);
	}
	spScene->AddRenderPass(spLightRenderPass);


	auto spBlurBuffer = std::make_shared<BlurBuffer>(SCR_WIDTH, SCR_HEIGHT);
	auto spBlurShader = std::make_shared<Shader>("../resources/shaders/bloom/blur.vs",
		"../resources/shaders/bloom/blur.fs");
	auto spBlurTexture = std::make_shared<Texture>();
	auto spBlurRenderState = std::make_shared<RenderState>(spBlurShader, spBlurTexture);
	spBlurRenderState->SetBackGround(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	spBlurRenderState->EnableDepthTest(true);
	spBlurRenderState->SetDrawMode(DRAW_MODE::ELEMENT_MODE);
	spBlurRenderState->SetPrimitiveMode(PRIMITIVE_MODE::TRIANGLES_MODE);
	spBlurRenderState->SetHDRBuffer(spHDRBuffer);
	spBlurRenderState->SetBlurBuffer(spBlurBuffer);
	spBlurRenderState->SetBlurFrame(10);
	spBlurRenderState->EnabelBlurBuffer(true);
	spBlurRenderState->SetClearBuffer(false);
	auto spBlurEntity = std::make_shared<Entity>();
	auto spBlurPass = std::make_shared<RenderPass>(spBlurEntity, spBlurRenderState);
	auto spNode = CreateBlurNode(spBlurRenderState);
	spBlurEntity->AddGeometryNode(spNode);
	for (int i = 0; i < 10; i++)
	{
		spScene->AddRenderPass(spBlurPass);
	}

	auto spBloomShader = std::make_shared<Shader>("../resources/shaders/bloom/bloom.vs",
		"../resources/shaders/bloom/bloom.fs");

	auto spColor = std::make_shared<TextureStruct>();
	spColor->eType = TextureType::DIFFUSE;
	spColor->uiID = spHDRBuffer->GetRendering();
	auto spBlur = std::make_shared<TextureStruct>();
	spBlur->eType = TextureType::DIFFUSE;
	spBlur->uiID = spBlurBuffer->GetRendering()[0];
	auto spBloomTexture = std::make_shared<Texture>();
	spBloomTexture->AddTexture(spColor);
	spBloomTexture->AddTexture(spBlur);
	auto spBloomRenderState = std::make_shared<RenderState>(spBloomShader, spBloomTexture);
	spBloomRenderState->SetBackGround(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	spBloomRenderState->EnableDepthTest(true);
	spBloomRenderState->SetDrawMode(DRAW_MODE::ELEMENT_MODE);
	spBloomRenderState->SetPrimitiveMode(PRIMITIVE_MODE::TRIANGLES_MODE);
	spBloomRenderState->EnabelUseExposure(true);
	spBloomRenderState->EnableUseBloom(true);
	spBloomRenderState->EnableUseGamma(true);
	auto spBloomEntity = std::make_shared<Entity>();
	spBloomEntity->AddGeometryNode(CreateBlurNode(spBloomRenderState));
	auto spBloomPass = std::make_shared<RenderPass>(spBloomEntity, spBloomRenderState);
	spScene->AddRenderPass(spBloomPass);

	spScene->Draw();
}

