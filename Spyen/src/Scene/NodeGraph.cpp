#include "spypch.h"
#include "NodeGraph.h"
#include <Core/Log.h>


namespace Spyen {
	void NodeGraph::AddNode(std::unique_ptr<Node> node)
	{
		m_NodesToAdd.push_back(std::move(node));
	}

	void NodeGraph::RemoveNode(Node* node)
	{
		m_NodesToRemove.push_back(node);
	}
	// add something in case of the return value being a nullptpr
	Node* NodeGraph::GetNode(const std::string_view name)
	{
		for (auto& node : m_Nodes) {
			if (node->GetName() == name) {
				return node.get();
			}
		}

		SPY_CORE_CRITICAL("Failed to find node {}!", name);
		return nullptr;
	}

	std::vector<Node*> NodeGraph::GetNodesWithTag(const std::string_view tag)
	{
		std::vector<Node*> tagged_nodes;
		for (auto& node : m_Nodes) {
			if (node->GetTag() == tag) {
				tagged_nodes.push_back(node.get());
			}
		}

		return tagged_nodes;
	}

	std::vector<std::unique_ptr<Node>>::iterator NodeGraph::begin()
	{
		return m_Nodes.begin();
	}

	std::vector<std::unique_ptr<Node>>::iterator NodeGraph::end()
	{
		return m_Nodes.end();
	}

	std::vector<std::unique_ptr<Node>>::const_iterator NodeGraph::begin() const
	{
		return m_Nodes.begin();
	}

	std::vector<std::unique_ptr<Node>>::const_iterator NodeGraph::end() const
	{
		return m_Nodes.end();
	}
	void NodeGraph::ProccesDeffered()
	{
		if (!m_NodesToRemove.empty()) {
			for (auto* node : m_NodesToRemove) {

				auto it = std::find_if(
					m_Nodes.begin(),
					m_Nodes.end(),
					[&](const std::unique_ptr<Node>& ptr) {
						return ptr.get() == node;
					}
				);

				if (it != m_Nodes.end()) {
					m_Nodes.erase(it);
				}
			}

			m_NodesToRemove.clear();
		}


		if (!m_NodesToAdd.empty()) {
			for (auto& node : m_NodesToAdd) {
				node->OnInit();
				m_Nodes.push_back(std::move(node));
			}
			m_NodesToAdd.clear();
		}
	}
	/*std::vector<RigidBody> NodeGraph::GetRigidBodies() const
	{
		std::vector<RigidBody> bodies;
		for (auto& node : m_Nodes) {
			if (node->HasRigidBody()) {
				bodies.push_back(node->RGetRigidBody());
			}
		}

		return bodies;
	}*/
}