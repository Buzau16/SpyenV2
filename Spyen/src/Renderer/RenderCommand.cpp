#include "spypch.h"
#include "RenderCommand.h"

#include "glad/glad.h"

#include "VertexArray.h"

namespace Spyen {
	void RenderCommand::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);
	}
	void RenderCommand::Clear(uint32_t mask)
	{
		glClear(mask);
	}
	void RenderCommand::ClearColor(const Vec3& color, const float alpha)
	{
		glClearColor(color.x, color.y, color.z, alpha);
	}
	void RenderCommand::DrawIndexed(VertexArray* va, uint32_t indexcount)
	{
		va->Bind();
		glDrawElements(GL_TRIANGLES, indexcount, GL_UNSIGNED_INT, nullptr);
	}
	void RenderCommand::DrawLines(VertexArray* va, uint32_t vertexcount)
	{
		va->Bind();
		glDrawArrays(GL_LINES, 0, vertexcount);
	}
	void RenderCommand::SetLineWidth(float width)
	{
		glLineWidth(width);
	}
}