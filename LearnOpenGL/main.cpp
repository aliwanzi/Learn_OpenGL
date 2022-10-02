#include "scene.h"
#include "gl_resource.h"
#include <map>

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

enum NodeType
{
	Red = 0,
	Green,
	Blue,
	Yellow
};

std::shared_ptr<Node> CreatColorNode(std::shared_ptr<RenderState> spRenderState,NodeType nodeType)
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
		glm::vec3(-0.75f, 0.75f, 0.0f),
		glm::vec3(0.75f, 0.75f, 0.0f),
		glm::vec3(-0.75f, -0.75f, 0.0f),
		glm::vec3(0.75f, -0.75f, 0.0f)
	};

	auto spTransform = std::make_shared<Transform>();
	switch (nodeType)
	{
	case Red:
		spTransform->SetModelPan(vecPosition[0]);
		break;
	case Green:
		spTransform->SetModelPan(vecPosition[1]);
		break;
	case Blue:
		spTransform->SetModelPan(vecPosition[2]);
		break;
	case Yellow:
		spTransform->SetModelPan(vecPosition[3]);
		break;
	default:
		break;
	}

	return std::make_shared<GeometryNode>(vecVertex, vecIndex, spRenderState, spTransform);
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

void CreatScreenNode(std::vector<std::shared_ptr<Node>>& vecNode, std::shared_ptr<RenderState> spRenderState)
{
	std::vector<Vertex> vecVertex
	{
		Vertex(glm::vec3(-1.0, 1.0, 0.0),glm::vec2(0.0, 1.0)),//0
		Vertex(glm::vec3(-1.0, -1.0, 0.0),glm::vec2(0.0, 0.0)),//1
		Vertex(glm::vec3(1.0, -1.0, 0.0),glm::vec2(1.0, 0.0)),//2
		Vertex(glm::vec3(1.0, 1.0, 0.0),glm::vec2(1.0, 1.0)),//3
	};

	std::vector<unsigned int> vecIndex
	{
		0,1,2,0,2,3
	};

	auto spTransform = std::make_shared<Transform>();
	auto spNode = std::make_shared<GeometryNode>(vecVertex, vecIndex, spRenderState, spTransform);
	vecNode.push_back(spNode);
}

void CreateTriangleNode(std::shared_ptr<Node>& spNode, std::shared_ptr<RenderState> spRenderState)
{
	std::vector<Vertex> vecVertex
	{
		Vertex(glm::vec3(-0.8, 0.8, 0.0),glm::vec2(0.0, 1.0)),//0
		Vertex(glm::vec3(-0.8, -0.8, 0.0),glm::vec2(0.0, 0.0)),//1
		Vertex(glm::vec3(0.8, -0.8, 0.0),glm::vec2(1.0, 0.0)),//2
		Vertex(glm::vec3(0.8, 0.8, 0.0),glm::vec2(1.0, 1.0)),//3
	};

	std::vector<unsigned int> vecIndex
	{
		0,1,2,0,2,3
	};

	auto spTransform = std::make_shared<Transform>();

	spNode = std::make_shared<GeometryNode>(vecVertex, vecIndex, spRenderState, spTransform);
}

void CreateRenderPass(
	std::shared_ptr<Shader> spShader, std::shared_ptr<UniformBuffer> spUniformBuffer, std::shared_ptr<Scene> spScene,NodeType nodetype)
{
	auto spRenderState = std::make_shared<RenderState>(spShader);
	spRenderState->EnableDepthTest(true);
	spRenderState->SetDrawMode(DRAW_MODE::ELEMENT_MODE);
	spRenderState->SetPrimitiveMode(PRIMITIVE_MODE::TRIANGLES_MODE);
	spRenderState->SetUniformBuffer(spUniformBuffer);
	spRenderState->EnableUniformBuffer(true);
	if (nodetype != NodeType::Red)
	{
		spRenderState->SetClearBuffer(false);
		spRenderState->UpdateUniformBuffer(false);
	}
	auto spEntity = std::make_shared<Entity>();
	auto spRenderPass = std::make_shared<RenderPass>(spEntity, spRenderState);
	auto spRedNode = CreatColorNode(spRenderState, nodetype);
	spEntity->AddGeometryNode(spRedNode);
	spScene->AddRenderPass(spRenderPass);
}

