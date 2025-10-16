#pragma once

#include "Renderer/VertexArray.h"
#include "Renderer/Shader.h"

namespace Spyen {

	struct QuadVertex {
		glm::vec2 Position;
		glm::vec3 Color;
	};

	class Renderer
	{
	public:
		Renderer() = default;
		Renderer(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Renderer();

		void BeginFrame();
		void EndFrame();
		void DrawQuad(glm::vec2& position, glm::vec3& color);

	private:
		std::shared_ptr<Shader> m_Shader = nullptr;
		std::shared_ptr<VertexArray> m_VertexArray = nullptr;
		std::shared_ptr<VertexBuffer> m_VertexBuffer = nullptr;
		std::shared_ptr<IndexBuffer> m_IndexBuffer = nullptr;
		
		QuadVertex* m_QuadVertexBuffer;
		uint32_t m_QuadIndexCount = 0;
		glm::vec2 m_QuadPositions[4];
		
	};

}

