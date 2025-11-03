#pragma once
#include <glm/glm.hpp>



namespace Spyen {
	class Entity;

	class Camera
	{
	public:
		Camera() = default;
		Camera(const glm::vec2& position, float zoom, const glm::ivec2& bounds);
		~Camera() = default;

		glm::mat4 GetViewProjMatrix() const;
		void UpdateMatrices(uint32_t width, uint32_t height);
		void Follow(Entity entity);

	private:
		glm::mat4 m_View = glm::mat4(1.0f);
		glm::mat4 m_Proj = glm::mat4(1.0f);
		glm::vec2 m_Position = {0.0f, 0.0f};
		float m_Zoom = 0.0f;
	};

}

