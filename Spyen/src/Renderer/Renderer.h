#pragma once

#include "Camera.h"
#include "SSBO.h"
#include "UniformBuffer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"

namespace Spyen {

	struct QuadVertex {
		glm::vec2 Position;
		glm::vec3 Color;
		glm::vec2 TextureCoords;
		int TextureIndex;
	};

	class Renderer
	{
	public:
		Renderer() = default;
		Renderer(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Renderer();

		void BeginFrame();
		void EndFrame();

		void DrawQuad(const glm::mat4& transform, const glm::vec3& color);
		void DrawQuad(const glm::mat4& transform, const Texture* texture);

	private:
		QuadVertex* m_QuadVertexBufferBase = nullptr;
		QuadVertex* m_QuadVertexBufferPtr = nullptr;
		std::vector<uint64_t> m_TextureHandles;
		std::shared_ptr<VertexBuffer> m_VertexBuffer = nullptr;
		std::shared_ptr<IndexBuffer> m_IndexBuffer = nullptr;

		std::unique_ptr<Shader> m_Shader = nullptr;
		std::unique_ptr<VertexArray> m_VertexArray = nullptr;
		std::unique_ptr<Camera> m_Camera = nullptr;
		std::unique_ptr<SSBO> m_HandleBuffer = nullptr;
		std::unique_ptr<UniformBuffer> m_CameraBuffer = nullptr;
		std::unique_ptr<Texture> m_WhiteTexture = nullptr;
		glm::vec4 m_QuadPositions[4];
		uint32_t m_QuadIndexCount = 0;

	};

}

