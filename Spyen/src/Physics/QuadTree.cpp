#include "QuadTree.h"


namespace Spyen {
	QuadTree::QuadTree(Boundary boundary, uint32_t capacity) : m_Boundary(boundary), m_Capacity(capacity)
	{
		m_Points.reserve(capacity);
	}

	void QuadTree::Subdivide()
	{
		int32_t halfW = m_Boundary.w / 2;
		int32_t halfH = m_Boundary.h / 2;

		m_NorthWest = new QuadTree({ m_Boundary.x - halfW / 2, m_Boundary.y + halfH / 2, halfW, halfH }, m_Capacity);
		m_NorthEast = new QuadTree({ m_Boundary.x + halfW / 2, m_Boundary.y + halfH / 2, halfW, halfH }, m_Capacity);
		m_SouthWest = new QuadTree({ m_Boundary.x - halfW / 2, m_Boundary.y - halfH / 2, halfW, halfH }, m_Capacity);
		m_SouthEast = new QuadTree({ m_Boundary.x + halfW / 2, m_Boundary.y - halfH / 2, halfW, halfH }, m_Capacity);

		m_IsDivided = true;
	}

	bool QuadTree::Insert(const Point& p)
	{
		if (!m_Boundary.Contains(p))
		{
			return false;
		}
		if (m_Points.size() < m_Capacity && m_IsDivided == false)
		{
			m_Points.push_back(p);
			return true;
		}
		if (!m_IsDivided)
			Subdivide();

		if (m_NorthWest->Insert(p)) return true;
		if (m_NorthEast->Insert(p)) return true;
		if (m_SouthWest->Insert(p)) return true;
		if (m_SouthEast->Insert(p)) return true;

		return false;
	}

	std::vector<Point> QuadTree::Query(const Boundary& boundary) const
	{
		std::vector<Point> points;

		if (!m_Boundary.Intersects(boundary))
			return points;

		for (auto& p : m_Points)
		{
			if (boundary.Contains(p))
			{
				points.push_back(p);
			}
		}

		if (!m_IsDivided)
		{
			return points;
		}

		for (auto& p : m_NorthWest->Query(boundary))
		{
			points.push_back(p);
		}
		for (auto& p : m_NorthEast->Query(boundary))
		{
			points.push_back(p);
		}
		for (auto& p : m_SouthWest->Query(boundary))
		{
			points.push_back(p);
		}
		for (auto& p : m_SouthEast->Query(boundary))
		{
			points.push_back(p);
		}

		return points;
	}

	void QuadTree::Draw(Renderer* renderer)
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
