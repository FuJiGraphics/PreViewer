#pragma once
#include <Core/Core.h>
#include "VirtualCamera.h"

namespace PreViewer {

	class CameraManager
	{
	public:
		CameraManager(const float aspectRatio, bool rotation = false);
		~CameraManager() = default;

		// void OnEvent(Event& event);
		// void OnUpdate(const float& dt);

		inline void ActivateRotation(bool enable) { m_OnRotation = enable; }

		inline VirtualCamera& GetCamera() { return *m_Camera; }
		inline const PrePtr<VirtualCamera>& GetCamera() const { return m_Camera; }

	protected:
		// bool OnMouseScrolled(MouseInputData event);

	private:
		float		m_Angle;
		float		m_Zoom;
		bool		m_OnRotation;
		glm::vec3	m_CameraPos;

		float	m_MoveSpeed = 1.0f;
		float	m_RotSpeed  = 1.0f;
		float	m_ZoomSpeed = 1.0f;

		PrePtr<VirtualCamera> m_Camera;
	};


} // namespace Normal