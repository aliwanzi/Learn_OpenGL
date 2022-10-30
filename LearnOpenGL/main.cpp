#include "scene.h"
#include "gl_resource.h"
#include <ctime>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const unsigned int SHADOW_WIDTH = 1024;
const unsigned int SHADOW_HEIGHT= 1024;
const float FNEAR(1.0F);
const float FFAR(25.0);

const std::string WINDOW_NAME = "LearnOpenGL";

std::vector<glm::vec3> objectPosition
{
	glm::vec3( 0.0,  1.5, 0.0),
	glm::vec3( 2.0,  0.0, 1.0),
	glm::vec3(-1.0,  0.0, 2.0)
};

std::vector<glm::vec3> objectPosition1
{
	glm::vec3(0.0),
	glm::vec3(4.0f,-3.5f,0.0),
	glm::vec3(2.0f,3.0f,1.0f),
	glm::vec3(-3.0f,-1.0f,0.0f),
	glm::vec3(-1.5f,1.0f,1.5f),
	glm::vec3(-1.5f,2.0f,-3.0f)
};

std::vector<glm::vec3> objectScale
{
	glm::vec3(0.5),
	glm::vec3(0.5),
	glm::vec3(0.25)
};

std::vector<glm::vec3> objectScale1
{
	glm::vec3(5.0f),
	glm::vec3(0.5f),
	glm::vec3(0.75f),
	glm::vec3(0.5f),
	glm::vec3(0.5f),
	glm::vec3(0.75)
};

std::vector<glm::vec3> objectRotateAxis
{
	glm::vec3(0.0, 0.0, 1.0),
	glm::vec3(0.0, 0.0, 1.0),
	glm::vec3(1.0, 0.0, 1.0)
};

std::vector<glm::vec3> objectRotateAxis1
{
	glm::vec3(0.0, 0.0, 1.0),
	glm::vec3(0.0, 0.0, 1.0),
	glm::vec3(0.0, 0.0, 1.0),
	glm::vec3(0.0, 0.0, 1.0),
	glm::vec3(0.0, 0.0, 1.0),
	glm::vec3(1.0, 0.0, 1.0)
};

std::vector<float> objectRotateAngle
{
	0.0,
	0.0,
	60.0
};

std::vector<float> objectRotateAngle1
{
	0.0,
	0.0,
	0.0,
	0.0,
	0.0,
	60.0
};

std::vector<glm::vec3> viewDiretion
{
	glm::vec3(1.0f,  0.0f,  0.0f),
	glm::vec3(-1.0f,  0.0f,  0.0f),
	glm::vec3(0.0f,  1.0f,  0.0f),
	glm::vec3(0.0f,  -1.0f,  0.0f),
	glm::vec3(0.0f,  0.0f,  1.0f),
	glm::vec3(0.0f,  0.0f,  -1.0f)
};

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

std::vector<Vertex> PlaneVertex
{
	Vertex(glm::vec3( 25.0f, -0.5f,  25.0f),glm::vec2(25.0f,  0.0f),glm::vec3(0.f,1.0f,0.f)),//0
	Vertex(glm::vec3(-25.0f, -0.5f,  25.0f),glm::vec2( 0.0f,  0.0f),glm::vec3(0.f,1.0f,0.f)),//0
	Vertex(glm::vec3(-25.0f, -0.5f, -25.0f),glm::vec2( 0.0f, 25.0f),glm::vec3(0.f,1.0f,0.f)),//0
	Vertex(glm::vec3( 25.0f, -0.5f, -25.0f),glm::vec2(25.0f, 25.0f),glm::vec3(0.f,1.0f,0.f)),//0
};

std::vector<unsigned int> PlaneIndex
{
	0,1,2,0,2,3
};

