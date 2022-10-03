#pragma once
#include "common.h"
#include "shader.h"
#include "texture.h"
#include "camera.h"
#include "transform.h"
#include "light.h"
#include "frame_buffer.h"
#include "uniform_buffer.h"

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

	std::shared_ptr<UniformBuffer> m_spUniformBuffer;
	bool m_bUniformBuffer;
	bool m_bUpdateUniformBuffer;

	bool m_bSkyBox;
	bool m_bExplode;

	bool m_bMultiSample;
	bool m_bMASS;
	std::shared_ptr<MSAAInfo> m_spMSAAInfo;
};