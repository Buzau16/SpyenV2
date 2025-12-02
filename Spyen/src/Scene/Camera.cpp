#include "spypch.h"
#include "Camera.h"
#include <Math/glm/gtc/matrix_transform.hpp>
#include <Core/Director.h>

namespace Spyen {
    void Camera::OnInit()
    {
        Node::OnInit();

        auto d = Director::GetWindowDimensions();
        uint64_t weird = 0;
        switch (m_Type) {
        case CameraType::NONE:
            SPY_CORE_ERROR("No camera type set, falling back to a orthographic projection!");
            m_Projection = glm::ortho(weird, d.x, weird, d.y);
            break;
        case CameraType::Orthographic:
            m_Projection = glm::ortho(weird, d.x, weird, d.y);
            break;
        case CameraType::Perspective:
            m_Projection = glm::perspective(glm::radians(90.f), static_cast<float>(d.x) / d.y, 0.1f, 1.f);
            break;
        }
    }
    void Camera::OnUpdate(Timestep dt)
    {
        Node::OnUpdate(dt);

        if (IsTransformDirty()) {
            RecalculateView();
            ClearDirtyFlag();
        }        
    }
    void Camera::SetCameraType(CameraType type) noexcept
    {
        m_Type = type;
    }

    glm::mat4 Camera::GetViewProjection() const noexcept
    {
        return m_View * m_Projection;
    }
    void Camera::RecalculateView()
    {
        
    }
}