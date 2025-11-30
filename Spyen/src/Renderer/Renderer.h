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

	struct LineVertex
	{
		glm::vec2 Position;
		glm::vec3 Color;
	};

	class Renderer
	{
	public:
		Renderer();
		~Renderer();

		void BeginBatch();

		void BeginFrame(const Camera* camera);
		void EndFrame();


		// Draw Functions
		void DrawQuad(const glm::vec2& position, const glm::vec2& scale, float rotation, const Texture* texture);
		void DrawQuad(const glm::vec2& position, const glm::vec2& scale, float rotation, const glm::vec3& color);

		// Under the hood function kind of
		void DrawQuad(const glm::mat4& transform, const glm::vec3& color);
		void DrawQuad(const glm::mat4& transform, const Texture* texture);

		void DrawLine(const glm::vec2& p0, const glm::vec2& p1, const glm::vec3& color);

		void SetLineWidth(const float& width) { m_LineWidth = width; }

	private:
		QuadVertex* m_QuadVertexBufferBase = nullptr;
		QuadVertex* m_QuadVertexBufferPtr = nullptr;
		LineVertex* m_LineVertexBufferBase = nullptr;
		LineVertex* m_LineVertexBufferPtr = nullptr;
		std::vector<uint64_t> m_TextureHandles;
		std::shared_ptr<VertexBuffer> m_QuadVertexBuffer = nullptr;
		std::shared_ptr<IndexBuffer> m_QuadIndexBuffer = nullptr;
		std::shared_ptr<VertexBuffer> m_LineVertexBuffer = nullptr;

		std::unique_ptr<Shader> m_QuadShader = nullptr;
		std::unique_ptr<Shader> m_LineShader = nullptr;
		std::unique_ptr<VertexArray> m_QuadVertexArray = nullptr;
		std::unique_ptr<VertexArray> m_LineVertexArray = nullptr;
		std::unique_ptr<SSBO> m_HandleBuffer = nullptr;
		std::unique_ptr<UniformBuffer> m_CameraBuffer = nullptr;
		std::unique_ptr<Texture> m_WhiteTexture = nullptr;
		glm::vec4 m_QuadPositions[4];
		uint32_t m_QuadIndexCount = 0;
		uint32_t m_LineVertexCount = 0;
		float m_LineWidth = 1.0f;

	};

}

