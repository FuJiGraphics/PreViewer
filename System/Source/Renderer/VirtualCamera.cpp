#include <pch.h>
#include "VirtualCamera.h"

namespace PreViewer {

	OrthogonalCamera::OrthogonalCamera(float left, float right, float bottom, float top)
		: m_Proj(glm::ortho(left, right, bottom, top, -1.0f, 1.0f))
		, m_Pos(0.0f, 0.0f, 0.0f)
	{
		SetCalculateViewProj();
	}

	void OrthogonalCamera::SetPosition(const glm::vec3& pos)
	{
		m_Pos = pos;
		SetCalculateViewProj();
	}

	void OrthogonalCamera::SetRotation(const float& angle, const EularAngle& type)
	{
		switch (type)
		{
		case EularAngle::Pitch: m_Pitch = glm::radians(-angle); break;
		case EularAngle::Yaw:   m_Yaw = glm::radians(-angle); break;
		case EularAngle::Roll:  m_Roll = glm::radians(-angle); break;
		// default: NR_CORE_ASSERT(false, "Unexpected Error : Failed to binding EularAngle");
		}

		SetCalculateViewProj();
	}

	void OrthogonalCamera::SetScale(const float scale)
	{
		m_Scale = scale;
		SetCalculateViewProj();
	}

	void OrthogonalCamera::SetCalculateViewProj()
	{
		const glm::mat4& translation = glm::translate(glm::mat4(1.0f), m_Pos);

		const glm::mat4& scale = glm::scale(glm::mat4(1.0f), glm::vec3(m_Scale));
		// --- Roll-Pitch-Yaw ¼ø¼­
		const glm::mat4& rotation =
			glm::rotate(glm::mat4(1.0f), m_Yaw, glm::vec3(0.0f, 1.0f, 0.0f)) *
			glm::rotate(glm::mat4(1.0f), m_Pitch, glm::vec3(1.0f, 0.0f, 0.0f)) *
			glm::rotate(glm::mat4(1.0f), m_Roll, glm::vec3(0.0f, 0.0f, 1.0f));

		const glm::mat4& transform = rotation * translation * scale;

		m_View = glm::inverse(transform);

		// Create a VP Matrix
		m_ViewProj = m_View * m_Proj;
	}
}