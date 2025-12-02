#include "spypch.h"
#include "NodeGraph.h"
#include <Core/Log.h>


namespace Spyen {
	void NodeGraph::AddNode(std::unique_ptr<Node> node)
	{
		m_Nodes.push_back(std::move(node));
	}

	/*void NodeGraph::RemoveNode(const std::string_view name)
	{
		std::erase_if(m_Nodes, [&](const std::unique_ptr<Node> node) {
			return node->GetName() == name;
		});
	}*/

	Node* NodeGraph::GetNode(const std::string_view name)
	{
		for (auto& node : m_Nodes) {
			if (node->GetName() == name) {
				return node.get();
			}
		}

		SPY_CORE_CRITICAL("Failed to find node {}!");
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