void CreatBoxNode(std::shared_ptr<RenderState> spRenderState,
	std::vector<std::shared_ptr<Node>>& vecBoxNode,bool depth)
{
	for (int i = 0; i < objectPosition.size(); i++)
	{
		auto spTransform = std::make_shared<Transform>();
		spTransform->SetModelPan(objectPosition[i]);
		spTransform->SetModelScale(objectScale[i]);
		spTransform->SetModelRotAngle(objectRotateAngle[i]);
		spTransform->SetModelRotAixs(objectRotateAxis[i]);

		auto spNode = std::make_shared<GeometryNode>(vecVertex, vecIndex, spRenderState, spTransform);
		vecBoxNode.push_back(spNode);
	}
	if (!depth)
	{
		glm::vec3 lightPos(-2.0f, 4.0f, -1.0f);
		std::vector<std::shared_ptr<Light>> vecLights;

		auto spPointLight = std::make_shared<PointLight>();
		spPointLight->SetLightType(LightType::POINT_LIGHT);

		spPointLight->SetLightPosition(lightPos);
		spPointLight->SetAmbient(glm::vec3(0.0f));
		spPointLight->SetDiffuse(glm::vec3(1.0f));
		spPointLight->SetSpecular(glm::vec3(1.0f), 64);
		vecLights.emplace_back(spPointLight);
		spRenderState->SetLights(vecLights);
	}
}

void CreatBoxNode1(std::shared_ptr<RenderState> spRenderState,
	std::vector<std::shared_ptr<Node>>& vecBoxNode)
{
	for (int i = 0; i < objectPosition1.size(); i++)
	{
		auto spTransform = std::make_shared<Transform>();
		spTransform->SetModelPan(objectPosition1[i]);
		spTransform->SetModelScale(objectScale1[i]);
		spTransform->SetModelRotAngle(objectRotateAngle1[i]);
		spTransform->SetModelRotAixs(objectRotateAxis1[i]);

		auto spNode = std::make_shared<GeometryNode>(vecVertex, vecIndex, spRenderState, spTransform);
		if (i == 0)
		{
			spNode->SetUniformReverseNormal(true);
		}
		else
		{
			spNode->SetUniformCull(true);
		}
		vecBoxNode.push_back(spNode);
	}

	std::vector<std::shared_ptr<Light>> vecLights;
	glm::vec3 lightPos(0.0f);

	auto spPointLight = std::make_shared<PointLight>();
	spPointLight->SetLightType(LightType::POINT_LIGHT);

	spPointLight->SetLightPosition(lightPos);
	spPointLight->SetAmbient(glm::vec3(0.0f));
	spPointLight->SetDiffuse(glm::vec3(1.0f));
	spPointLight->SetSpecular(glm::vec3(1.0f), 64);
	vecLights.emplace_back(spPointLight);
	spRenderState->SetLights(vecLights);
}

std::shared_ptr<Node> CreatWoodNode(std::shared_ptr<RenderState> spRenderState, bool depth)
{
	auto spTransform = std::make_shared<Transform>();
	if (!depth)
	{
		std::vector<std::shared_ptr<Light>> vecLights;
		glm::vec3 lightPos(-2.0f, 4.0f, -1.0f);

		auto spPointLight = std::make_shared<PointLight>();
		spPointLight->SetLightType(LightType::POINT_LIGHT);

		spPointLight->SetLightPosition(lightPos);
		spPointLight->SetAmbient(glm::vec3(0.0f));
		spPointLight->SetDiffuse(glm::vec3(1.0f));
		spPointLight->SetSpecular(glm::vec3(1.0f), 64);
		vecLights.emplace_back(spPointLight);
		spRenderState->SetLights(vecLights);
	}
	return std::make_shared<GeometryNode>(PlaneVertex, PlaneIndex, spRenderState, spTransform);
}

std::shared_ptr<Node> CreateQuardNode(std::shared_ptr<RenderState> spRenderState)
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

void CreatLightNode(std::shared_ptr<RenderState> spRenderState,
	std::vector<std::shared_ptr<Node>>& vecLightNode)
{
	std::vector<std::shared_ptr<Light>> vecLights;
	glm::vec3 lightPos(-2.0f, 4.0f, -1.0f);

	auto spTransform = std::make_shared<Transform>();
	spTransform->SetModelPan(lightPos);
	spTransform->SetModelScale(glm::vec3(0.25f));

	auto spNode = std::make_shared<GeometryNode>(vecVertex, vecIndex, spRenderState, spTransform);
	spNode->SetUniformColor(glm::vec3(1.0f));
	vecLightNode.push_back(spNode);
}

