#pragma once
#include "common.h"
#include "shader.h"
#include "texture.h"
#include "camera.h"
#include "transform.h"
#include "light.h"
#include "frame_buffer.h"
#include "uniform_buffer.h"
#include "GBuffer.h"
#include "HDRBuffer.h"
#include "BlurBuffer.h"
#include "DepthBuffer.h"

enum POLYGON_MODE
{
	POINT_MODE = 0,
	LINE_MODE,
	FACE_MODE
};

enum DRAW_MODE
{
	ARRAY_MODE = 0,
	ELEMENT_MODE,
	ARRAY_INSTANCE_MODE,
	ELEMENT_INSTANCE_MODE
};

enum PRIMITIVE_MODE
{
	PATCH_MODE = 0,
	POINTS_MODE,
	LINES_MODE,
	LINES_ADJACENCY_MODE,
	TRIANGLES_MODE,
	TRIANGLES_ADJACENCY_MODE
};

struct Stencil
{
	GLint WriteMask;
	GLenum SFunc;
	GLint RefValue;
	GLuint Mask;
	GLenum SFail;
	GLenum DpFail;
	GLenum DpPass;
};

struct  Blend
{
	GLenum SRGB;
	GLenum DRGB;
	GLenum SAlpha;
	GLenum DAlpha;
	GLenum BlendFunc;
};

struct CullFace
{
	GLenum FaceMode;
	GLenum FaceOri;
};

struct MSAAInfo
{
	GLuint Source;
	unsigned int SourceWidth;
	unsigned int SourceHeight;
	GLuint Target;
	unsigned int TargetWidth;
	unsigned int TargetHeight;
};

class RenderState
{
public:
	RenderState(std::shared_ptr<Shader>spShader, std::shared_ptr<Texture>spTexture = nullptr);
	~RenderState();

	void SetLights(const std::vector<std::shared_ptr<Light>>& vecLights);
	void AddLight(std::shared_ptr<Light> spLight);
	const std::vector<std::shared_ptr<Light>>& GetLights()const;

	void Use();
	void ApplyState();
	void ApplyPreState();
	void ApplyPostState();
	void ApplyTransform(std::shared_ptr<Camera>spCamera);
	void ApplyLights(std::shared_ptr<Camera> spCamera);

	void EnableStencil(bool bStencil);
	void SetStencil(std::shared_ptr<Stencil> spStencil);

	void EnableBlend(bool bBlend);
	void SetBlend(std::shared_ptr<Blend> spBlend);

	void EnableDepthTest(bool bDepthTest);
	void SetDepthFunc(GLenum gDepthFunc);

	void EnableCullFace(bool bCull);
	void SetCullFace(std::shared_ptr<CullFace> spCullFace);

	void SetTexture(std::shared_ptr<Texture>spTexture);
	std::shared_ptr<Texture>& GetTexture();

	void EnableFrameBuffer(bool bFrameBuffer);
	void SetFrameBuffer(std::shared_ptr<FrameBuffer> spFrameBuffer);
	void SetClearBuffer(bool bClearBuffer);

	void EnableGBuffer(bool bGBuffer);
	void SetGBuffer(std::shared_ptr<GBuffer> spGBuffer);
	void CopyGBufferDepth(bool bCopy);

	void SetModelMatrix(const glm::mat4& matModel);

	void SetPatchVertices(int iVertices);
	int GetPatchVerteics() const;

	void SetDrawMode(DRAW_MODE eDrawMode);
	DRAW_MODE GetDrawMode()const;

	void SetPrimitiveMode(PRIMITIVE_MODE ePrimitiveMode);
	PRIMITIVE_MODE GetPrimitiveMode()const;

	void SetPolygonMode(POLYGON_MODE polygonMode);

	void SetBackGround(const glm::vec4& vec4BackGround);

	void EnableUniformBuffer(bool bUniformBuffer);
	void UpdateUniformBuffer(bool bUpdate);
	void SetUniformBuffer(std::shared_ptr<UniformBuffer> spUniformBuffer);

	std::shared_ptr<Shader> GetShader()const;

	void SetDrawSkyBox(bool bSkyBox);
	void SetExplode(bool bExplode);
		
	void EnableMultiSample(bool bMultiSample);
	void EnableMSAA(bool bMSAA);
	void SetMSAAInfor(std::shared_ptr<MSAAInfo> spMSAAInfo);

	void SetHDRBuffer(std::shared_ptr<HDRBuffer> spHDRBuffer);
	void EnabelHDRBuffer(bool bHDRBuffer);
	void SetBlurBuffer(std::shared_ptr<BlurBuffer> spBlurBuffer);
	void EnabelBlurBuffer(bool bBlurBuffer);
	void SetBlurFrame(int frame);

