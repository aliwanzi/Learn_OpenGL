#pragma once
#include "Node.h"

class GeometryNode :public Node
{
public:
	GeometryNode(std::vector<Vertex>& vecVertexs, std::vector<unsigned int>& vecIndexs,
		std::shared_ptr<RenderState> spRenderState, std::shared_ptr<Transform> spTransform);
	~GeometryNode();
	void Prender() override;
	void Draw() override;
};