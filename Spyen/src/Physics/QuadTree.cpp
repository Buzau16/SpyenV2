#include "spypch.h"
#include "QuadTree.h"


namespace Spyen {
	QuadTree::QuadTree(Boundary boundary, uint32_t capacity) : m_Boundary(boundary), m_Capacity(capacity)
	{
		m_Colliders.reserve(capacity);
	}

	QuadTree::~QuadTree()
	{
		delete m_NorthWest;
		delete m_NorthEast;
		delete m_SouthWest;
		delete m_SouthEast;
	}

	void QuadTree::Subdivide()
	{
		float halfW = m_Boundary.w / 2;
		float halfH = m_Boundary.h / 2;

		m_NorthWest = new QuadTree({ m_Boundary.x - halfW / 2, m_Boundary.y + halfH / 2, halfW, halfH }, m_Capacity);
		m_NorthEast = new QuadTree({ m_Boundary.x + halfW / 2, m_Boundary.y + halfH / 2, halfW, halfH }, m_Capacity);
		m_SouthWest = new QuadTree({ m_Boundary.x - halfW / 2, m_Boundary.y - halfH / 2, halfW, halfH }, m_Capacity);
		m_SouthEast = new QuadTree({ m_Boundary.x + halfW / 2, m_Boundary.y - halfH / 2, halfW, halfH }, m_Capacity);

		m_IsDivided = true;
	}

	bool QuadTree::Insert(const RigidBody& box)
	{
		if (!m_Boundary.Contains({ box.GetCollider().Position.x, box.GetCollider().Position.y}))
		{
			return false;
		}
		if (m_Colliders.size() < m_Capacity && m_IsDivided == false)
		{
			m_Colliders.push_back(box);
			return true;
		}
		if (!m_IsDivided)
			Subdivide();

		if (m_NorthWest->Insert(box)) return true;
		if (m_NorthEast->Insert(box)) return true;
		if (m_SouthWest->Insert(box)) return true;
		if (m_SouthEast->Insert(box)) return true;

		return false;
	}

	std::vector<RigidBody> QuadTree::Query(const Boundary& boundary) const
	{
		std::vector<RigidBody> colliders;

		if (!m_Boundary.Intersects(boundary))
			return colliders;

		for (auto& rb : m_Colliders)
		{
			if (boundary.Contains({ rb.GetCollider().Position.x, rb.GetCollider().Position.y}))
			{
				colliders.push_back(rb);
			}
		}

		if (!m_IsDivided)
		{
			return colliders;
		}

		for (auto& p : m_NorthWest->Query(boundary))
		{
			colliders.push_back(p);
		}
		for (auto& p : m_NorthEast->Query(boundary))
		{
			colliders.push_back(p);
		}
		for (auto& p : m_SouthWest->Query(boundary))
		{
			colliders.push_back(p);
		}
		for (auto& p : m_SouthEast->Query(boundary))
		{
			colliders.push_back(p);
		}

		return colliders;
	}

	void QuadTree::Draw(Renderer* renderer) const
	{
		uint32_t offset = 2;
		
		float left = (m_Boundary.x - m_Boundary.w / 2) + 2;
		float right = m_Boundary.x + m_Boundary.w / 2;
		float top = m_Boundary.y + m_Boundary.h / 2;
		float bottom = (m_Boundary.y - m_Boundary.h / 2) + 2;
		//bottom left -> bottom right
		renderer->DrawLine({ left, bottom }, {right, bottom}, { 0.0f, 0.0f, 0.0f });
		// bottom right -> top right
		renderer->DrawLine({ right, bottom }, {right, top}, { 0.0f, 0.0f, 0.0f });
		// top right -> top left
		renderer->DrawLine({ right, top }, {left, top}, { 0.0f, 0.0f, 0.0f });
		// top left -> bottom left
		renderer->DrawLine({ left, top }, {left, bottom}, { 0.0f, 0.0f, 0.0f });

		if (m_IsDivided)
		{
			m_NorthWest->Draw(renderer);
			m_NorthEast->Draw(renderer);
			m_SouthWest->Draw(renderer);
			m_SouthEast->Draw(renderer);
		}
	}
}
