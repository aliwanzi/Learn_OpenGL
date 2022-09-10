#include "scene.h"
#include "gl_resource.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const std::string WINDOW_NAME = "LearnOpenGL";

void CreateTriangleNode(std::shared_ptr<Node>&spNode, std::shared_ptr<RenderState> spRenderState)
{
	std::vector<Vertex> vecVertex
	{
		Vertex(glm::vec3(0.5,0.5,0.0)),
		Vertex(glm::vec3(0.5, -0.5, 0.0)),
		Vertex(glm::vec3(-0.5, -0.5, 0.0))
	};

	std::vector<unsigned int> vecIndex
	{
		0,1,2
	};

	auto spTransform = std::make_shared<Transform>();

	spNode = std::make_shared<GeometryNode>(vecVertex, vecIndex, spRenderState, spTransform);
}

void CreatGeometryNode(std::vector<std::shared_ptr<Node>>& vecNode, std::shared_ptr<RenderState> spRenderState)
{
	std::vector<Vertex> vecVertex
	{
		Vertex(glm::vec3(0.5,0.5,0.0),
			glm::vec2(1.0,1.0),
			glm::vec3(1.0,0.0,0.0)),
		Vertex(glm::vec3(0.5, -0.5, 0.0),
			glm::vec2(1.0, 0.0),
			glm::vec3(0.0, 1.0, 0.0)),
		Vertex(glm::vec3(-0.5, -0.5, 0.0),
			glm::vec2(0.0, 0.0),
			glm::vec3(0.0, 0.0, 1.0)),
		Vertex(glm::vec3(-0.5, 0.5, 0.0),
			glm::vec2(0.0, 1.0),
			glm::vec3(1.0, 1.0, 0.0))
	};

	std::vector<unsigned int> vecIndex
	{
		0,1,3,1,2,3
	};

	auto spTransform1 = std::make_shared<Transform>();
	spTransform1->SetModelPan(glm::vec3(0.5f, -0.5f, 0.0f));
	spTransform1->SetModelRotAixs(glm::vec3(0.0, 0.0, 1.0));
	spTransform1->SetModelRotUseTime();

	auto spTransform2 = std::make_shared<Transform>();
	spTransform2->SetModelPan(glm::vec3(-0.5f, 0.5f, 0.0f));
	spTransform2->SetModelScalUseTime();

	vecNode.push_back(std::make_shared<GeometryNode>(vecVertex, vecIndex, spRenderState, spTransform1));
	vecNode.push_back(std::make_shared<GeometryNode>(vecVertex, vecIndex, spRenderState, spTransform2));
}

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

//#define CASE1
//#define CASE2
#define CASE3

int main()
{
	//初始化glfw、glad
	auto spGLResource = std::make_shared<GLResource>();
	spGLResource->CreateGLFWWindow(SCR_WIDTH, SCR_HEIGHT, WINDOW_NAME);
	std::cout << "显卡型号：" << spGLResource->GetGPUVersion() << std::endl;

	auto spCamera = std::make_shared<Camera>(glm::vec3(0.f, 0.f, 3.f));
	auto spScene = std::make_shared<Scene>(spGLResource, spCamera);
	auto spEntity = std::make_shared<Entity>();

#ifdef CASE1
	//绘制一个三角形分别使用三种细分曲面评估着色器
	auto spShader = std::make_shared<Shader>
		("../resources/shaders/tessellation/vertex.vs", "../resources/shaders/tessellation/fragment.fs",
			"../resources/shaders/tessellation/triangle.tcs","../resources/shaders/tessellation/triangle.tes");
	auto spRenderState = std::make_shared<RenderState>(spShader);
	auto spNode = std::make_shared<Node>();
	CreateTriangleNode(spNode, spRenderState);

	spEntity->AddNode(spNode);

	spRenderState->SetBackGround(glm::vec4(0.2, 0.3, 0.3, 1.0));
	spRenderState->SetDrawMode(DRAW_MODE::ELEMENT_MODE);
	spRenderState->SetPrimitiveMode(PRIMITIVE_MODE::PATCH_MODE);
	spRenderState->SetPolygonMode(POLYGON_MODE::LINE_MODE);
	spRenderState->SetPatchVertices(3);

#endif // CASE1

#ifdef CASE2
	auto spShader = std::make_shared<Shader>("../resources/shaders/geometry/vertex.vs", "../resources/shaders/geometry/fragment.fs",
		"","", "../resources/shaders/geometry/geometry.gs");
	auto spRenderState = std::make_shared<RenderState>(spShader);
	spRenderState->SetBackGround(glm::vec4(0.2, 0.3, 0.3, 1.0));
	spRenderState->SetDrawMode(DRAW_MODE::ARRAY_MODE);
	spRenderState->SetPrimitiveMode(PRIMITIVE_MODE::POINTS_MODE);
	std::vector<std::shared_ptr<Node>> vecNode;
	CreatGeometryNode(vecNode, spRenderState);

	for (size_t i = 0; i < vecNode.size(); i++)
	{
		spEntity->AddNode(vecNode[i]);
	}

#endif // CASE2

#ifdef CASE3
	//添加10个立方体笑脸盒子
	auto spShader = std::make_shared<Shader>("../resources/shaders/texture/vertex.vs", "../resources/shaders/texture/fragment.fs");
	auto spTexture = std::make_shared<Texture>();
	spTexture->AddTexture("../resources/textures/container.jpg", DIFFUSE);
	spTexture->AddTexture("../resources/textures/awesomeface.png", DIFFUSE, true);

	auto spRenderState = std::make_shared<RenderState>(spShader, spTexture);
	spRenderState->SetBlend(0.5);
	spRenderState->SetDepthTest(true);
	spRenderState->SetBackGround(glm::vec4(0.2, 0.3, 0.3, 1.0));
	spRenderState->SetDrawMode(DRAW_MODE::ELEMENT_MODE);
	spRenderState->SetPrimitiveMode(PRIMITIVE_MODE::TRIANGLES_MODE);
	std::vector<std::shared_ptr<Node>> vecNode;
	CreatBoxNode(vecNode, spRenderState);
	for (size_t i = 0; i < vecNode.size(); i++)
	{
		spEntity->AddNode(vecNode[i]);
	}
#endif // CASE3

	auto spRenderPass = std::make_shared<RenderPass>(spEntity, spRenderState);
	spScene->AddRenderPass(spRenderPass);

	spScene->Draw();
}

