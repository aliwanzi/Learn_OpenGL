#pragma once
#include "glm/glm.hpp"

enum LightType
{
	DIR_LIGHT = 0,
	POINT_LIGHT,
	SPOT_LIGHT
};

class Light
{
public:
	Light();
	virtual ~Light();
	void SetLightType(LightType eLightType);
	LightType GetLightType()const;

	void SetAmbient(const glm::vec3& vec3Ambient);
	const glm::vec3& GetAmbient()const;
	void SetDiffuse(const glm::vec3& vec3Diffuse);
	const glm::vec3& GetDiffuse()const;
	void SetSpecular(const glm::vec3& vec3Specular,float fShiness);
	const glm::vec3& GetSpecular()const;
	float GetShiness()const;

private:
	LightType m_eLightType;

	glm::vec3 m_vec3Ambient;
	glm::vec3 m_vec3Diffuse;
	glm::vec3 m_vec3Specular;
	float m_fShininess;
};

class DirLight:public Light
{
public:
	DirLight();
	virtual ~DirLight();
	void SetLightDirection(const glm::vec3& vec3Direction);
	const glm::vec3& GetLightDirction()const;

private:
	glm::vec3 m_vec3Direction;
};

class PointLight :public Light
{
public:
	PointLight();
	virtual ~PointLight();

	void SetLightPosition(const glm::vec3& vec3Position);
	const glm::vec3& GetLightPosition()const;

	void SetConstant(float fConstant);
	float GetConstant()const;
	void SetLinear(float fLinear);
	float GetLinear()const;
	void SetQuartic(float fQuaric);
	float GetQuartic()const;
	void SetRadius(float fRadius);
	float GetRadius()const;

private:
	glm::vec3 m_vec3Position;
	float m_fConstant;
	float m_fLinear;
	float m_fQuaratic;
	float m_fRadius;
};

class SpotLight :public Light
{
public:
	SpotLight();
	virtual ~SpotLight();

	void SetLightPosition(const glm::vec3& vec3Position);
	const glm::vec3& GetLightPosition()const;
	void SetLightDirection(const glm::vec3& vec3Direction);
	const glm::vec3& GetLightDirction()const;

	void SetConstant(float fConstant);
	float GetConstant()const;
	void SetLinear(float fLinear);
	float GetLinear()const;
	void SetQuartic(float fQuaric);
	float GetQuartic()const;

	void SetCutOff(float fCutOff);
	float GetCutOff()const;
	void SetOuterCutOff(float fOuterCutOff);
	float GetOuterCutOff()const;

private:
	glm::vec3 m_vec3Position;
	glm::vec3 m_vec3ViewDirection;

	float m_fConstant;
	float m_fLinear;
	float m_fQuaratic;

	float m_fCutOff;
	float m_fOuterCutOff;
};

