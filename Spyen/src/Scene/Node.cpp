#include "spypch.h"
#include "Node.h"

#include <Core/Log.h>
#include <Core/Defines.h>

namespace Spyen {
	void Node::OnInit()
	{
		for (auto& child : m_Children) {
			child->OnInit();
		}
		for (auto& script : m_Scripts) {
			script->OnInit();
		}
	}

	void Node::OnUpdate(Timestep dt)
	{
		for (auto& child : m_Children) {
			child->OnUpdate(dt);
		}
		for (auto& script : m_Scripts) {
			script->OnUpdate(dt);
		}
	}

	void Node::OnRender(Renderer* renderer)
	{
		for (auto& child : m_Children) {
			child->OnRender(renderer);
		}
	}

	Vec2 Node::GetPosition() const noexcept {
		return Position;
	}

	void Node::SetPosition(const Vec2& value) noexcept {
		Position = value;
		m_IsTransformDirty = true;
	}

	Vec2 Node::GetScale() const noexcept {
		return Scale;
	}

	void Node::SetScale(const Vec2& value) noexcept {
		Scale = value;
		m_IsTransformDirty = true;
	}

	float Node::GetRotation() const noexcept {
		return Rotation;
	}

	void Node::SetRotation(const float value) noexcept {
		Rotation = value;
		m_IsTransformDirty = true;
	}

	std::string Node::GetName() const noexcept {
		return Name;
	}

	void Node::SetName(const std::string& value) noexcept {
		Name = value;
	}

	std::optional<RigidBody> Node::GetRigidBody() const noexcept
	{
		return HasRigidBody() ? m_RigidBody : std::nullopt;
	}

	RigidBody& Node::RGetRigidBody() noexcept
	{
		SPY_CORE_ASSERT(HasRigidBody(), "Node does not have a rigidbody component!");
		return m_RigidBody.value();
	}

	bool Node::HasRigidBody() const noexcept
	{
		return m_RigidBody.has_value();
	}

	bool Node::IsTransformDirty() const noexcept
	{
		return m_IsTransformDirty;
	}

	void Node::ClearDirtyFlag() noexcept
	{
		m_IsTransformDirty = false;
	}

	void Node::AddScript(std::unique_ptr<ScriptComponent> script)
	{
		script->Parent = this;
		m_Scripts.push_back(std::move(script));
	}

	void Node::AddChild(std::unique_ptr<Node> child)
	{
		child->m_Parent = this;

		m_Children.push_back(std::move(child));
	}

	const std::vector<std::unique_ptr<Node>>& Node::GetChildren() const
	{
		return m_Children;
	}

	std::unique_ptr<Node> Node::Create()
	{
		return std::make_unique<Node>();
	}

}
