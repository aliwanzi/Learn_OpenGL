#pragma once
#include "geometry_node.h"
#include "mesh_node.h"
#include "transform.h"
#include <list>

class Entity
{
public:
	Entity();
	~Entity();

	void DrawSelfAndChild();
	void AddMeshNode(const std::string& strPath, std::shared_ptr<RenderState>& spRenderState);
	void AddGeometryNode(std::shared_ptr<Node> spNode);
	void SetInstanceOffset(const std::vector<glm::vec2>& vecOffset);
	void SetInstanceOffset(const std::vector<glm::mat4>& vecOffset);
	void SetTransform(std::shared_ptr<Transform> spTransform);
	void SetMultiTransform(std::vector<std::shared_ptr<Transform>>& vecTransform);
private:
	void ProcessMeshNode(aiNode* node, const aiScene* scene, const std::string& strPath, 
		std::shared_ptr<RenderState>& spRenderState);


private:
	std::list<std::shared_ptr<Entity>> m_listEntity;
	std::shared_ptr<Entity> m_spParent;
	std::list<std::shared_ptr<Node>> m_listNode;
	std::vector<std::shared_ptr<Transform>> m_vecTransform;
};