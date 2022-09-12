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

private:
	void ProcessMeshNode(aiNode* node, const aiScene* scene, const std::string& strPath, 
		std::shared_ptr<RenderState>& spRenderState);


private:
	std::list<std::shared_ptr<Entity>> m_listEntity;
	std::shared_ptr<Entity> m_spParent;
	std::list<std::shared_ptr<Node>> m_listNode;
};