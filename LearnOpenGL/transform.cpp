#include "transform.h"

Transform::Transform() :
	m_vec3ModelPan(glm::vec3(0.0)),
	m_vec3ModelRotAxis(glm::vec3(0.0, 0.0, 1.0)),
	m_fModelRotAngle(0.0),
	m_bModelRotUseTime(false),
	m_vec3ModelScal(glm::vec3(1.0)),
	m_bModelScalUseTime(false)
{

}

Transform::~Transform()
{

}

glm::mat4 Transform::GetModelMatrix() const
{
	glm::mat4 model = glm::mat4(1.0f);

	glm::mat4 mat4Tran = glm::translate(model, m_vec3ModelPan);

	glm::mat4 mat4Rot = glm::rotate(mat4Tran, glm::radians(m_fModelRotAngle), m_vec3ModelRotAxis);

	glm::mat4 mat4Scal = glm::scale(mat4Rot, m_vec3ModelScal);

	return mat4Scal ;
}

void Transform::SetModelPan(const glm::vec3& vec3Pan)
{
	m_vec3ModelPan = vec3Pan;
}

void Transform::SetModelRotAngle(float fAngle)
{
	m_fModelRotAngle = fAngle;
}

void Transform::SetModelRotAixs(const glm::vec3& vec3RotAixs)
{
	m_vec3ModelRotAxis = vec3RotAixs;
}

void Transform::SetModelRotUseTime(bool bUseTime /*= true*/)
{
	m_bModelRotUseTime = bUseTime;
}

bool Transform::GetModelRotUseTime()const
{
	return m_bModelRotUseTime;
}

void Transform::SetModelScale(const glm::vec3& vec3Scal)
{
	m_vec3ModelScal = vec3Scal;
}

void Transform::SetModelScalUseTime(bool bUseTime /*= true*/)
{
	m_bModelScalUseTime = bUseTime;
}

bool Transform::GetModelScalUseTime()const
{
	return m_bModelScalUseTime;
}