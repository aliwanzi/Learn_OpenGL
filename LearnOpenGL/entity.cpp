#include "entity.h"

Entity::Entity():m_spParent(nullptr)
{
}

Entity::~Entity()
{

}

void Entity::AddGeometryNode(std::shared_ptr<Node> spNode)
{
	m_listNode.push_back(spNode);
}

void Entity::SetInstanceOffset(const std::vector<glm::vec2>& vecOffset)
{
	for (auto& child : m_listNode)
	{
		child->SetInstanceOffset(vecOffset);
	}
}

void Entity::SetInstanceOffset(const std::vector<glm::mat4>& vecOffset)
{
	for (auto& child : m_listNode)
	{
		child->SetInstanceOffset(vecOffset);
	}
}

void Entity::SetTransform(std::shared_ptr<Transform> spTransform)
{
	for (auto& child : m_listNode)
	{
		child->SetTransform(spTransform);
	}
}

void Entity::DrawSelfAndChild()
{
	for (auto& child : m_listNode)
	{
		child->Prender();
		child->Draw();
		child->PostRender();
	}
}

void Entity::AddMeshNode(const std::string& strPath, std::shared_ptr<RenderState>& spRenderState)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(strPath, aiProcess_Triangulate | aiProcess_GenSmoothNormals
		| aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "Error::ASSIMP::" << importer.GetErrorString() << std::endl;
		return;
	}

	ProcessMeshNode(scene->mRootNode, scene, strPath, spRenderState);
}

void Entity::ProcessMeshNode(aiNode* node, const aiScene* scene, const std::string& strPath, 
	std::shared_ptr<RenderState>& spRenderState)
{
	for (int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		auto spMeshNode = std::make_shared<MeshNode>();
		spMeshNode->SetRenderState(spRenderState);
		spMeshNode->ProcessMesh(mesh, scene, strPath);
		m_listNode.push_back(spMeshNode);
	}
	for (int i = 0; i < node->mNumChildren; i++)
	{
		ProcessMeshNode(node->mChildren[i], scene, strPath, spRenderState);
	}
}
