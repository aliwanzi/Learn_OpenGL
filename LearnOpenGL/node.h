#pragma once
#include "common.h"
#include "render_state.h"
#include "transform.h"

struct Vertex
{
	Vertex(glm::vec3 position = glm::vec3(0.f), glm::vec2 texCoords = glm::vec2(0.0),
		glm::vec3 normal = glm::vec3(0.0), glm::vec3 tangent = glm::vec3(0.0), glm::vec3 bitangent = glm::vec3(0.0)) :
		Position(position), TexCoords(texCoords),
		Normal(normal), Tangent(tangent), Bitangent(bitangent)
	{

	}
	glm::vec3 Position;
	glm::vec2 TexCoords;
	glm::vec3 Normal;
	glm::vec3 Tangent;
	glm::vec3 Bitangent;
};


class Node
{
public:
	Node();
	Node(std::vector<Vertex>& vecVertexs, std::vector<unsigned int>& vecIndexs,
		std::shared_ptr<RenderState> spRenderState, std::shared_ptr<Transform> spTransform);
	~Node();
	void SetRenderState(std::shared_ptr<RenderState> spRenderState);
	std::shared_ptr<RenderState> GetRenderState();
	void SetTransform(std::shared_ptr<Transform> spTransform);
	void SetInstanceOffset(const std::vector<glm::vec2>& vecOffset);
	void SetInstanceOffset(const std::vector<glm::mat4>& vecOffset);
	void SetUniformColor(const glm::vec3& color, bool bUniformColor = true);
	void SetUniformCull(bool bUseNodeCull, bool bUniformCull = true);
	void SetUniformReverseNormal(bool bUnifromReverse);
	void SetUniformSamples(const std::vector<glm::vec3>& vecSamples);
	void SetUniformAlbedo(const glm::vec3& albedo, bool bAlbedo = true);
	void SetUniformMetallic(float metallic, bool bMetallic = true);
	void SetUniformRouthness(float roughness, bool bRoughness = true);
	void SetUniformAo(float ao, bool bAo = true);

	virtual void Prender();
	virtual void Draw();
	virtual void PostRender();

	void ApplyTexture();

private:
	void ApplyTransform();
	void ApplyUniform();

protected:

	void SetVertexs(std::vector<Vertex>& vecVertexs);
	void SetIndexs(std::vector<unsigned int>& vecIndexs);
	void SetVAOVBO();

protected:
	std::shared_ptr<RenderState> m_spRenderState;
	std::shared_ptr<Transform> m_spTransform;
	std::vector<GLuint> m_vecTexture;

	bool m_bUniformColor;
	glm::vec3 m_vec3Color;

private:
	std::vector<Vertex> m_vecVertexs;
	std::vector<unsigned int> m_vecIndexs;

	unsigned int m_uiVAO;
	unsigned int m_uiVBO;
	unsigned int m_uiEBO;
	unsigned int m_uiInstance;

	bool m_bUseNodeCull;
	bool m_bUniformCull;
	bool m_bUnifromReverse;
	std::vector<glm::vec3> m_vecSamples;

	glm::vec3 m_vec3Albedo;
	bool m_bAlbedo;
	float m_fMetallic;
	bool m_bMetallic;
	float m_fRouthness;
	bool m_bRouthness;
	float m_fAo;
	bool m_bAo;
};