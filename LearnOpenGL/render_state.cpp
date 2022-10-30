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
	m_spFrameBuffer(nullptr),
	m_bFrameBuffer(false),
	m_bClearFrameBuffer(true),
	m_ePolygonMode(POLYGON_MODE::FACE_MODE),
	m_eDrawMode(DRAW_MODE::ELEMENT_MODE),
	m_ePrimitiveMode(PRIMITIVE_MODE::POINTS_MODE),
	m_vec4BackGround(glm::vec4(0.f)),
	m_spUniformBuffer(nullptr),
	m_bUniformBuffer(false),
	m_bUpdateUniformBuffer(true),
	m_bSkyBox(false),
	m_bExplode(false),
	m_bMultiSample(false),
	m_bMASS(false),
	m_spMSAAInfo(nullptr),
	m_bGBuffer(false),
	m_spGBuffer(nullptr),
	m_bCopyGBufferDepth(false),
	m_bHDRBuffer(false),
	m_spHDRBuffer(nullptr),
	m_spBlurBuffer(nullptr),
	m_bBlurBuffer(false),
	m_bHorizontal(true),
	m_bFirst(true),
	m_bUseBlinn(false),
	m_blinn(true),
	m_bBlinnPressed(false),
	m_bUseBloom(false),
	m_bBloom(false),
	m_bUseGamma(false),
	m_bGamma(true),
	m_bGammaPressed(false),
	m_bUseExposure(false),
	m_fExposure(1.0f),
	m_bEnableDepthBuffer(false),
	m_spDepthBuffer(nullptr),
	m_bEnabelLightSpace(false),
	m_bEnableCubeLightSpace(false),
	m_bUseShadow(false),
	m_bShadow(false),
	m_bShadowPressed(false),
	m_bEnableFarAndNear(false),
	m_fFar(0.f),
	m_fNear(0.f)
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

const std::vector<std::shared_ptr<Light>>& RenderState::GetLights() const
{
	return m_vecLights;
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

void RenderState::EnableFrameBuffer(bool bFrameBuffer)
{
	m_bFrameBuffer = bFrameBuffer;
}

void RenderState::SetClearBuffer(bool bClearBuffer)
{
	m_bClearFrameBuffer = bClearBuffer;
}

void RenderState::SetFrameBuffer(std::shared_ptr<FrameBuffer> spFrameBuffer)
{
	m_spFrameBuffer = spFrameBuffer;
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
		if (m_spBlend)
		{
			glBlendEquation(m_spBlend->BlendFunc);
			glBlendFuncSeparate(m_spBlend->SRGB, m_spBlend->DRGB, m_spBlend->SAlpha, m_spBlend->DAlpha);
		}
	}
	else
	{
		glDisable(GL_BLEND);
	}

	if (m_bStencil)
	{
		glEnable(GL_STENCIL_TEST);
		if (m_spStencil)
		{
			glStencilOp(m_spStencil->SFail, m_spStencil->DpFail, m_spStencil->DpPass);
			glStencilFunc(m_spStencil->SFunc, m_spStencil->RefValue, m_spStencil->Mask);
			glStencilMask(m_spStencil->WriteMask);
		}
	}
	else
	{
		glDisable(GL_STENCIL_TEST);
		glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
	}

	if (m_bCullFace)
	{
		glEnable(GL_CULL_FACE);
		if (m_spCullFace)
		{
			glCullFace(m_spCullFace->FaceMode);
			//glFrontFace(m_spCullFace->FaceOri);
		}
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

	if (m_bMultiSample)
	{
		glEnable(GL_MULTISAMPLE);
	}
	else
	{
		glDisable(GL_MULTISAMPLE);
	}

	switch (m_ePolygonMode)
	{
	case POLYGON_MODE::POINT_MODE:
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		glEnable(GL_PROGRAM_POINT_SIZE);
		break;
	}
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

void RenderState::ApplyPreState()
{
	if (m_bFrameBuffer)
	{
		if (m_spFrameBuffer)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, m_spFrameBuffer->GetFrameBuffer());
		}
	}
	else if (m_bHDRBuffer)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_spHDRBuffer->GetHDRBuffer());
	}
	else
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	if (m_bCopyGBufferDepth)
	{
		glBindFramebuffer(GL_READ_FRAMEBUFFER, m_spGBuffer->GetGBuffer());
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
		glBlitFramebuffer(0, 0, m_spGBuffer->GetWidth(), m_spGBuffer->GetHeight(), 0, 0,
			m_spGBuffer->GetWidth(), m_spGBuffer->GetHeight(), GL_DEPTH_BUFFER_BIT, GL_NEAREST);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	if (m_bBlurBuffer)
	{
		static int num(0);
		static bool first(true);
		int frame = num % 2;
		glBindFramebuffer(GL_FRAMEBUFFER, m_spBlurBuffer->GetBlurBuffer()[frame]);
		m_spShader->SetInt("horizontal", frame);
		glBindTexture(GL_TEXTURE_2D, first ? m_spHDRBuffer->GetBrightness() : m_spBlurBuffer->GetRendering()[(num+1) % 2]);
		num++;
		if (first)
		{
			glClearColor(m_vec4BackGround.r, m_vec4BackGround.g, m_vec4BackGround.b, m_vec4BackGround.a);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
			first = false;
		}
		if (num == m_iFrame)
		{
			first = true;
			num = 0;
		}
	}

	if (m_bEnableDepthBuffer)
	{
		m_spDepthBuffer->Bind();
	}

	if (m_bGBuffer)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_spGBuffer->GetGBuffer());
	}

	if (m_bClearFrameBuffer)
	{
		glClearColor(m_vec4BackGround.r, m_vec4BackGround.g, m_vec4BackGround.b, m_vec4BackGround.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}
}

