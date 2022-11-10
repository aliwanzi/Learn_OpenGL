#include "node.h"
#include "GLFW/glfw3.h"

Node::Node() :m_uiVAO(0), m_uiVBO(0), m_uiEBO(0),
m_spRenderState(nullptr), m_spTransform(nullptr),
m_bUniformColor(false), m_bUniformCull(false), m_bUnifromReverse(false), m_bUseNodeCull(false)
{

}

Node::Node(std::vector<Vertex>& vecVertexs, std::vector<unsigned int>& vecIndexs,
	std::shared_ptr<RenderState> spRenderState, std::shared_ptr<Transform> spTransform) :
	m_vecVertexs(vecVertexs), m_vecIndexs(vecIndexs), m_spRenderState(spRenderState), m_spTransform(spTransform),
	m_bUniformColor(false), m_bUniformCull(false), m_bUnifromReverse(false),m_bUseNodeCull(false)
{
	SetVAOVBO();
}

Node::~Node()
{

}

void Node::Prender()
{
	ApplyTexture();
	ApplyTransform();
	ApplyUniform();
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
	else if(m_spRenderState->GetDrawMode() == DRAW_MODE::ELEMENT_INSTANCE_MODE)
	{
		glDrawElementsInstanced(GL_TRIANGLES, static_cast<unsigned int>(m_vecIndexs.size()), GL_UNSIGNED_INT, 0, m_uiInstance);
	}
	glBindVertexArray(0);
	glActiveTexture(GL_TEXTURE0);
	glGetError();
}

void Node::PostRender()
{

}

void Node::ApplyTexture()
{
	unsigned int diffuseNr(1), specularNr(1), normalNr(1), heightNr(1), cubeMap(1);
	auto mapTextures = m_spRenderState->GetTexture()->GetTexures();
	for (size_t i = 0; i < m_vecTexture.size(); i++)
	{
		auto iter = mapTextures.find(m_vecTexture[i]);
		if (iter!=mapTextures.end())
		{
			glActiveTexture(GL_TEXTURE0 + i);
			std::string sNumber(""), sName("");
			switch (iter->second->eType)
			{
			case DIFFUSE:
			{
				sNumber = std::to_string(diffuseNr++);
				sName = "texture_diffuse";
				break;
			}
			case SPECULAR:
			{
				sNumber = std::to_string(specularNr++);
				sName = "texture_specular";
				break;
			}
			case NORMAL:
			{
				sNumber = std::to_string(normalNr++);
				sName = "texture_normal";
				break;
			}
			case HEIGHT:
			{
				sNumber = std::to_string(heightNr++);
				sName = "texture_height";
				break;
			}
			case CUBEMAP:
			{
				sNumber = std::to_string(cubeMap++);
				sName = "texture_cube_map";
				break;
			}
			default:
				break;
			}
			auto spShader = m_spRenderState->GetShader();
			spShader->SetInt(sName + sNumber, i);
			if (iter->second->eType == TextureType::CUBEMAP)
			{
				glBindTexture(GL_TEXTURE_CUBE_MAP, iter->second->uiID);
			}
			else
			{
				glBindTexture(GL_TEXTURE_2D, iter->second->uiID);
			}
		}
	}
}

void Node::ApplyTransform()
{
	if (m_spTransform != nullptr)
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
	else
	{
		m_spRenderState->SetModelMatrix(glm::mat4(1.0));
	}
}

void Node::ApplyUniform()
{
	auto spShader = m_spRenderState->GetShader();
	if (m_bUniformColor)
	{
		spShader->SetVec3("lightColor", m_vec3Color);
	}
	if (m_bUseNodeCull)
	{
		if (m_bUniformCull)
		{
			glEnable(GL_CULL_FACE);
		}
		else
		{
			glDisable(GL_CULL_FACE);
		}
	}

	if (m_bUnifromReverse)
	{
		spShader->SetBool("reverse_normals", m_bUnifromReverse);
	}
	else
	{
		spShader->SetBool("reverse_normals", m_bUnifromReverse);
	}

	if (m_vecSamples.size()>0)
	{
		for (size_t i = 0; i < m_vecSamples.size(); i++)
		{
			spShader->SetVec3("samples[" + std::to_string(i) + "]", m_vecSamples[i]);
		}
	}
}

void Node::SetVertexs(std::vector<Vertex>& vecVertexs)
{
	this->m_vecVertexs = vecVertexs;
}

void Node::SetIndexs(std::vector<unsigned int>& vecIndexs)
{
	this->m_vecIndexs = vecIndexs;
}

void Node::SetRenderState(std::shared_ptr<RenderState> spRenderState)
{
	this->m_spRenderState = spRenderState;

	auto& mapTexture = spRenderState->GetTexture()->GetTexures();
	for (auto iter = mapTexture.begin(); iter != mapTexture.end(); iter++)
	{
		if (iter->second->eType==TextureType::CUBEMAP)
		{
			m_vecTexture.push_back(iter->second->uiID);
		}
	}
}

void Node::SetTransform(std::shared_ptr<Transform> spTransform)
{
	this->m_spTransform = spTransform;
}

void Node::SetInstanceOffset(const std::vector<glm::vec2>& vecOffset)
{
	glBindVertexArray(m_uiVAO);
	GLuint uiInstanceVBO;
	glGenBuffers(1, &uiInstanceVBO);
	glBindBuffer(GL_ARRAY_BUFFER, uiInstanceVBO);
	glBufferData(GL_ARRAY_BUFFER, vecOffset.size() * sizeof(glm::vec2), &vecOffset[0], GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);
	glVertexAttribDivisor(5, 1);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	if (m_spRenderState->GetDrawMode() == DRAW_MODE::ELEMENT_INSTANCE_MODE)
	{
		m_uiInstance = vecOffset.size();
	}
}

void Node::SetInstanceOffset(const std::vector<glm::mat4>& vecOffset)
{
	glBindVertexArray(m_uiVAO);
	GLuint uiInstanceVBO;
	glGenBuffers(1, &uiInstanceVBO);
	glBindBuffer(GL_ARRAY_BUFFER, uiInstanceVBO);
	glBufferData(GL_ARRAY_BUFFER, vecOffset.size() * sizeof(glm::mat4), &vecOffset[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
	glEnableVertexAttribArray(6);
	glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
	glEnableVertexAttribArray(7);
	glVertexAttribPointer(7, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
	glEnableVertexAttribArray(8);
	glVertexAttribPointer(8, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));

	glVertexAttribDivisor(5, 1);
	glVertexAttribDivisor(6, 1);
	glVertexAttribDivisor(7, 1);
	glVertexAttribDivisor(8, 1);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	if (m_spRenderState->GetDrawMode() == DRAW_MODE::ELEMENT_INSTANCE_MODE)
	{
		m_uiInstance = vecOffset.size();
	}
}

void Node::SetUniformColor(const glm::vec3& color, bool bUniformColor)
{
	m_bUniformColor = bUniformColor;
	m_vec3Color = color;
}

void Node::SetUniformCull(bool bUseNodeCull, bool bUniformCull)
{
	m_bUseNodeCull = bUseNodeCull;
	m_bUniformCull = bUniformCull;
}

void Node::SetUniformReverseNormal(bool bUnifromReverse)
{
	m_bUnifromReverse = bUnifromReverse;
}

void Node::SetUniformSamples(const std::vector<glm::vec3>& vecSamples)
{
	m_vecSamples = vecSamples;
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