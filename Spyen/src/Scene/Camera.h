#pragma once
#include <Scene/Node.h>
#include <Time/TimeStep.h>
#include <glm/glm.hpp>
#include <Events/Event.h>

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
		virtual void OnEvent(Event& event) override;

		void SetCameraType(CameraType type) noexcept;
		glm::mat4 GetViewProjection() const noexcept;

	private:
		void RecalculateView();
		bool RecalculateProjection(uint32_t width, uint32_t height);
		glm::mat4 m_Projection{ 1.0f };
		glm::mat4 m_View{ 1.0f };
		CameraType m_Type;
	};

}