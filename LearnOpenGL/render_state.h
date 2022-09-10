#pragma once
#include "glm/glm.hpp"
#include "shader.h"
#include "texture.h"
#include "camera.h"
#include "transform.h"
#include "light.h"

enum POLYGON_MODE
{
	POINT_MODE = 0,
	LINE_MODE,
	FACE_MODE
};

enum DRAW_MODE
{
	ARRAY_MODE = 0,
	ELEMENT_MODE
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


class RenderState
{
public:
	RenderState(std::shared_ptr<Shader>spShader, std::shared_ptr<Texture>spTexture = nullptr);
	~RenderState();

	void SetLights(const std::vector<std::shared_ptr<Light>>& vecLights);
	void AddLight(std::shared_ptr<Light> spLight);

	void Use();
	void ApplyState();
	void ApplyTexture();
	void ApplyTransform(std::shared_ptr<Camera>spCamera);
	void ApplyLights(std::shared_ptr<Camera> spCamera);

	void SetBlend(float fBlend);
	void SetDepthTest(bool bDepthTest);

	void SetModelMatrix(const glm::mat4& matModel);

	void SetPatchVertices(int iVertices);
	int GetPatchVerteics() const;

	void SetDrawMode(DRAW_MODE eDrawMode);
	DRAW_MODE GetDrawMode()const;

	void SetPrimitiveMode(PRIMITIVE_MODE ePrimitiveMode);
	PRIMITIVE_MODE GetPrimitiveMode()const;

	void SetPolygonMode(POLYGON_MODE polygonMode);

private:
	float m_fBlend;
	bool m_bBlend;

	bool m_bDepthTest;

	int m_iVertices;
	POLYGON_MODE m_ePolygonMode;
	DRAW_MODE m_eDrawMode;
	PRIMITIVE_MODE m_ePrimitiveMode;

	glm::mat4 m_matModel;

	std::shared_ptr<Shader> m_spShader;
	std::shared_ptr<Texture> m_spTexture;
	std::vector<std::shared_ptr<Light>> m_vecLights;
};