#include "light.h"

Light::Light() :
	m_eLightType(LightType::POINT_LIGHT), 
	m_vec3Ambient(glm::vec3(0.f)), m_vec3Diffuse(glm::vec3(0.f)),
	m_vec3Specular(glm::vec3(0.f)), m_fShininess(32.f),
	m_vec3Color(glm::vec3(1.f))
{

}

Light::~Light()
{

}

void Light::SetLightType(LightType eLightType)
{
	m_eLightType = eLightType;
}

LightType Light::GetLightType()const
{
	return m_eLightType;
}

void Light::SetAmbient(const glm::vec3& vec3Ambient)
{
	m_vec3Ambient = vec3Ambient;
}

const glm::vec3& Light::GetAmbient()const
{
	return m_vec3Ambient;
}

void Light::SetDiffuse(const glm::vec3& vec3Diffuse)
{
	m_vec3Diffuse = vec3Diffuse;
}

const glm::vec3& Light::GetDiffuse()const
{
	return m_vec3Diffuse;
}

void Light::SetSpecular(const glm::vec3& vec3Specular, float fShiness)
{
	m_vec3Specular = vec3Specular;
	m_fShininess = fShiness;
}

const glm::vec3& Light::GetSpecular()const
{
	return m_vec3Specular;
}

float Light::GetShiness()const
{
	return m_fShininess;
}

void Light::SetColor(const glm::vec3& vec3Color)
{
	m_vec3Color = vec3Color;
}

const glm::vec3& Light::GetColor() const
{
	return m_vec3Color;
}

DirLight::DirLight():m_vec3Direction(glm::vec3(0.f))
{

}

DirLight::~DirLight()
{

}

void DirLight::SetLightDirection(const glm::vec3& vec3Direction)
{
	m_vec3Direction = vec3Direction;
}

const glm::vec3& DirLight::GetLightDirction()const
{
	return m_vec3Direction;
}

PointLight::PointLight() :m_vec3Position(glm::vec3(0.f)),
m_fConstant(1.f), m_fLinear(0.09f), m_fQuaratic(0.032f)
{

}

PointLight::~PointLight()
{

}

void PointLight::SetLightPosition(const glm::vec3& vec3Position)
{
	m_vec3Position = vec3Position;
}

const glm::vec3& PointLight::GetLightPosition()const
{
	return m_vec3Position;
}

void PointLight::SetConstant(float fConstant)
{
	m_fConstant = fConstant;
}

float PointLight::GetConstant()const
{
	return m_fConstant;
}

void PointLight::SetLinear(float fLinear)
{
	m_fLinear = fLinear;
}

float PointLight::GetLinear()const
{
	return m_fLinear;
}

void PointLight::SetQuartic(float fQuaric)
{
	m_fQuaratic = fQuaric;
}

float PointLight::GetQuartic()const
{
	return m_fQuaratic;
}

SpotLight::SpotLight() :m_vec3Position(glm::vec3(0.f)), m_vec3ViewDirection(glm::vec3(0.f)),
m_fConstant(1.f), m_fLinear(0.09f), m_fQuaratic(0.032f),
m_fCutOff(12.5f), m_fOuterCutOff(15.f)
{

}

SpotLight::~SpotLight()
{

}

void SpotLight::SetLightPosition(const glm::vec3& vec3Position)
{
	m_vec3Position = vec3Position;
}

const glm::vec3& SpotLight::GetLightPosition()const
{
	return m_vec3Position;
}

void SpotLight::SetLightDirection(const glm::vec3& vec3Direction)
{
	m_vec3ViewDirection = vec3Direction;
}

const glm::vec3& SpotLight::GetLightDirction()const
{
	return m_vec3ViewDirection;
}

void SpotLight::SetConstant(float fConstant)
{
	m_fConstant = fConstant;
}

float SpotLight::GetConstant()const
{
	return m_fConstant;
}

void SpotLight::SetLinear(float fLinear)
{
	m_fLinear = fLinear;
}

float SpotLight::GetLinear()const
{
	return m_fLinear;
}

void SpotLight::SetQuartic(float fQuaric)
{
	m_fQuaratic = fQuaric;
}

float SpotLight::GetQuartic()const
{
	return m_fQuaratic;
}

void SpotLight::SetCutOff(float fCutOff)
{
	m_fCutOff = fCutOff;
}

float SpotLight::GetCutOff()const
{
	return m_fCutOff;
}

void SpotLight::SetOuterCutOff(float fOuterCutOff)
{
	m_fOuterCutOff = fOuterCutOff;
}

float SpotLight::GetOuterCutOff()const
{
	return m_fOuterCutOff;
}