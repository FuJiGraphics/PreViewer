#pragma once

#include <Core/Core.h>

namespace PreViewer {

	enum class EularAngle {
		None = 0,
		Pitch, Yaw, Roll
	};

	enum class RotSpace
	{
		None = 0,
		Local, World
	};

	enum class Direction
	{
		Xaxis, Yaxis
	};

	struct DrawInfo
	{
		void AddMove(float move, Direction dir);
		void SetMove(float x, float y);
		void AddScale(float x, float y);
		void SetScale(float x, float y);
		inline glm::vec2	GetPos()	{ return { m_PosX, m_PosY }; }
		inline glm::vec2	GetScale()	{ return { m_ScaleX, m_ScaleY }; }
		inline float		GetAngle()	{ return m_Angle; }
		inline glm::vec2	GetPos()	const { return { m_PosX, m_PosY }; }
		inline glm::vec2	GetScale()	const { return { m_ScaleX, m_ScaleY }; }
		inline float		GetAngle()	const { return m_Angle; }
	private:
		float m_PosX = 0.0f, m_PosY = 0.0f;
		float m_ScaleX = 1.0f, m_ScaleY = 1.0f;
		float m_Angle = 0.0f;
	};

	// Camera Interface
	class VirtualCamera
	{
	public:
		explicit VirtualCamera() = default;
		~VirtualCamera() = default;

	public:
		inline virtual glm::mat4& GetVPMatrix() = 0;

		virtual void SetPosition(const glm::vec3& pos) = 0;
		virtual void SetRotation(const float& angle, const EularAngle& type) = 0;
		virtual void SetScale(const float scale) = 0;
	};

	// Orthogonal Projection Camera
	class OrthogonalCamera : public VirtualCamera
	{
	public:
		OrthogonalCamera(float left, float right, float bottom, float top);
		~OrthogonalCamera() = default;

	public:
		inline virtual glm::mat4& GetVPMatrix() override { return m_ViewProj; }

		virtual void SetPosition(const glm::vec3& pos) override;
		virtual void SetRotation(const float& angle, const EularAngle& type) override;
		virtual void SetScale(const float scale) override;


	private:
		void SetCalculateViewProj();

	private:
		glm::vec3 m_Pos;

		float m_Pitch = 0.0f;
		float m_Yaw = 0.0f;
		float m_Roll = 0.0f;

		float m_Scale = 1.0f;
		glm::mat4 m_View;
		glm::mat4 m_Proj;
		glm::mat4 m_ViewProj;
	};

}