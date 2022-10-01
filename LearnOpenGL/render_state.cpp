#pragma once
#include "render_state.h"

RenderState::RenderState(std::shared_ptr<Shader>spShader, std::shared_ptr<Texture>spTexture /*= nullptr*/) :
	m_bBlend(false),
	m_spBlend(nullptr),
	m_iVertices(0),
	m_bDepthTest(false),
	m_glDepthFunc(GL_LESS),
	m_bStencil(false),
	m_bCullFace(false),
	m_spCullFace(nullptr),
	m_spShader(spShader),
	m_spTexture(spTexture),
	m_spStencil(nullptr),
	m_matModel(glm::mat4()),
	m_ePolygonMode(POLYGON_MODE::FACE_MODE),
	m_eDrawMode(DRAW_MODE::ELEMENT_MODE),
	m_ePrimitiveMode(PRIMITIVE_MODE::POINTS_MODE)
{

}

RenderState::~RenderState()
{

}

void RenderState::EnableBlend(bool bBlend)
{
	m_bBlend = bBlend;
}

void RenderState::SetBlend(std::shared_ptr<Blend> spBlend)
{
	m_spBlend = spBlend;
}

void RenderState::EnableDepthTest(bool bDepthTest)
{
	m_bDepthTest = bDepthTest;
}

void RenderState::SetDepthFunc(GLenum gDepthFunc)
{
	m_glDepthFunc = gDepthFunc;
}

void RenderState::EnableCullFace(bool bCull)
{
	m_bCullFace = bCull;
}

void RenderState::SetCullFace(std::shared_ptr<CullFace> spCullFace)
{
	m_spCullFace = spCullFace;
}

void RenderState::SetTexture(std::shared_ptr<Texture>spTexture)
{
	m_spTexture = spTexture;
}

std::shared_ptr<Texture>& RenderState::GetTexture()
{
	return m_spTexture;
}

void RenderState::SetLights(const std::vector<std::shared_ptr<Light>>& vecLights)
{
	m_vecLights = vecLights;
}

void RenderState::AddLight(std::shared_ptr<Light> spLight)
{
	m_vecLights.push_back(spLight);
}

void RenderState::Use()
{
	m_spShader->Use();
}

void RenderState::ApplyState()
{
	if (m_bBlend)
	{
		glEnable(GL_BLEND);
		glBlendEquation(m_spBlend->BlendFunc);
		glBlendFuncSeparate(m_spBlend->SRGB, m_spBlend->DRGB, m_spBlend->SAlpha, m_spBlend->DAlpha);
	}
	else
	{
		glDisable(GL_BLEND);
	}

	if (m_bStencil)
	{
		glEnable(GL_STENCIL_TEST);
		glStencilOp(m_spStencil->SFail, m_spStencil->DpFail, m_spStencil->DpPass);
		glStencilFunc(m_spStencil->SFunc, m_spStencil->RefValue, m_spStencil->Mask);
		glStencilMask(m_spStencil->WriteMask);
	}
	else
	{
		glDisable(GL_STENCIL_TEST);
		glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
	}

	if (m_bCullFace)
	{
		glEnable(GL_CULL_FACE);
		glCullFace(m_spCullFace->FaceMode);
		glFrontFace(m_spCullFace->FaceOri);
	}
	else
	{
		glDisable(GL_CULL_FACE);
	}

	if (m_bDepthTest)
	{
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(m_glDepthFunc);
	}
	else
	{
		glDisable(GL_DEPTH_TEST);
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

void RenderState::ApplyPostState()
{
	if (m_bStencil)
	{
		glStencilFunc(GL_ALWAYS, 0, 0xFF);
		glStencilMask(0xFF);
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

void RenderState::ApplyLights(std::shared_ptr<Camera> spCamera)
{
	if (m_vecLights.size() > 0)
	{
		unsigned int uiPoint(0);
		m_spShader->SetVec3("viewPos", spCamera->GetEye());
		for (int i = 0; i < m_vecLights.size(); i++)
		{
			switch (m_vecLights[i]->GetLightType())
			{
			case LightType::DIR_LIGHT:
			{
				std::shared_ptr<DirLight> spDirLight = std::dynamic_pointer_cast<DirLight>(m_vecLights[i]);
				if (spDirLight != nullptr)
				{
					m_spShader->SetVec3("dirLight.direction", (spDirLight)->GetLightDirction());
					m_spShader->SetVec3("dirLight.ambient", (spDirLight)->GetAmbient());
					m_spShader->SetVec3("dirLight.diffuse", (spDirLight)->GetDiffuse());
					m_spShader->SetVec3("dirLight.specular", (spDirLight)->GetSpecular());
					m_spShader->SetFloat("dirLight.shininess", (spDirLight)->GetShiness());
				}
				break;
			}
			case LightType::POINT_LIGHT:
			{
				std::shared_ptr<PointLight> spPointLight = std::dynamic_pointer_cast<PointLight>(m_vecLights[i]);
				if (spPointLight != nullptr)
				{
					auto sName = "pointLights[" + std::to_string(uiPoint++) + "]";
					m_spShader->SetVec3(sName + ".position", (spPointLight)->GetLightPosition());
					m_spShader->SetVec3(sName + ".ambient", (spPointLight)->GetAmbient());
					m_spShader->SetVec3(sName + ".diffuse", (spPointLight)->GetDiffuse());
					m_spShader->SetVec3(sName + ".specular", (spPointLight)->GetSpecular());
					m_spShader->SetFloat(sName + ".shininess", (spPointLight)->GetShiness());
					m_spShader->SetFloat(sName + ".constant", (spPointLight)->GetConstant());
					m_spShader->SetFloat(sName + ".linear", (spPointLight)->GetLinear());
					m_spShader->SetFloat(sName + ".quadratic", (spPointLight)->GetQuartic());
				}
				break;
			}
			case LightType::SPOT_LIGHT:
			{
				std::shared_ptr<SpotLight> spSpotLight = std::dynamic_pointer_cast<SpotLight>(m_vecLights[i]);
				if (spSpotLight != nullptr)
				{
					m_spShader->SetVec3("spotLight.position", spCamera->GetEye());
					m_spShader->SetVec3("spotLight.direction", spCamera->GetViewDirection());
					m_spShader->SetVec3("spotLight.ambient", (spSpotLight)->GetAmbient());
					m_spShader->SetVec3("spotLight.diffuse", (spSpotLight)->GetDiffuse());
					m_spShader->SetVec3("spotLight.specular", (spSpotLight)->GetSpecular());
					m_spShader->SetFloat("spotLight.shininess", (spSpotLight)->GetShiness());
					m_spShader->SetFloat("spotLight.constant", (spSpotLight)->GetConstant());
					m_spShader->SetFloat("spotLight.linear", (spSpotLight)->GetLinear());
					m_spShader->SetFloat("spotLight.quadratic", (spSpotLight)->GetQuartic());
					m_spShader->SetFloat("spotLight.cutOff", glm::cos(glm::radians((spSpotLight)->GetCutOff())));
					m_spShader->SetFloat("spotLight.outerCutOff", glm::cos(glm::radians((spSpotLight)->GetOuterCutOff())));
				}
				break;
			}

			default:
				break;
			}
		}
	}
}

void RenderState::EnableStencil(bool bStencil)
{
	m_bStencil = bStencil;
}

void RenderState::SetStencil(std::shared_ptr<Stencil> spStencil)
{
	m_spStencil = spStencil;
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
