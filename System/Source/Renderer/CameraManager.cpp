#include <pch.h>
#include "CameraManager.h"

namespace PreViewer {
	CameraManager::CameraManager(unsigned int width, unsigned int height, BOOL rotation)
		: m_Zoom(1.0f)
		, m_CameraPos(0.0f, 0.0f, 0.0f)
		, m_OnRotation(rotation)
		, m_Camera(nullptr)
	{
		float aspectRatio = static_cast<float>(width) / static_cast<float>(height);
		m_Camera.reset(new OrthogonalCamera(-aspectRatio * m_Zoom, aspectRatio * m_Zoom, -aspectRatio * m_Zoom, aspectRatio * m_Zoom));
	}

	CameraManager::CameraManager(const float aspectRatio, bool rotation)
		: m_Zoom(1.0f), m_CameraPos(0.0f, 0.0f, 0.0f), m_OnRotation(rotation)
		, m_Camera(new OrthogonalCamera(-aspectRatio * m_Zoom, aspectRatio * m_Zoom, -aspectRatio * m_Zoom, aspectRatio * m_Zoom))
	{ /* Empty */ }

	void CameraManager::AddMove(float move, const Direction& dir)
	{
		switch (dir)
		{
			case Direction::Xaxis:
				m_CameraPos.x += (move);
				break;
			case Direction::Yaxis:
				m_CameraPos.y += (move);
				break;
		}
		m_Camera->SetPosition(m_CameraPos);
	}

	void CameraManager::SetMove(float x, float y)
	{
		m_CameraPos.x = x;
		m_CameraPos.y = y;
		m_Camera->SetPosition(m_CameraPos);
	}

	void CameraManager::AddScale(float scale)
	{
		m_Zoom += scale;
		m_Camera->SetScale(m_Zoom);
	}

	void CameraManager::SetScale(float scale)
	{
		m_Zoom = scale;
		m_Camera->SetScale(m_Zoom);
	}

	void CameraManager::AddRotate(float angle, const EularAngle& axis)
	{
		if (m_OnRotation == FALSE)
			return;

		float* targetAngle = nullptr;
		switch (axis)
		{
			case EularAngle::Roll:	targetAngle = &m_Roll;
			case EularAngle::Pitch:	targetAngle = &m_Pitch;
			case EularAngle::Yaw:	targetAngle = &m_Yaw;
		}

		(*targetAngle) += angle;
		m_Camera->SetRotation((*targetAngle), axis);
	}

	void CameraManager::SetRotate(float angle, const EularAngle& axis)
	{
		if (m_OnRotation == FALSE)
			return;

		float* targetAngle = nullptr;
		switch (axis)
		{
			case EularAngle::Roll:	targetAngle = &m_Roll;
			case EularAngle::Pitch:	targetAngle = &m_Pitch;
			case EularAngle::Yaw:	targetAngle = &m_Yaw;
		}
		float newAngle = (*targetAngle) + angle;
		if (newAngle >= 360.0f)
			newAngle = newAngle - (glm::floor(newAngle / 360.0f) * newAngle);
		else if (newAngle <= -360.0f)
		{
			newAngle = -newAngle;
			newAngle = newAngle - (glm::floor(newAngle / 360.0f) * newAngle);
			newAngle = -newAngle;
		}
		(*targetAngle) = newAngle;
		m_Camera->SetRotation((*targetAngle), axis);
	}
	
}