#pragma once
#include <Scene/Node.h>
#include <Time/TimeStep.h>
#include <Math/glm/glm.hpp>

namespace Spyen {
	enum class CameraType {
		NONE = 0, Orthographic, Perspective
	};

	class Camera : public Node
	{
	public:
		Camera() = default;
		virtual ~Camera() = default;

		virtual void OnInit() override;
		virtual void OnUpdate(Timestep dt) override;

		void SetCameraType(CameraType type) noexcept;
		glm::mat4 GetViewProjection() const noexcept;

	private:
		void RecalculateView();
		glm::mat4 m_Projection{ 1.0f };
		glm::mat4 m_View{ 1.0f };
		CameraType m_Type;
	};

}