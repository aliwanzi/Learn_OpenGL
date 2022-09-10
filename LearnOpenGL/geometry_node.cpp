#include "geometry_node.h"

GeometryNode::GeometryNode(std::vector<Vertex>& vecVertexs, std::vector<unsigned int>& vecIndexs,
	std::shared_ptr<RenderState> spRenderState, std::shared_ptr<Transform> spTransform):
	Node(vecVertexs, vecIndexs, spRenderState, spTransform)
{

}

GeometryNode::~GeometryNode()
{

}

void GeometryNode::Draw()
{
	Node::Prender();
	Node::Draw();
}

void GeometryNode::Prender()
{
}
