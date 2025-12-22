#pragma once


#include <Math/Math.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Renderer/Texture.h>
#include <Core/UUID.h>
#include <Scene/SceneCamera.h>

namespace Spyen {
	struct TransformComponent {
		Vec2 Position = { 0.f, 0.f };
		Vec2 Scale = { 100.f, 100.f };
		float Rotation = 0.f;
		float ZIndex = 0.f;

		inline const glm::mat4 GetTransform() const noexcept{
			return glm::translate(glm::mat4(1.f), glm::vec3(Position.x, Position.y, ZIndex)) *
				glm::rotate(glm::mat4(1.f), glm::radians(Rotation), glm::vec3(0.f, 0.f, 1.f)) *
				glm::scale(glm::mat4(1.f), glm::vec3(Scale.x, Scale.y, 1.f));
		}
	};

	struct SpriteRenderComponent {
		Spyen::Texture* Texture = nullptr;
		glm::vec4 Color = { 1.f, 1.f, 1.f, 1.f };
	};

	struct RigidBodyComponent {
		Vec2 Velocity = { 0.f, 0.f };
		Vec2 Acceleration = { 0.f, 0.f };
		enum class BodyType{Static = 0, Dynamic, Kinematic};
		BodyType Type = BodyType::Static;
	};

	struct BoxColliderComponent {
		Vec2 Offset = { 0.f, 0.f };
		Vec2 Scale = { 1.f, 1.f }; // is multiplied by the entities Scale
		float Rotation = 0.f;
	};

	struct IDComponent {
		UUID ID = 0;
	};

	struct TagComponent {
		std::string Tag;
	};

	struct CameraComponent {
		SceneCamera Camera;
		bool MainCamera = true;
	};

	class Script;

	struct ScriptComponent {
		std::unique_ptr<Script> ScriptInstance = nullptr;
	};
}