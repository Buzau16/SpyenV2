#pragma once
#include "Node.h"
#include "Components.h"
#include <memory>
#include <string_view>
#include <vector>

namespace Spyen {
	class NodeGraph
	{
	public:
		NodeGraph() = default;
		~NodeGraph() = default;

		void AddNode(std::unique_ptr<Node> node);
		void RemoveNode(Node* node);
		Node* GetNode(const std::string_view name);
		std::vector<Node*> GetNodesWithTag(const std::string_view tag);

		std::vector<std::unique_ptr<Node>>::iterator begin();
		std::vector<std::unique_ptr<Node>>::iterator end();
		std::vector<std::unique_ptr<Node>>::const_iterator begin() const;
		std::vector<std::unique_ptr<Node>>::const_iterator end() const;

		//std::vector<RigidBody> GetRigidBodies() const;
		void ProccesDeffered();

	private:
		

		std::vector<std::unique_ptr<Node>> m_Nodes;
		std::vector<std::unique_ptr<Node>> m_NodesToAdd;
		std::vector<Node*> m_NodesToRemove;
	};

}

