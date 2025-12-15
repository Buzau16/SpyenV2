#pragma once

#include <glm/glm.hpp>

namespace Spyen {

	// An Orthographic camera
	class SceneCamera
	{
	public:
		SceneCamera();
		~SceneCamera() = default;

		void RecalculateProjection();
		void RecalculateView();
		glm::mat4 GetViewProjection() const { return m_View * m_Proj; };

	private:
		glm::mat4 m_View{ 1.f };
		glm::mat4 m_Proj{ 1.f };
	};

}