void RenderState::ApplyPostState()
{
	if (m_bMASS)
	{
		glBindFramebuffer(GL_READ_FRAMEBUFFER, m_spMSAAInfo->Source);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_spMSAAInfo->Target);
		glBlitFramebuffer(0, 0, m_spMSAAInfo->SourceWidth, m_spMSAAInfo->SourceHeight,
			0, 0, m_spMSAAInfo->TargetWidth, m_spMSAAInfo->TargetHeight, GL_COLOR_BUFFER_BIT, GL_NEAREST);
	}
	if (m_bStencil)
	{
		glStencilFunc(GL_ALWAYS, 0, 0xFF);
		glStencilMask(0xFF);
	}
	if (m_bFrameBuffer)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	if (m_glDepthFunc != GL_LESS)
	{
		glDepthFunc(GL_LESS);
	}
	if (m_bEnableDepthBuffer)
	{
		int width(0), height(0);
		m_spDepthBuffer->GetOriWidthAndHeight(width, height);
		glViewport(0, 0, width, height);
	}
	if (m_bCullFace)
	{
		glCullFace(GL_BACK);
	}
}

void RenderState::ApplyTransform(std::shared_ptr<Camera>spCamera)
{
	if (m_bUniformBuffer)
	{
		if (m_bUpdateUniformBuffer)
		{
			glBindBuffer(GL_UNIFORM_BUFFER, m_spUniformBuffer->GetUniformBuffer());
			if (m_bSkyBox)
			{
				glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(spCamera->GetViewMatrixRemoveTranslate()));
			}
			else
			{
				glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(spCamera->GetViewMatrix()));
			}

			glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(spCamera->GetProjectionMatrix()));
			glBindBuffer(GL_UNIFORM_BUFFER, 0);
		}
	}
	else if (m_bEnableCubeLightSpace)
	{
		for (size_t i = 0; i < m_vecLightSpaceMatrix.size(); i++)
		{
			auto sName = "matLightSpace[" + std::to_string(i) + "]";
			m_spShader->SetMat4(sName, m_vecLightSpaceMatrix[i]);
		}
	}
	else
	{
		if (m_bSkyBox)
		{
			m_spShader->SetMat4("matView", spCamera->GetViewMatrixRemoveTranslate());
		}
		else
		{
			m_spShader->SetMat4("matView", spCamera->GetViewMatrix());
		}
		
		m_spShader->SetMat4("matProjection", spCamera->GetProjectionMatrix());
	}
	if (m_bExplode)
	{
		m_spShader->SetFloat("time", glm::sin(glfwGetTime()));
	}
	if (m_bEnabelLightSpace)
	{
		m_spShader->SetMat4("matLightSpace", m_matLightSpaceMatrix);
	}

	if (m_bUseExposure)
	{
		m_spShader->SetFloat("exposure", m_fExposure);
	}
	if (m_bUseBloom)
	{
		m_spShader->SetBool("bloom", m_bBloom);
		//m_bBloom ? std::cout << "use Bloom" << std::endl : std::cout << "no use Blomm" << std::endl;
	}
	if (m_bUseGamma)
	{
		m_spShader->SetBool("bgamma", m_bGamma);
		//m_bGamma ? std::cout << "use Gamma" << std::endl : std::cout << "no use Gamma" << std::endl;
	}
	if (m_bUseBlinn)
	{
		m_spShader->SetBool("blinn", m_blinn);
		//m_bBloom ? std::cout << "use BlinnPhong" << std::endl : std::cout << "use Phong" << std::endl;
	}
	if (m_bEnableFarAndNear)
	{
		m_spShader->SetFloat("far_plane", m_fFar);
		m_spShader->SetFloat("near_plane", m_fNear);
	}
	if (m_bUseShadow)
	{
		m_spShader->SetBool("bShadow", m_bShadow);
	}
}

