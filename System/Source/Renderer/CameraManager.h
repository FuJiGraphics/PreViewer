#pragma once
#include <Core/Core.h>
#include "VirtualCamera.h"

namespace PreViewer {

	class CameraManager
	{
	public:
		CameraManager(unsigned int width, unsigned int height, BOOL rotation = FALSE);
		CameraManager(const float aspectRatio, bool rotation = false);
		~CameraManager() = default;

		void AddMove(float move, const Direction& dir);
		void SetMove(float x, float y);
		void AddScale(float scale);
		void SetScale(float scale);
		void AddRotate(float angle, const EularAngle& axis);
		void SetRotate(float angle, const EularAngle& axis);

		inline void ActivateRotation(bool enable) { m_OnRotation = enable; }

		inline VirtualCamera& GetCamera() { return *m_Camera; }
		inline const PrePtr<VirtualCamera>& GetCamera() const { return m_Camera; }

	protected:
		// bool OnMouseScrolled(MouseInputData event);

	private:
		float		m_Zoom;
		bool		m_OnRotation;
		glm::vec3	m_CameraPos;

		float	m_Roll = 0.0f;
		float	m_Pitch = 0.0f;
		float	m_Yaw = 0.0f;

		float	m_MoveSpeed = 1.0f;
		float	m_RotSpeed  = 1.0f;
		float	m_ZoomSpeed = 1.0f;

		PrePtr<VirtualCamera> m_Camera;
	};


} // namespace Normal