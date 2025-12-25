#pragma once
#include <cstdint>
#include <Math/Vector/Vec.h>

namespace Spyen {
	class VertexArray;

	class RenderCommand
	{
	public:
		static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
		static void Clear(uint32_t mask);
		static void ClearColor(const Vec3& color);

		static void DrawIndexed(VertexArray* va, uint32_t indexcount);
		static void DrawLines(VertexArray* va, uint32_t vertexcount);

		static void SetLineWidth(float width);
	};

}