void CreateLightSpaceMatric(std::shared_ptr<RenderState> spRenderState)
{
	float fnear(1.0), ffar(7.5);
	glm::vec3 lightPos(-2.0f, 4.0f, -1.0f);
	glm::mat4 lightProjection(glm::mat4(1.0)), lightView(glm::mat4(1.0)), lightSpaceMatrix(glm::mat4(1.0));
	lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, fnear, ffar);
	lightView = glm::lookAt(lightPos, glm::vec3(0.f), glm::vec3(0.0, 1.0, 0.0));
	lightSpaceMatrix = lightProjection * lightView;
	spRenderState->EnableLightSpace(true);
	spRenderState->SetLightSpaceMatrix(lightSpaceMatrix);
}

void CreateLightSpaceMatric1(std::shared_ptr<RenderState> spRenderState)
{
	glm::vec3 lightPos(0.f);
	glm::mat4 shadowProj = glm::perspective(glm::radians(90.f), (float)SHADOW_WIDTH / (float)SHADOW_HEIGHT, FNEAR, FFAR);
	std::vector<glm::mat4> shadowTransforms;
	shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
	shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
	shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
	shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)));
	shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
	shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));

	spRenderState->EnabelCubeLightSpace(true);
	spRenderState->SetCubeLightSpaceMatrix(shadowTransforms);
}

#define CASE1
//#define CASE2

