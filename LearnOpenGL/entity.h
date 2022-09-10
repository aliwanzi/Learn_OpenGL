#pragma once
#include "geometry_node.h"
#include "transform.h"
#include <list>

class Entity
{
public:
	Entity();
	~Entity();

	void DrawSelfAndChild();
	void AddNode(std::shared_ptr<Node> spNode);

private:
	std::list<std::shared_ptr<Entity>> m_listEntity;
	std::shared_ptr<Entity> m_spParent;
	std::list<std::shared_ptr<Node>> m_listNode;
};