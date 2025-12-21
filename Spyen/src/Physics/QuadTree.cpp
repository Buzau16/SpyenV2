#include "spypch.h"
#include "QuadTree.h"
#include <Scene/Components.h>

namespace Spyen {
	QuadTree::QuadTree(Boundary boundary, uint32_t capacity) : m_Boundary(boundary), m_Capacity(capacity)
	{
		m_Entities.reserve(capacity);
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

	bool QuadTree::Insert(ColliderEntity& entity)
	{
		if (!m_Boundary.Contains({ entity.ColliderPos.x, entity.ColliderPos.x }))
		{
			return false;
		}
		if (m_Entities.size() < m_Capacity && m_IsDivided == false)
		{
			m_Entities.push_back(entity);
			return true;
		}
		if (!m_IsDivided)
			Subdivide();

		if (m_NorthWest->Insert(entity)) return true;
		if (m_NorthEast->Insert(entity)) return true;
		if (m_SouthWest->Insert(entity)) return true;
		if (m_SouthEast->Insert(entity)) return true;

		return false;
	}

	std::vector<ColliderEntity> QuadTree::Query(const Boundary& boundary)
	{
		std::vector<ColliderEntity> Entities;

		if (!m_Boundary.Intersects(boundary)) {
			return Entities;
		}

		for (auto& entity : m_Entities) {
			if (boundary.Contains({ entity.ColliderPos.x, entity.ColliderPos.y }))
			{
				Entities.push_back(entity);
			}
		}

		if (!m_IsDivided) {
			return Entities;
		}

		for (auto& e : m_NorthWest->Query(boundary))
		{
			Entities.push_back(e);
		}
		for (auto& e : m_NorthEast->Query(boundary))
		{
			Entities.push_back(e);
		}
		for (auto& e : m_SouthWest->Query(boundary))
		{
			Entities.push_back(e);
		}
		for (auto& e : m_SouthEast->Query(boundary))
		{
			Entities.push_back(e);
		}

		return Entities;
	}


	void QuadTree::Draw(Renderer* renderer) const
	{
		uint32_t offset = 2;
		
		float left = (m_Boundary.x - m_Boundary.w / 2) + 2;
		float right = m_Boundary.x + m_Boundary.w / 2;
		float top = m_Boundary.y + m_Boundary.h / 2;
		float bottom = (m_Boundary.y - m_Boundary.h / 2) + 2;
		//bottom left -> bottom right
		//renderer->DrawLine({ left, bottom }, {right, bottom}, { 0.0f, 0.0f, 0.0f });
		//// bottom right -> top right
		//renderer->DrawLine({ right, bottom }, {right, top}, { 0.0f, 0.0f, 0.0f });
		//// top right -> top left
		//renderer->DrawLine({ right, top }, {left, top}, { 0.0f, 0.0f, 0.0f });
		//// top left -> bottom left
		//renderer->DrawLine({ left, top }, {left, bottom}, { 0.0f, 0.0f, 0.0f });

		if (m_IsDivided)
		{
			m_NorthWest->Draw(renderer);
			m_NorthEast->Draw(renderer);
			m_SouthWest->Draw(renderer);
			m_SouthEast->Draw(renderer);
		}
	}
}
