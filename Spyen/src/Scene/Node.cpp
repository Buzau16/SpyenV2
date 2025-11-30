#include "Node.h"
void Spyen::Node::AddChild(std::unique_ptr<Node> child)
{
	child->m_Parent = this;

	m_Children.push_back(std::move(child));
}

std::unique_ptr<Spyen::Node> Spyen::Node::Create()
{
	return std::make_unique<Spyen::Node>();
}