#define CASE1
//#define CASE2
//#define CASE3

int main()
{
	//≥ı ºªØglfw°¢glad
	auto spGLResource = std::make_shared<GLResource>();
	spGLResource->CreateGLFWWindow(SCR_WIDTH, SCR_HEIGHT, WINDOW_NAME);
	std::cout << "œ‘ø®–Õ∫≈£∫" << spGLResource->GetGPUVersion() << std::endl;

	auto spCamera = std::make_shared<Camera>(glm::vec3(0.f, 0.f, 3.f));
	auto spScene = std::make_shared<Scene>(spGLResource, spCamera);

#ifdef CASE1
	auto spFrameBufferInfo = std::make_shared<FrameBufferInfo>();
	spFrameBufferInfo->Width = SCR_WIDTH;
	spFrameBufferInfo->Height = SCR_HEIGHT;
	auto spFrameBuffer = std::make_shared<FrameBuffer>(spFrameBufferInfo);

	auto spShader = std::make_shared<Shader>("../resources/shaders/depth/vertex.vs",
		"../resources/shaders/depth/fragment.fs");
	
	auto spPlaneTexture = std::make_shared<Texture>();
	spPlaneTexture->AddTexture("../resources/textures/metal.png", TextureType::DIFFUSE);

	auto spPlaneRenderState = std::make_shared<RenderState>(spShader, spPlaneTexture);
	spPlaneRenderState->SetBackGround(glm::vec4(0.2f, 0.3f, 0.3f, 1.0f));
	spPlaneRenderState->EnableDepthTest(true);
	spPlaneRenderState->SetDrawMode(DRAW_MODE::ELEMENT_MODE);
	spPlaneRenderState->SetPrimitiveMode(PRIMITIVE_MODE::TRIANGLES_MODE);

	spPlaneRenderState->EnableFrameBuffer(true);
	spPlaneRenderState->SetFrameBuffer(spFrameBuffer);

	auto spPlaneEntity = std::make_shared<Entity>();
	auto spPalneRenderPass = std::make_shared<RenderPass>(spPlaneEntity, spPlaneRenderState);
	std::vector<std::shared_ptr<Node>> vecPlaneNode;
	CreatPlaneNode(vecPlaneNode, spPlaneRenderState);
	for (size_t i = 0; i < vecPlaneNode.size(); i++)
	{
		spPlaneEntity->AddGeometryNode(vecPlaneNode[i]);
	}

	auto spCubeTexture = std::make_shared<Texture>();
	spCubeTexture->AddTexture("../resources/textures/container.jpg", TextureType::DIFFUSE);

	auto spCubeRenderState = std::make_shared<RenderState>(spShader, spCubeTexture);
	spCubeRenderState->EnableDepthTest(true);
	spCubeRenderState->SetDrawMode(DRAW_MODE::ELEMENT_MODE);
	spCubeRenderState->SetPrimitiveMode(PRIMITIVE_MODE::TRIANGLES_MODE);
	spCubeRenderState->EnableFrameBuffer(true);
	spCubeRenderState->SetFrameBuffer(spFrameBuffer);
	spCubeRenderState->SetClearBuffer(false);

	auto spCubeEntity = std::make_shared<Entity>();
	auto spCubeRenderPass = std::make_shared<RenderPass>(spCubeEntity, spCubeRenderState);
	std::vector<std::shared_ptr<Node>> vecCubeNode;
	CreatCubeNode(vecCubeNode, spCubeRenderState, false);
	for (size_t i = 0; i < vecCubeNode.size(); i++)
	{
		spCubeEntity->AddGeometryNode(vecCubeNode[i]);
	}

	auto spScreenTexture = std::make_shared<Texture>();
	TextureStruct texture;
	texture.uiID = spFrameBuffer->GetColorAttachment();
	texture.eType = TextureType::DIFFUSE;
	texture.sPath = "";
	spScreenTexture->AddTexture(texture);

	auto spFrameShader = std::make_shared<Shader>("../resources/shaders/framebuffer/vertex.vs",
	"../resources/shaders/framebuffer/fragment.fs");
	auto spScreenRenderState = std::make_shared<RenderState>(spFrameShader, spScreenTexture);
	spScreenRenderState->SetDrawMode(DRAW_MODE::ELEMENT_MODE);
	spScreenRenderState->SetPrimitiveMode(PRIMITIVE_MODE::TRIANGLES_MODE);

	auto spScreenEntity = std::make_shared<Entity>();
	auto spScreenRenderPass = std::make_shared<RenderPass>(spScreenEntity, spScreenRenderState);
	std::vector<std::shared_ptr<Node>> vecScreenNode;
	CreatScreenNode(vecScreenNode, spScreenRenderState);
	for (size_t i = 0; i < vecScreenNode.size(); i++)
	{
		spScreenEntity->AddGeometryNode(vecScreenNode[i]);
	}

	spScene->AddRenderPass(spPalneRenderPass);
	spScene->AddRenderPass(spCubeRenderPass);
	spScene->AddRenderPass(spScreenRenderPass);

#endif // CASE1

#ifdef CASE2
	auto spTexture = std::make_shared<Texture>();
	spTexture->AddTexture("../resources/textures/container.jpg", TextureType::DIFFUSE);
	spTexture->AddTexture("../resources/textures/awesomeface.png", TextureType::DIFFUSE);

	auto spShader = std::make_shared<Shader>
		("../resources/shaders/tessellation/vertex.vs", "../resources/shaders/tessellation/fragment.fs");
	auto spRenderState = std::make_shared<RenderState>(spShader, spTexture);
	auto spNode = std::make_shared<Node>();
	CreateTriangleNode(spNode, spRenderState);

	auto spEntity = std::make_shared<Entity>();
	spEntity->AddGeometryNode(spNode);

	spRenderState->SetBackGround(glm::vec4(0.2, 0.3, 0.3, 1.0));
	spRenderState->SetDrawMode(DRAW_MODE::ELEMENT_MODE);
	spRenderState->SetPrimitiveMode(PRIMITIVE_MODE::TRIANGLES_MODE);
	//spRenderState->SetPolygonMode(POLYGON_MODE::POINT_MODE);
	//spRenderState->EnableCullFace(true);
	auto spRenderPass = std::make_shared<RenderPass>(spEntity, spRenderState);
	spScene->AddRenderPass(spRenderPass);
#endif // CASE2

#ifdef CASE3
	auto spRedShader = std::make_shared<Shader>
		("../resources/shaders/uniformbuffer/vertex.vs", "../resources/shaders/uniformbuffer/red.fs");
	spRedShader->SetUniformBlock("Matrices",2);
	auto spGreenShader = std::make_shared<Shader>
		("../resources/shaders/uniformbuffer/vertex.vs", "../resources/shaders/uniformbuffer/green.fs");
	spGreenShader->SetUniformBlock("Matrices",2);
	auto spBlueShader = std::make_shared<Shader>
		("../resources/shaders/uniformbuffer/vertex.vs", "../resources/shaders/uniformbuffer/blue.fs");
	spBlueShader->SetUniformBlock("Matrices",2);
	auto spYellowShader = std::make_shared<Shader>
		("../resources/shaders/uniformbuffer/vertex.vs", "../resources/shaders/uniformbuffer/yellow.fs");
	spYellowShader->SetUniformBlock("Matrices",2);

	auto spUniformBuffer = std::make_shared<UniformBuffer>(2, sizeof(glm::mat4), 2);
	CreateRenderPass(spRedShader, spUniformBuffer, spScene, NodeType::Red);
	CreateRenderPass(spGreenShader, spUniformBuffer, spScene, NodeType::Green);
	CreateRenderPass(spBlueShader, spUniformBuffer, spScene, NodeType::Blue);
	CreateRenderPass(spYellowShader, spUniformBuffer, spScene, NodeType::Yellow);

#endif // CASE3

	spScene->Draw();
}

