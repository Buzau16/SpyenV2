#include "Camera.h"

#include "Scene/Entity.h"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>


namespace Spyen {
	Camera::Camera(const glm::vec2& position, const glm::ivec2& bounds, float zoom) : m_Position(position), m_Zoom(zoom)
	{
		m_Proj = glm::ortho(0.0f, static_cast<float>(bounds.x), 0.0f, static_cast<float>(bounds.y));
	}
	glm::mat4 Camera::GetViewProjMatrix() const
	{
		return m_Proj;
	}

	void Camera::UpdateMatrices(uint32_t width, uint32_t height)
	{
		m_View = glm::translate(glm::mat4(1.f), glm::vec3(-m_Position.x, -m_Position.y, 0.0f));

		glm::mat4 zoomMatrix = glm::scale(glm::mat4(1.f), glm::vec3(m_Zoom, m_Zoom, 1.0f));

		glm::mat4 recenterMatrix = glm::translate(glm::mat4(1.f), glm::vec3(width / 2, height / 2, 0.0f));

		m_View = recenterMatrix * zoomMatrix * m_View;
	}

	void Camera::Follow(Entity entity)
	{
		// to be implemented
	}
}
