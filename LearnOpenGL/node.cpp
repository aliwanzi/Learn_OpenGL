#include "node.h"
#include "GLFW/glfw3.h"

Node::Node() :m_uiVAO(0), m_uiVBO(0), m_uiEBO(0),
m_spRenderState(nullptr), m_spTransform(nullptr)
{

}

Node::Node(std::vector<Vertex>& vecVertexs, std::vector<unsigned int>& vecIndexs,
	std::shared_ptr<RenderState> spRenderState, std::shared_ptr<Transform> spTransform) :
	m_vecVertexs(vecVertexs), m_vecIndexs(vecIndexs), m_spRenderState(spRenderState), m_spTransform(spTransform)
{
	SetVAOVBO();
}

Node::~Node()
{

}

void Node::SetNode(std::vector<Vertex>& vecVertexs, std::vector<unsigned int>& vecIndexs,
	std::shared_ptr<RenderState> spRenderState, std::shared_ptr<Transform> spTransform)
{
	this->m_vecVertexs = vecVertexs;
	this->m_vecIndexs = vecIndexs;
	this->m_spRenderState = spRenderState;
	this->m_spTransform = spTransform;
	SetVAOVBO();
}

void Node::Prender()
{
	if (m_spTransform->GetModelRotUseTime())
	{
		auto rotAngel = static_cast<float>(glm::degrees(glfwGetTime()));
		m_spTransform->SetModelRotAngle(rotAngel);
	}

	if (m_spTransform->GetModelScalUseTime())
	{
		auto scaleAmount = static_cast<float>(sin(glfwGetTime()));
		m_spTransform->SetModelScale(glm::vec3(scaleAmount, scaleAmount, scaleAmount));
	}
	m_spRenderState->SetModelMatrix(m_spTransform->GetModelMatrix());
}


void Node::Draw()
{
	glBindVertexArray(m_uiVAO);
	if (m_spRenderState->GetDrawMode() == DRAW_MODE::ARRAY_MODE)
	{
		if (m_spRenderState->GetPrimitiveMode() == PRIMITIVE_MODE::POINTS_MODE)
		{
			glDrawArrays(GL_POINTS, 0, m_vecVertexs.size());
		}
	}
	else if (m_spRenderState->GetDrawMode() == DRAW_MODE::ELEMENT_MODE)
	{
		if (m_spRenderState->GetPrimitiveMode() == PRIMITIVE_MODE::PATCH_MODE)
		{
			glPatchParameteri(GL_PATCH_VERTICES, m_spRenderState->GetPatchVerteics());
			glDrawElements(GL_PATCHES, static_cast<unsigned int>(m_vecIndexs.size()), GL_UNSIGNED_INT, 0);
		}
		else if (m_spRenderState->GetPrimitiveMode() == PRIMITIVE_MODE::TRIANGLES_MODE)
		{
			glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(m_vecIndexs.size()), GL_UNSIGNED_INT, 0);
		}
	}

	glBindVertexArray(0);
	glActiveTexture(GL_TEXTURE0);
}

void Node::SetVAOVBO()
{
	glGenVertexArrays(1, &m_uiVAO);
	glGenBuffers(1, &m_uiVBO);
	glGenBuffers(1, &m_uiEBO);

	glBindVertexArray(m_uiVAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_uiVBO);
	glBufferData(GL_ARRAY_BUFFER, m_vecVertexs.size() * sizeof(Vertex), &m_vecVertexs[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_uiEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_vecIndexs.size() * sizeof(unsigned int), &m_vecIndexs[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));

	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}