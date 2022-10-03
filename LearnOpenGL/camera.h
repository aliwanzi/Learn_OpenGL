#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum Movement
{
	FORWARD = 1,
	BACKWARD,
	LEFT,
	RIGHT
};

class Camera
{
public:
	Camera(glm::vec3 vec3Eye, float fYaw = -90.f, float fPicth = 0.0f);

	void ProcessKeyboard(Movement direction, float deltaTime);
	void ProcessMouseMovement(float fXOffset, float fYOffset, bool bConstrainPitch = true);
	void ProcessMouseScroll(float fYOffset);

	void SetEye(const glm::vec3& vec3Eye);
	void SetLookAt(const glm::vec3& vec3LookAt);
	void SetNearAndFar(float fNear, float fFar);

	glm::mat4 GetViewMatrixRemoveTranslate();
	glm::mat4 GetViewMatrix() const;
	void SetViewUseTime(bool bUseTime = true);
	bool GetViewUseTime()const;

	glm::mat4 GetProjectionMatrix()const;
	void SetFOV(int iWidth, int iHeight);

	const glm::vec3& GetEye()const;
	const glm::vec3& GetViewDirection()const;
private:
	void UpdateCameraVectors();

private:
	glm::vec3 m_vec3Eye;
	glm::vec3 m_vec3LookAt;
	glm::vec3 m_vec3ViewDirection;

	glm::vec3 m_vec3Up;
	glm::vec3 m_vec3Right;

	float m_fYaw;
	float m_fPitch;
	float m_fNear;
	float m_fFar;

	float m_fMovementSpeed;
	float m_fMouseSensitivity;
	float m_fZoom;

	int m_iWidth;
	int m_iHeight;

	bool m_bUseViewTime;
};