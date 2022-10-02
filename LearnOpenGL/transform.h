#pragma once
#include "common.h"

class Transform
{
public:
	Transform();
	~Transform();
	glm::mat4 GetModelMatrix() const;

	void SetModelPan(const glm::vec3& vec3Pos);

	void SetModelRotAngle(float fAngle);
	void SetModelRotAixs(const glm::vec3& vec3RotAixs);
	void SetModelRotUseTime(bool bUseTime = true);
	bool GetModelRotUseTime()const;

	void SetModelScale(const glm::vec3& vec3Scal);
	void SetModelScalUseTime(bool bUseTime = true);
	bool GetModelScalUseTime()const;
private:

	glm::vec3 m_vec3ModelPan;

	glm::vec3 m_vec3ModelRotAxis;
	float m_fModelRotAngle;
	bool m_bModelRotUseTime;

	glm::vec3 m_vec3ModelScal;
	bool m_bModelScalUseTime;
};