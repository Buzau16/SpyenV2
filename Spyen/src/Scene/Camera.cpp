#include "spypch.h"
#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <Core/Director.h>
#include <Events/WindowEvents.h>
#include <Core/Defines.h>

namespace Spyen {
    void Camera::OnInit()
    {
        Node::OnInit();

        auto d = Director::GetWindowDimensions();
        switch (m_Type) {
        case CameraType::NONE:
            SPY_CORE_ERROR("No camera type set, falling back to a orthographic projection!");
            m_Projection = glm::ortho(0.f, d.x, 0.f, d.y);
            break;
        case CameraType::Orthographic:
            m_Projection = glm::ortho(0.f, d.x, 0.f, d.y);
            break;
        case CameraType::Perspective:
            //m_Projection = glm::perspective(glm::radians(90.f), d.x / d.y, 0.1f, 1.f);
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
    void Camera::OnEvent(Event& event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<WindowResizedEvent>([this](const WindowResizedEvent& event) {return RecalculateProjection(event.GetWidth(), event.GetHeight()); });
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
    bool Camera::RecalculateProjection(uint32_t width, uint32_t height)
    {
        m_Projection = glm::ortho(0.f, (float)width, 0.f, (float)height);
        return true;
    }
}