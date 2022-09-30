#include "scene.h"
#include "gl_resource.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const std::string WINDOW_NAME = "LearnOpenGL";

void CreatCubeNode(std::vector<std::shared_ptr<Node>>& vecNode, std::shared_ptr<RenderState> spRenderState,bool bBoard)
{
	std::vector<Vertex> vecVertex
	{
		Vertex(glm::vec3(-0.5, -0.5, -0.5),glm::vec2(0.0, 0.0)),//0
		Vertex(glm::vec3(0.5, -0.5, -0.5),glm::vec2(1.0, 0.0)),//1
		Vertex(glm::vec3(0.5,  0.5, -0.5),glm::vec2(1.0, 1.0)),//2
		Vertex(glm::vec3(-0.5,  0.5, -0.5),glm::vec2(0.0, 1.0)),//3

		Vertex(glm::vec3(-0.5, -0.5, 0.5),glm::vec2(0.0, 0.0)),//4
		Vertex(glm::vec3(0.5, -0.5, 0.5),glm::vec2(1.0, 0.0)),//5
		Vertex(glm::vec3(0.5,  0.5, 0.5),glm::vec2(1.0, 1.0)),//6
		Vertex(glm::vec3(-0.5,  0.5, 0.5),glm::vec2(0.0, 1.0)),//7

		Vertex(glm::vec3(-0.5,  0.5,  0.5),glm::vec2(1.0, 0.0)),
		Vertex(glm::vec3(-0.5,  0.5, -0.5),glm::vec2(1.0, 1.0)),
		Vertex(glm::vec3(-0.5, -0.5, -0.5),glm::vec2(0.0, 1.0)),
		Vertex(glm::vec3(-0.5, -0.5,  0.5),glm::vec2(0.0, 0.0)),

		Vertex(glm::vec3(0.5,  0.5,  0.5),glm::vec2(1.0, 0.0)),
		Vertex(glm::vec3(0.5,  0.5, -0.5),glm::vec2(1.0, 1.0)),
		Vertex(glm::vec3(0.5, -0.5, -0.5),glm::vec2(0.0, 1.0)),
		Vertex(glm::vec3(0.5, -0.5,  0.5),glm::vec2(0.0, 0.0)),

		Vertex(glm::vec3(-0.5, -0.5, -0.5),glm::vec2(0.0, 1.0)),
		Vertex(glm::vec3(0.5, -0.5, -0.5),glm::vec2(1.0, 1.0)),
		Vertex(glm::vec3(0.5, -0.5,  0.5),glm::vec2(1.0, 0.0)),
		Vertex(glm::vec3(-0.5, -0.5,  0.5),glm::vec2(0.0, 0.0)),

		Vertex(glm::vec3(-0.5,  0.5, -0.5),glm::vec2(0.0, 1.0)),
		Vertex(glm::vec3(0.5,  0.5, -0.5),glm::vec2(1.0, 1.0)),
		Vertex(glm::vec3(0.5,  0.5,  0.5),glm::vec2(1.0, 0.0)),
		Vertex(glm::vec3(-0.5,  0.5,  0.5),glm::vec2(0.0, 0.0))
	};

	std::vector<unsigned int> vecIndex
	{
		0,1,2,2,3,0, 4,5,6,6,7,4, 8,9,10,10,11,8, 12,13,14,14,15,12, 16,17,18,18,19,16, 20,21,22,22,23,20
	};

	std::vector<glm::vec3> vecPosition
	{
		glm::vec3(-1.0f,0.0f,-1.0f),
		glm::vec3(2.0f,0.0f,0.0f)
	};

	for (int i = 0; i < 2; i++)
	{
		auto spTransform = std::make_shared<Transform>();
		spTransform->SetModelPan(vecPosition[i]);
		if (bBoard)
		{
			spTransform->SetModelScale(glm::vec3(1.1));
		}
		auto spNode = std::make_shared<GeometryNode>(vecVertex, vecIndex, spRenderState, spTransform);
		vecNode.push_back(spNode);
	}
}

void CreatPlaneNode(std::vector<std::shared_ptr<Node>>& vecNode, std::shared_ptr<RenderState> spRenderState)
{
	std::vector<Vertex> vecVertex
	{
		Vertex(glm::vec3( 5.0, -0.5, 5.0),glm::vec2(2.0, 0.0)),//0
		Vertex(glm::vec3(-5.0, -0.5, 5.0),glm::vec2(0.0, 0.0)),//1
		Vertex(glm::vec3(-5.0, -0.5, -5.0),glm::vec2(0.0, 2.0)),//2
		Vertex(glm::vec3( 5.0, -0.5, -5.0),glm::vec2(2.0, 2.0)),//3
	};

	std::vector<unsigned int> vecIndex
	{
		0,1,2,0,2,3
	};

	auto spTransform = std::make_shared<Transform>();
	auto spNode = std::make_shared<GeometryNode>(vecVertex, vecIndex, spRenderState, spTransform);
	vecNode.push_back(spNode);
}

