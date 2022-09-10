#include "entity.h"

Entity::Entity():m_spParent(nullptr)
{
}

Entity::~Entity()
{

}

void Entity::AddNode(std::shared_ptr<Node> spNode)
{
	m_listNode.push_back(spNode);
}

void Entity::DrawSelfAndChild()
{
	for (auto& child : m_listNode)
	{
		child->Draw();
	}
}