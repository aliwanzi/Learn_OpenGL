#pragma once
#include "render_state.h"

RenderState::RenderState(std::shared_ptr<Shader>spShader, std::shared_ptr<Texture>spTexture /*= nullptr*/) :
	m_fBlend(0.f),
	m_bBlend(false),
	m_iVertices(0),
	m_bDepthTest(false),
	m_vec4BackGround(glm::vec4(0.f)),
	m_spShader(spShader),
	m_spTexture(spTexture),
	m_ePolygonMode(POLYGON_MODE::FACE_MODE),
	m_eDrawMode(DRAW_MODE::ELEMENT_MODE),
	m_ePrimitiveMode(PRIMITIVE_MODE::POINTS_MODE)
{

}

RenderState::~RenderState()
{

}

void RenderState::SetBackGround(const glm::vec4& vec4BackGround)
{
	m_vec4BackGround = vec4BackGround;
}

void RenderState::SetBlend(float fBlend)
{
	m_fBlend = fBlend;
	m_bBlend = true;
}

void RenderState::SetDepthTest(bool bDepthTest)
{
	m_bDepthTest = bDepthTest;
}

void RenderState::Use()
{
	m_spShader->Use();
}

void RenderState::ApplyState()
{
	glClearColor(m_vec4BackGround.r, m_vec4BackGround.g, m_vec4BackGround.b, m_vec4BackGround.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (m_bBlend)
	{
		m_spShader->SetFloat("mixValue", m_fBlend);
	}
	if (m_bDepthTest)
	{
		glEnable(GL_DEPTH_TEST);
	}
	switch (m_ePolygonMode)
	{
	case POLYGON_MODE::POINT_MODE:
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		break;
	case POLYGON_MODE::LINE_MODE:
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	case POLYGON_MODE::FACE_MODE:
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	default:
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	}
}

void RenderState::ApplyTexture()
{
	if (m_spTexture == nullptr)
	{
		return;
	}
	unsigned int diffuseNr(1), specularNr(1), normalNr(1), heightNr(1);
	auto vecTextures = m_spTexture->GetTexures();
	for (size_t i = 0; i < vecTextures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		std::string sNumber(""), sName("");
		switch (vecTextures[i].eType)
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
		default:
			break;
		}
		m_spShader->SetInt(sName + sNumber, i);
		glBindTexture(GL_TEXTURE_2D, vecTextures[i].uiID);
	}
}

void RenderState::ApplyTransform(std::shared_ptr<Camera>spCamera)
{
	m_spShader->SetMat4("matView", spCamera->GetViewMatrix());
	m_spShader->SetMat4("matProjection", spCamera->GetProjectionMatrix());
}

void RenderState::SetPatchVertices(int iVertices)
{
	m_iVertices = iVertices;
}

int RenderState::GetPatchVerteics() const
{
	return m_iVertices;
}

void RenderState::SetDrawMode(DRAW_MODE eDrawMode)
{
	m_eDrawMode = eDrawMode;
}

DRAW_MODE RenderState::GetDrawMode() const
{
	return m_eDrawMode;
}

void RenderState::SetPrimitiveMode(PRIMITIVE_MODE ePrimitiveMode)
{
	m_ePrimitiveMode = ePrimitiveMode;
}

PRIMITIVE_MODE RenderState::GetPrimitiveMode() const
{
	return m_ePrimitiveMode;
}

void RenderState::SetPolygonMode(POLYGON_MODE polygonMode)
{
	m_ePolygonMode = polygonMode;
}

void RenderState::SetModelMatrix(const glm::mat4& matModel)
{
	m_spShader->SetMat4("matModel", matModel);
}
