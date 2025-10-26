#pragma once

#include "SSBO.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"

namespace Spyen {

	struct QuadVertex {
		glm::vec2 Position;
		glm::vec3 Color;
		glm::vec2 TextureCoords;
		int TextureIndex;
		int TransformIndex;
	};

	class Renderer
	{
	public:
		Renderer() = default;
		Renderer(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Renderer();

		void BeginFrame();
		void EndFrame();
		
		[[deprecated]] void DrawQuad(const glm::vec2& position, const glm::vec3& color);
		
		[[deprecated]] void DrawQuad(const glm::vec2& position, const std::shared_ptr<Texture>& texture);

		void DrawQuad(const glm::mat4& transform, const glm::vec3& color);
		void DrawQuad(const glm::mat4& transform, const std::shared_ptr<Texture>& texture);

	private:
		QuadVertex* m_QuadVertexBuffer;

		std::vector<uint64_t> m_TextureHandles;
		std::vector<glm::mat4> m_TransformationMatrices;

		std::shared_ptr<VertexBuffer> m_VertexBuffer = nullptr;
		std::shared_ptr<IndexBuffer> m_IndexBuffer = nullptr;
		std::unique_ptr<Shader> m_Shader = nullptr;
		std::unique_ptr<VertexArray> m_VertexArray = nullptr;
		
		std::unique_ptr<SSBO> m_HandleBuffer = nullptr;
		std::unique_ptr<SSBO> m_TransformBuffer = nullptr;
		std::unique_ptr<Texture> m_WhiteTexture = nullptr;

		glm::vec2 m_QuadPositions[4];
		uint32_t m_QuadIndexCount = 0;
	};

}

