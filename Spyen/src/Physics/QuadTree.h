#pragma once
#include <vector>

#include "Renderer/Renderer.h"

namespace Spyen {
	struct Point
	{
		int32_t x, y;
	};

	struct Boundary
	{
		int32_t x, y, w, h;

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
		~QuadTree() = default;

		void Subdivide();
		bool Insert(const Point& p);
		std::vector<Point> Query(const Boundary& boundary) const;


		// For debbuging
		void Draw(Renderer* renderer);


	private:
		QuadTree* m_NorthWest = nullptr;
		QuadTree* m_NorthEast = nullptr;
		QuadTree* m_SouthWest = nullptr;
		QuadTree* m_SouthEast = nullptr;
		bool m_IsDivided = false;
		std::vector<Point> m_Points;
		Boundary m_Boundary;
		uint32_t m_Capacity = 0;
	};

}