	void EnableUseBlinn(bool bUseLinn);
	bool GetUseBlinn()const;
	bool GetBlinn()const;
	void SetBlinn(bool blinn);
	bool GetBlinnPressed()const;
	void SetBlinnPressed(bool bPress);

	void EnableUseBloom(bool bBloom);
	bool GetUseBloom()const;
	bool GetBloom()const;
	void SetBloom(bool bBloom);
	void SetBloomPressed(bool bPress);
	bool GetBloomPressed()const;

	void EnableUseGamma(bool bEnable);
	bool GetUseGamma()const;
	bool GetGamma()const;
	void SetGamma(bool bGamma);
	void SetGammaPressed(bool bPress);
	bool GetGammaPressed()const;

	void EnabelUseExposure(bool bExposure);
	bool GetUseExpusure()const;
	float GetExposure() const;
	void SetExposure(float fExposure);

	void SetDepthMappingBuffer(std::shared_ptr<DepthBuffer> spDepthBuffer);
	void EnableDepthMappingBuffer(bool bEnableDepthBuffer);
	void SetLightSpaceMatrix(const glm::mat4& matLightSpace);
	void EnableLightSpace(bool bEnable);

	void SetCubeLightSpaceMatrix(const std::vector<glm::mat4>& vecMatLightSpace);
	void EnabelCubeLightSpace(bool bEnable);

	void EnableUseShadow(bool bUseShadow);
	bool GetUseShadow()const;
	bool GetShadow()const;
	void SetShadow(bool Shadow);
	bool GetShadowPressed()const;
	void SetShadowPressed(bool bPress);

	void EnabelNearAndFar(bool bEnable);
	void SetNearAndFar(float fnear, float ffar);

	void EnabelUseHightScale(bool bHeightScale);
	bool GetUseHightScale()const;
	float GetHightScale() const;
	void SetHightScale(float fHeightScale);

private:

	glm::vec4 m_vec4BackGround;

	bool m_bBlend;
	std::shared_ptr<Blend> m_spBlend;

	bool m_bDepthTest;
	GLenum m_glDepthFunc;

	bool m_bStencil;
	std::shared_ptr<Stencil> m_spStencil;

	bool m_bCullFace;
	std::shared_ptr<CullFace> m_spCullFace;

	int m_iVertices;
	POLYGON_MODE m_ePolygonMode;
	DRAW_MODE m_eDrawMode;
	PRIMITIVE_MODE m_ePrimitiveMode;

	glm::mat4 m_matModel;

	std::shared_ptr<Shader> m_spShader;
	std::shared_ptr<Texture> m_spTexture;
	std::vector<std::shared_ptr<Light>> m_vecLights;

	bool m_bFrameBuffer;
	bool m_bClearFrameBuffer;
	std::shared_ptr<FrameBuffer> m_spFrameBuffer;

	bool m_bGBuffer;
	bool m_bCopyGBufferDepth;
	std::shared_ptr<GBuffer> m_spGBuffer;

	std::shared_ptr<UniformBuffer> m_spUniformBuffer;
	bool m_bUniformBuffer;
	bool m_bUpdateUniformBuffer;

	bool m_bSkyBox;
	bool m_bExplode;

	bool m_bMultiSample;
	bool m_bMASS;
	std::shared_ptr<MSAAInfo> m_spMSAAInfo;

	bool m_bHDRBuffer;
	std::shared_ptr<HDRBuffer> m_spHDRBuffer;
	bool m_bBlurBuffer, m_bHorizontal, m_bFirst;
	std::shared_ptr<BlurBuffer> m_spBlurBuffer;
	int m_iFrame;

	bool m_bUseBlinn;
	bool m_blinn;
	bool m_bBlinnPressed;

	bool m_bUseBloom;
	bool m_bBloom;
	bool m_bBloomPressed;

	bool m_bUseGamma;
	bool m_bGamma;
	bool m_bGammaPressed;

	bool m_bUseExposure;
	float m_fExposure;

	bool m_bEnableDepthBuffer;
	std::shared_ptr<DepthBuffer> m_spDepthBuffer;

	bool m_bEnabelLightSpace;
	glm::mat4 m_matLightSpaceMatrix;
	bool m_bEnableCubeLightSpace;
	std::vector<glm::mat4> m_vecLightSpaceMatrix;

	bool m_bUseShadow;
	bool m_bShadow;
	bool m_bShadowPressed;

	bool m_bEnableFarAndNear;
	float m_fNear;
	float m_fFar;

	bool m_bEnabelHightScale;
	float m_fHeightScale;
};