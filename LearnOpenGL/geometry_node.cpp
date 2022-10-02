#include "geometry_node.h"

GeometryNode::GeometryNode(std::vector<Vertex>& vecVertexs, std::vector<unsigned int>& vecIndexs,
	std::shared_ptr<RenderState> spRenderState, std::shared_ptr<Transform> spTransform):
	Node(vecVertexs, vecIndexs, spRenderState, spTransform)
{
	auto& mapTexture = spRenderState->GetTexture()->GetTexures();
	for (auto iter = mapTexture.begin(); iter != mapTexture.end(); iter++)
	{
		m_vecTexture.push_back(iter->second->uiID);
	}
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
