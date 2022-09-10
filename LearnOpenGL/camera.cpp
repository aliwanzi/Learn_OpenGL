#include "camera.h"
#include <algorithm>

Camera::Camera(glm::vec3 vec3Eye, float fYaw /*= -90.f*/, float fPicth /*= 0.0f*/) :
	m_vec3Eye(vec3Eye), m_fYaw(fYaw), m_fPitch(fPicth),
	m_fMovementSpeed(2.5f), m_fMouseSensitivity(0.1f), m_fZoom(45.0f),
	m_iWidth(0.f), m_iHeight(0.f), m_bUseViewTime(false)
{
	UpdateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix()const
{
	return glm::lookAt(m_vec3Eye, m_vec3LookAt, m_vec3Up);
}

void Camera::SetFOV(int iWidth, int iHeight)
{
	m_iWidth = iWidth;
	m_iHeight = iHeight;
}

glm::mat4 Camera::GetProjectionMatrix()const
{
	return glm::perspective(glm::radians(m_fZoom),
		static_cast<float>(m_iWidth) / static_cast<float>(m_iHeight), 0.1f, 100.0f);
}

void Camera::ProcessKeyboard(Movement direction, float deltaTime)
{
	float velocity = m_fMovementSpeed * deltaTime;
	switch (direction)
	{
	case FORWARD:
		m_vec3Eye += m_vec3ViewDirection * velocity;
		break;
	case BACKWARD:
		m_vec3Eye -= m_vec3ViewDirection * velocity;
		break;
	case LEFT:
		m_vec3Eye -= m_vec3Right * velocity;
		break;
	case RIGHT:
		m_vec3Eye += m_vec3Right * velocity;
		break;
	default:
		break;
	}

	UpdateCameraVectors();
}

void Camera::ProcessMouseMovement(float fXOffset, float fYOffset, bool bConstrainPitch/* = true*/)
{
	float fOffsetX = fXOffset * m_fMouseSensitivity;
	float fOffsetY = fYOffset * m_fMouseSensitivity;

	m_fYaw += fOffsetX;

	m_fPitch += fOffsetY;
	m_fPitch = bConstrainPitch ? std::clamp(m_fPitch, -89.0f, 89.0f) : m_fPitch;

	UpdateCameraVectors();
}

void Camera::UpdateCameraVectors()
{
	glm::vec3 vecViewDir;
	vecViewDir.x = cos(glm::radians(m_fYaw)) * cos(glm::radians(m_fPitch));
	vecViewDir.y = sin(glm::radians(m_fPitch));
	vecViewDir.z = sin(glm::radians(m_fYaw)) * cos(glm::radians(m_fPitch));

	m_vec3ViewDirection = glm::normalize(vecViewDir);
	m_vec3Right = glm::normalize(glm::cross(m_vec3ViewDirection, glm::vec3(0.f, 1.f, 0.f)));
	m_vec3Up = glm::normalize(glm::cross(m_vec3Right, m_vec3ViewDirection));

	m_vec3LookAt = m_vec3Eye + vecViewDir;
}

void Camera::ProcessMouseScroll(float fYOffset)
{
	m_fZoom -= fYOffset;
	m_fZoom = std::clamp(m_fZoom, 1.0f, 45.0f);
}

void Camera::SetEye(const glm::vec3& vec3Eye)
{
	m_vec3Eye = vec3Eye;
}

void Camera::SetLookAt(const glm::vec3& vec3LookAt)
{
	m_vec3LookAt = vec3LookAt;
}

void Camera::SetViewUseTime(bool bUseTime /*= true*/)
{
	m_bUseViewTime = bUseTime;
}

bool Camera::GetViewUseTime()const
{
	return m_bUseViewTime;
}

const glm::vec3& Camera::GetEye()const
{
	return m_vec3Eye;
}

const glm::vec3& Camera::GetViewDirection()const
{
	return m_vec3ViewDirection;
}
