#include "spypch.h"
#include "SceneCamera.h"
#include <Core/Director.h>
#include <glm/gtc/matrix_transform.hpp>

namespace Spyen {
	SceneCamera::SceneCamera()
	{
		RecalculateProjection();
		RecalculateView();
	}
	void SceneCamera::RecalculateProjection()
	{
		auto dim = Director::GetWindowDimensions();
		m_Proj = glm::ortho(0.f, dim.x, 0.f, dim.y);
	}
	void SceneCamera::RecalculateView()
	{
		// to be implemented
	}
}