void RenderState::ApplyLights(std::shared_ptr<Camera> spCamera)
{
	m_spShader->SetVec3("viewPos", spCamera->GetEye());
	if (m_vecLights.size() > 0)
	{
		unsigned int uiPoint(0);
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
					m_spShader->SetFloat(sName + ".radius", spPointLight->GetRadius());
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

void RenderState::EnableGBuffer(bool bGBuffer)
{
	m_bGBuffer = bGBuffer;
}

void RenderState::SetGBuffer(std::shared_ptr<GBuffer> spGBuffer)
{
	m_spGBuffer = spGBuffer;
}

void RenderState::CopyGBufferDepth(bool bCopy)
{
	m_bCopyGBufferDepth = bCopy;
}

void RenderState::SetBackGround(const glm::vec4& vec4BackGround)
{
	m_vec4BackGround = vec4BackGround;
}

void RenderState::EnableUniformBuffer(bool bUniformBuffer)
{
	m_bUniformBuffer = bUniformBuffer;
}

void RenderState::UpdateUniformBuffer(bool bUpdate)
{
	m_bUpdateUniformBuffer = bUpdate;
}

void RenderState::SetUniformBuffer(std::shared_ptr<UniformBuffer> spUniformBuffer)
{
	m_spUniformBuffer = spUniformBuffer;
}

std::shared_ptr<Shader> RenderState::GetShader() const
{
	return m_spShader;
}

void RenderState::SetDrawSkyBox(bool bSkyBox)
{
	m_bSkyBox = bSkyBox;
}

void RenderState::SetExplode(bool bExplode)
{
	m_bExplode = bExplode;
}

void RenderState::SetHDRBuffer(std::shared_ptr<HDRBuffer> spHDRBuffer)
{
	m_spHDRBuffer = spHDRBuffer;
}

void RenderState::EnabelHDRBuffer(bool bHDRBuffer)
{
	m_bHDRBuffer = bHDRBuffer;
}

void RenderState::SetBlurBuffer(std::shared_ptr<BlurBuffer> spBlurBuffer)
{
	m_spBlurBuffer = spBlurBuffer;
}

void RenderState::EnabelBlurBuffer(bool bBlurBuffer)
{
	m_bBlurBuffer = bBlurBuffer;
}

void RenderState::SetBlurFrame(int frame)
{
	m_iFrame = frame;
}

void RenderState::EnableUseBlinn(bool bUseLinn)
{
	m_bUseBlinn = bUseLinn;
}

bool RenderState::GetUseBlinn() const
{
	return m_bUseBlinn;
}

bool RenderState::GetBlinn() const
{
	return m_blinn;
}

void RenderState::SetBlinn(bool blinn)
{
	m_blinn = blinn;
}

bool RenderState::GetBlinnPressed() const
{
	return m_bBlinnPressed;
}

void RenderState::SetBlinnPressed(bool bPress)
{
	m_bBlinnPressed = bPress;
}

void RenderState::EnableUseBloom(bool bBloom)
{
	m_bUseBloom = bBloom;
}

bool RenderState::GetUseBloom() const
{
	return m_bUseBloom;
}

bool RenderState::GetBloom() const
{
	return m_bBloom;
}

void RenderState::SetBloom(bool bBloom)
{
	m_bBloom = bBloom;
}

void RenderState::SetBloomPressed(bool bPress)
{
	m_bBloomPressed = bPress;
}

bool RenderState::GetBloomPressed() const
{
	return m_bBloomPressed;
}

void RenderState::EnabelUseExposure(bool bExposure)
{
	m_bUseExposure = bExposure;
}


void RenderState::EnableUseGamma(bool bEnable)
{
	m_bUseGamma = bEnable;
}

bool RenderState::GetUseGamma() const
{
	return m_bUseGamma;
}

bool RenderState::GetGamma() const
{
	return m_bGamma;
}

void RenderState::SetGamma(bool bGamma)
{
	m_bGamma = bGamma;
}

void RenderState::SetDepthMappingBuffer(std::shared_ptr<DepthBuffer> spDepthBuffer)
{
	m_spDepthBuffer = spDepthBuffer;
}

void RenderState::EnableDepthMappingBuffer(bool bEnableDepth)
{
	m_bEnableDepthBuffer = bEnableDepth;
}

void RenderState::EnableLightSpace(bool bEnable)
{
	m_bEnabelLightSpace = bEnable;
}

void RenderState::SetCubeLightSpaceMatrix(const std::vector<glm::mat4>& vecMatLightSpace)
{
	m_vecLightSpaceMatrix = vecMatLightSpace;
}

void RenderState::EnabelCubeLightSpace(bool bEnable)
{
	m_bEnableCubeLightSpace = bEnable;
}

void RenderState::EnableUseShadow(bool bUseShadow)
{
	m_bUseShadow = bUseShadow;
}

bool RenderState::GetUseShadow() const
{
	return m_bUseShadow;
}

bool RenderState::GetShadow() const
{
	return m_bShadow;
}

void RenderState::SetShadow(bool Shadow)
{
	m_bShadow = Shadow;
}

bool RenderState::GetShadowPressed() const
{
	return m_bShadowPressed;
}

void RenderState::SetShadowPressed(bool bPress)
{
	m_bShadowPressed = bPress;
}

void RenderState::EnabelNearAndFar(bool bEnable)
{
	m_bEnableFarAndNear = bEnable;
}

void RenderState::SetNearAndFar(float fnear, float ffar)
{
	m_fNear = fnear;
	m_fFar = ffar;
}

void RenderState::SetLightSpaceMatrix(const glm::mat4& matLightSpace)
{
	m_matLightSpaceMatrix = matLightSpace;
}

void RenderState::SetGammaPressed(bool bPress)
{
	m_bGammaPressed = bPress;
}

bool RenderState::GetGammaPressed() const
{
	return m_bGammaPressed;
}


bool RenderState::GetUseExpusure() const
{
	return m_bUseExposure;
}

void RenderState::SetExposure(float fExposure)
{
	m_fExposure = fExposure;
}

float RenderState::GetExposure()const
{
	return m_fExposure;
}

void RenderState::EnableMultiSample(bool bMultiSample)
{
	m_bMultiSample = bMultiSample;
}

void RenderState::EnableMSAA(bool bMSAA)
{
	m_bMASS = bMSAA;
}

void RenderState::SetMSAAInfor(std::shared_ptr<MSAAInfo> spMSAAInfo)
{
	m_spMSAAInfo = spMSAAInfo;
}

void RenderState::SetModelMatrix(const glm::mat4& matModel)
{
	m_spShader->SetMat4("matModel", matModel);
}