int main()
{
	//≥ı ºªØglfw°¢glad
	auto spGLResource = std::make_shared<GLResource>();
	spGLResource->CreateGLFWWindow(SCR_WIDTH, SCR_HEIGHT, WINDOW_NAME);
	std::cout << "œ‘ø®–Õ∫≈£∫" << spGLResource->GetGPUVersion() << std::endl;

	auto spCamera = std::make_shared<Camera>(glm::vec3(0.f, 0.f, 3.f));
	auto spScene = std::make_shared<Scene>(spGLResource, spCamera);
	spScene->SetBackGround(glm::vec4(0.2f, 0.3f, 0.3f, 1.0f));

	auto spShader = std::make_shared<Shader>("../resources/shaders/depth/vertex.vs",
		"../resources/shaders/depth/fragment.fs");
	
	auto spPlaneTexture = std::make_shared<Texture>();
	spPlaneTexture->AddTexture("../resources/textures/metal.png", TextureType::DIFFUSE);

	auto spPlaneRenderState = std::make_shared<RenderState>(spShader, spPlaneTexture);
	spPlaneRenderState->EnableDepthTest(true);
	spPlaneRenderState->SetDrawMode(DRAW_MODE::ELEMENT_MODE);
	spPlaneRenderState->SetPrimitiveMode(PRIMITIVE_MODE::TRIANGLES_MODE);

	auto spPlaneEntity = std::make_shared<Entity>();
	auto spPalneRenderPass = std::make_shared<RenderPass>(spPlaneEntity, spPlaneRenderState);
	std::vector<std::shared_ptr<Node>> vecPlaneNode;
	CreatPlaneNode(vecPlaneNode, spPlaneRenderState);
	for (size_t i = 0; i < vecPlaneNode.size(); i++)
	{
		spPlaneEntity->AddGeometryNode(vecPlaneNode[i]);
	}

	auto spCubeTexture = std::make_shared<Texture>();
	spCubeTexture->AddTexture("../resources/textures/marble.jpg", TextureType::DIFFUSE);

	auto spCubeRenderState = std::make_shared<RenderState>(spShader, spCubeTexture);
	auto spCubeStencil = std::make_shared<Stencil>();
	spCubeStencil->WriteMask = 0xFF;
	spCubeStencil->SFunc = GL_ALWAYS;
	spCubeStencil->RefValue = 1;
	spCubeStencil->Mask = 0xFF;
	spCubeStencil->SFail = GL_KEEP;
	spCubeStencil->DpFail = GL_KEEP;
	spCubeStencil->DpPass = GL_REPLACE;
	spCubeRenderState->EnableStencil(true);
	spCubeRenderState->SetStencil(spCubeStencil);

	spCubeRenderState->EnableDepthTest(true);
	spCubeRenderState->SetDrawMode(DRAW_MODE::ELEMENT_MODE);
	spCubeRenderState->SetPrimitiveMode(PRIMITIVE_MODE::TRIANGLES_MODE);

	auto spCubeEntity = std::make_shared<Entity>();
	auto spCubeRenderPass = std::make_shared<RenderPass>(spCubeEntity, spCubeRenderState);
	std::vector<std::shared_ptr<Node>> vecCubeNode;
	CreatCubeNode(vecCubeNode, spCubeRenderState, false);
	for (size_t i = 0; i < vecCubeNode.size(); i++)
	{
		spCubeEntity->AddGeometryNode(vecCubeNode[i]);
	}

	auto spBoardShader = std::make_shared<Shader>("../resources/shaders/depth/vertex.vs",
		"../resources/shaders/depth/board.fs");
	auto spBoardCubeTexture = std::make_shared<Texture>();
	auto spBoardRenderState = std::make_shared<RenderState>(spBoardShader, spBoardCubeTexture);
	auto spBoardStencil = std::make_shared<Stencil>();
	spBoardStencil->WriteMask = 0x00;
	spBoardStencil->SFunc = GL_NOTEQUAL;
	spBoardStencil->RefValue = 1;
	spBoardStencil->Mask = 0xFF;
	spBoardStencil->SFail = GL_KEEP;
	spBoardStencil->DpFail = GL_KEEP;
	spBoardStencil->DpPass = GL_REPLACE;
	spBoardRenderState->EnableStencil(true);
	spBoardRenderState->SetStencil(spBoardStencil);
	spBoardRenderState->EnableDepthTest(false);
	spBoardRenderState->SetDrawMode(DRAW_MODE::ELEMENT_MODE);
	spBoardRenderState->SetPrimitiveMode(PRIMITIVE_MODE::TRIANGLES_MODE);
	auto spBoardEntity = std::make_shared<Entity>();
	auto spBoardRenderPass = std::make_shared<RenderPass>(spBoardEntity, spBoardRenderState);
	std::vector<std::shared_ptr<Node>> vecBoardNode;
	CreatCubeNode(vecBoardNode, spBoardRenderState, true);
	for (size_t i = 0; i < vecBoardNode.size(); i++)
	{
		spBoardEntity->AddGeometryNode(vecBoardNode[i]);
	}

	spScene->AddRenderPass(spPalneRenderPass);
	spScene->AddRenderPass(spCubeRenderPass);
	spScene->AddRenderPass(spBoardRenderPass);

	spScene->Draw();
}

