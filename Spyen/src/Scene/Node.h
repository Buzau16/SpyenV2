#pragma once

#include <Math/glm/glm.hpp>
#include <Time/TimeStep.h>
#include <Scene/Components.h>
#include <memory>
#include <optional>
#include <vector>
#include <string>

namespace Spyen {
	class Renderer;

	class Node
	{
	public:
		Node() = default;
		virtual ~Node() = default;

		virtual void OnInit();
		virtual void OnUpdate(Timestep dt);
		virtual void OnRender(Renderer* renderer) {};

		Vec2 GetPosition() const noexcept; 
		void SetPosition(const Vec2& value) noexcept;

		Vec2 GetScale() const noexcept;
		void SetScale(const Vec2& value) noexcept;

		float GetRotation() const noexcept;
		void SetRotation(const float value) noexcept;

		std::string GetName() const noexcept;
		void SetName(const std::string& value) noexcept;

		std::optional<RigidBody> GetRigidBody() const noexcept;
		RigidBody& RGetRigidBody() noexcept;
		bool HasRigidBody() const noexcept;

		bool IsTransformDirty() const noexcept;
		void ClearDirtyFlag() noexcept;

		template<typename... Args>
		RigidBody& AddRigidBody(Args&&... args) {
			m_RigidBody.emplace(std::forward<Args>(args)...);
			return m_RigidBody.value();
		}

		void AddScript(std::unique_ptr<ScriptComponent> script);

		void AddChild(std::unique_ptr<Node> child);

		static std::unique_ptr<Node> Create();
	private:
		std::optional<RigidBody> m_RigidBody;
		std::vector<std::unique_ptr<Node>> m_Children;
		std::vector<std::unique_ptr<ScriptComponent>> m_Scripts;
	protected:
		std::string Name;
		Vec2 Position { 0,0 };
		Vec2 Scale{ 100.f, 100.f };
		float Rotation = 0.f;
	private:
		Node* m_Parent = nullptr;	
		bool m_IsTransformDirty = false;
	};


}
