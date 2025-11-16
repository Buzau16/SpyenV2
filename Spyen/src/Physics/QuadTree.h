#pragma once
#include <vector>

#include "Renderer/Renderer.h"
#include "Scene/Components.h"

namespace Spyen {

	struct Point
	{
		float x, y;
	};

	struct Boundary
	{
		float x, y, w, h;

		bool Contains(const Point& p) const noexcept
		{
			return (x - w / 2 <= p.x && p.x <= x + w / 2) &&
				(y - h / 2 <= p.y && p.y <= y + h / 2);
		}
		bool Intersects(const Boundary& b) const noexcept
		{
			return !(b.x - b.w / 2 > x + w / 2 ||
				b.x + b.w / 2 < x - w / 2 ||
				b.y - b.h / 2 > y + h / 2 ||
				b.y + b.h / 2 < y - h / 2);
		}
	};
	class QuadTree
	{
	public:
		QuadTree(Boundary boundary, uint32_t capacity);
		~QuadTree(); 

		void Subdivide();
		bool Insert(const OBB& box);
		std::vector<OBB> Query(const Boundary& boundary) const;


		// For debbuging
		void Draw(Renderer* renderer) const;
	private:
		QuadTree* m_NorthWest = nullptr;
		QuadTree* m_NorthEast = nullptr;
		QuadTree* m_SouthWest = nullptr;
		QuadTree* m_SouthEast = nullptr;
		bool m_IsDivided = false;
		std::vector<OBB> m_Colliders;
		Boundary m_Boundary;
		uint32_t m_Capacity = 0;
	};

}