int main()
{
	//≥ı ºªØglfw°¢glad
	auto spGLResource = std::make_shared<GLResource>();
	spGLResource->CreateGLFWWindow(SCR_WIDTH, SCR_HEIGHT, WINDOW_NAME);
	std::cout << "œ‘ø®–Õ∫≈£∫" << spGLResource->GetGPUVersion() << std::endl;

	auto spCamera = std::make_shared<Camera>(glm::vec3(0.f, 0.f, 3.f));
	auto spScene = std::make_shared<Scene>(spGLResource, spCamera);

#ifdef CASE1
	auto spDepthBuffer = std::make_shared<DepthBuffer>(SHADOW_WIDTH, SHADOW_HEIGHT, false);
	spDepthBuffer->SetOriWidthAndHeight(SCR_WIDTH, SCR_HEIGHT);
	auto spDepthShader = std::make_shared<Shader>("../resources/shaders/shadowmapping/shadow_mapping/shadow_depth.vs",
		"../resources/shaders/shadowmapping/shadow_mapping/shadow_depth.fs");
	auto spDepthTexture = std::make_shared<Texture>();
	auto spDepthRenderState = std::make_shared<RenderState>(spDepthShader, spDepthTexture);
	spDepthRenderState->SetBackGround(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	spDepthRenderState->EnableDepthTest(true);
	spDepthRenderState->SetDrawMode(DRAW_MODE::ELEMENT_MODE);
	spDepthRenderState->SetPrimitiveMode(PRIMITIVE_MODE::TRIANGLES_MODE);
	spDepthRenderState->EnableDepthMappingBuffer(true);
	spDepthRenderState->SetDepthMappingBuffer(spDepthBuffer);
	//spDepthRenderState->EnableCullFace(true);
	auto spCullface = std::make_shared<CullFace>();
	spCullface->FaceMode = GL_FRONT;
	spCullface->FaceOri = GL_CW;
	spDepthRenderState->SetCullFace(spCullface);
	CreateLightSpaceMatric(spDepthRenderState);

	auto spDepthEntity = std::make_shared<Entity>();
	auto spDepthRenderPass = std::make_shared<RenderPass>(spDepthEntity, spDepthRenderState);
	std::vector<std::shared_ptr<Node>> vecDepthNode;
	CreatBoxNode(spDepthRenderState, vecDepthNode, true);
	for (auto i = 0; i < vecDepthNode.size(); i++)
	{
		spDepthEntity->AddGeometryNode(vecDepthNode[i]);
	}
	auto spDepthNode = CreatWoodNode(spDepthRenderState, true);
	spDepthEntity->AddGeometryNode(spDepthNode);
	spScene->AddRenderPass(spDepthRenderPass);

	auto spRenderShader = std::make_shared<Shader>("../resources/shaders/shadowmapping/shadow_mapping/shadow_mapping.vs",
		"../resources/shaders/shadowmapping/shadow_mapping/shadow_mapping.fs");
	auto spTexStruct = std::make_shared<TextureStruct>();
	spTexStruct->eType = TextureType::DIFFUSE;
	spTexStruct->uiID = spDepthBuffer->GetDepthMap();
	auto spTexture = std::make_shared<Texture>();
	spTexture->AddTexture("../resources/textures/wood.png", TextureType::DIFFUSE, true, true);
	spTexture->AddTexture(spTexStruct);
	auto spRenderState = std::make_shared<RenderState>(spRenderShader, spTexture);
	spRenderState->SetBackGround(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	spRenderState->EnableDepthTest(true);
	spRenderState->SetDrawMode(DRAW_MODE::ELEMENT_MODE);
	spRenderState->SetPrimitiveMode(PRIMITIVE_MODE::TRIANGLES_MODE);
	spRenderState->EnableUseShadow(true);
	CreateLightSpaceMatric(spRenderState);

	auto spRenderEntity = std::make_shared<Entity>();
	auto spRenderPass = std::make_shared<RenderPass>(spRenderEntity, spRenderState);
	std::vector<std::shared_ptr<Node>> vecBoxNode;
	CreatBoxNode(spRenderState, vecBoxNode, false);
	for (auto i = 0; i < vecBoxNode.size(); i++)
	{
		spRenderEntity->AddGeometryNode(vecBoxNode[i]);
	}
	auto spWoodNode = CreatWoodNode(spRenderState, false);
	spRenderEntity->AddGeometryNode(spWoodNode);
	spScene->AddRenderPass(spRenderPass);

	auto spLightShader = std::make_shared<Shader>("../resources/shaders/bloom/vertex.vs",
		"../resources/shaders/bloom/light.fs");
	auto spLightTexture = std::make_shared<Texture>();
	auto spLightRenderState = std::make_shared<RenderState>(spLightShader, spLightTexture);
	spLightRenderState->SetBackGround(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	spLightRenderState->EnableDepthTest(true);
	spLightRenderState->SetDrawMode(DRAW_MODE::ELEMENT_MODE);
	spLightRenderState->SetPrimitiveMode(PRIMITIVE_MODE::TRIANGLES_MODE);
	spLightRenderState->SetClearBuffer(false);
	CreateLightSpaceMatric(spLightRenderState);
	auto spLightEntity = std::make_shared<Entity>();
	auto spLightRenderPass = std::make_shared<RenderPass>(spLightEntity, spLightRenderState);
	std::vector<std::shared_ptr<Node>> vecLightNode;
	CreatLightNode(spLightRenderState, vecLightNode);
	for (auto i = 0; i < vecLightNode.size(); i++)
	{
		spLightEntity->AddGeometryNode(vecLightNode[i]);
	}
	//spScene->AddRenderPass(spLightRenderPass);

	auto spQuadShader = std::make_shared<Shader>("../resources/shaders/shadowmapping/shadow_mapping/quad.vs",
		"../resources/shaders/shadowmapping/shadow_mapping/quad.fs");
	auto spTextureStruct = std::make_shared<TextureStruct>();
	spTextureStruct->eType = TextureType::DIFFUSE;
	spTextureStruct->uiID = spDepthBuffer->GetDepthMap();
	auto spQuadTexture = std::make_shared<Texture>();
	spQuadTexture->AddTexture(spTextureStruct);
	auto spQuadRenderState = std::make_shared<RenderState>(spQuadShader, spQuadTexture);
	spQuadRenderState->SetBackGround(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	spQuadRenderState->EnableDepthTest(true);
	spQuadRenderState->SetDrawMode(DRAW_MODE::ELEMENT_MODE);
	spQuadRenderState->SetPrimitiveMode(PRIMITIVE_MODE::TRIANGLES_MODE);

	auto spQuadNode = CreateQuardNode(spQuadRenderState);
	auto spQuadEntity = std::make_shared<Entity>();
	auto spQuadRenderPass = std::make_shared<RenderPass>(spQuadEntity, spQuadRenderState);
	spQuadEntity->AddGeometryNode(spQuadNode);
	spScene->AddRenderPass(spQuadRenderPass);
#endif // CASE1

#ifdef CASE2
	auto spDepthShader = std::make_shared<Shader>("../resources/shaders/shadowmapping/point_shadow_mapping/point_shadow_depth.vs",
		"../resources/shaders/shadowmapping/point_shadow_mapping/point_shadow_depth.fs",
		"../resources/shaders/shadowmapping/point_shadow_mapping/point_shadow_depth.gs");
	auto spDepthTexture = std::make_shared<Texture>();
	auto spDepthRenderState = std::make_shared<RenderState>(spDepthShader, spDepthTexture);
	spDepthRenderState->SetBackGround(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	spDepthRenderState->EnableDepthTest(true);
	spDepthRenderState->SetDrawMode(DRAW_MODE::ELEMENT_MODE);
	spDepthRenderState->SetPrimitiveMode(PRIMITIVE_MODE::TRIANGLES_MODE);
	spDepthRenderState->EnabelNearAndFar(true);
	spDepthRenderState->SetNearAndFar(FNEAR, FFAR);

	spDepthRenderState->EnableDepthMappingBuffer(true);
	auto spDepthBuffer = std::make_shared<DepthBuffer>(SHADOW_WIDTH, SHADOW_HEIGHT, true);
	spDepthBuffer->SetOriWidthAndHeight(SCR_WIDTH, SCR_HEIGHT);
	spDepthRenderState->SetDepthMappingBuffer(spDepthBuffer);
	CreateLightSpaceMatric1(spDepthRenderState);

	auto spDepthEntity = std::make_shared<Entity>();
	auto spDepthRenderPass = std::make_shared<RenderPass>(spDepthEntity, spDepthRenderState);
	std::vector<std::shared_ptr<Node>> vecDepthNode;
	CreatBoxNode1(spDepthRenderState, vecDepthNode);
	for (auto i = 0; i < vecDepthNode.size(); i++)
	{
		spDepthEntity->AddGeometryNode(vecDepthNode[i]);
	}
	spScene->AddRenderPass(spDepthRenderPass);

	auto spRenderShader = std::make_shared<Shader>("../resources/shaders/shadowmapping/point_shadow_mapping/point_shadow_mapping.vs",
		"../resources/shaders/shadowmapping//point_shadow_mapping/point_shadow_mapping.fs");
	auto spTexStruct = std::make_shared<TextureStruct>();
	spTexStruct->eType = TextureType::CUBEMAP;
	spTexStruct->uiID = spDepthBuffer->GetDepthMap();
	auto spTexture = std::make_shared<Texture>();
	spTexture->AddTexture("../resources/textures/wood.png", TextureType::DIFFUSE, true, true);
	spTexture->AddTexture(spTexStruct);
	auto spRenderState = std::make_shared<RenderState>(spRenderShader, spTexture);
	spRenderState->SetBackGround(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	spRenderState->EnableDepthTest(true);
	spRenderState->SetDrawMode(DRAW_MODE::ELEMENT_MODE);
	spRenderState->SetPrimitiveMode(PRIMITIVE_MODE::TRIANGLES_MODE);
	spRenderState->EnabelNearAndFar(true);
	spRenderState->SetNearAndFar(FNEAR, FFAR);
	spRenderState->EnableUseShadow(true);

	auto spRenderEntity = std::make_shared<Entity>();
	auto spRenderPass = std::make_shared<RenderPass>(spRenderEntity, spRenderState);
	std::vector<std::shared_ptr<Node>> vecBoxNode;
	CreatBoxNode1(spRenderState, vecBoxNode);
	for (auto i = 0; i < vecBoxNode.size(); i++)
	{
		spRenderEntity->AddGeometryNode(vecBoxNode[i]);
	}
	spScene->AddRenderPass(spRenderPass);

#endif // CASE2

	spScene->Draw();
}

