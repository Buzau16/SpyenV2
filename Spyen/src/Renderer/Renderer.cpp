#include "Renderer.h"

#include <glad/glad.h>


namespace Spyen {
	constexpr uint32_t MaxQuads		= 10000;
	constexpr uint32_t MaxVertices	= MaxQuads * 4;
	constexpr uint32_t MaxIndices	= MaxQuads * 6;

	Renderer::Renderer(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		SPY_CORE_INFO("Initializing the renderer!");

		m_QuadVertexBuffer = new QuadVertex[MaxVertices];
		m_VertexArray = std::make_shared<VertexArray>();
		m_VertexArray->Bind();

		m_VertexBuffer = std::make_shared<VertexBuffer>(nullptr, MaxVertices * sizeof(QuadVertex));
		m_VertexBuffer->Bind();
		m_VertexBuffer->SetLayout({
			{ ShaderDataType::Float2, "a_Position"},
			{ ShaderDataType::Float3, "a_Color"}
			});
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		m_QuadPositions[0] = { -0.5f, -0.5f };
		m_QuadPositions[1] = { 0.5f, -0.5f };
		m_QuadPositions[2] = { 0.5f, 0.5f  };
		m_QuadPositions[3] = { -0.5f, 0.5f };

		uint32_t* indices = new uint32_t[MaxIndices];
		uint32_t offset = 0;
		for (uint32_t i = 0; i < MaxIndices; i += 6) {
			indices[i + 0] = offset + 0;
			indices[i + 1] = offset + 1;
			indices[i + 2] = offset + 2;
			indices[i + 3] = offset + 2;
			indices[i + 4] = offset + 3;
			indices[i + 5] = offset + 0;
			offset += 4;
		}
		m_IndexBuffer = std::make_shared<IndexBuffer>(indices, MaxIndices);
		m_VertexArray->AddIndexBuffer(m_IndexBuffer);
		delete[] indices;

		m_Shader = std::make_shared<Shader>("QuadShader", vertexSrc, fragmentSrc);
	}

	Renderer::~Renderer()
	{
		glDeleteVertexArrays(1, &m_VertexArray->GetRendererID());
		glDeleteBuffers(1, &m_VertexBuffer->GetRendererID());
		glDeleteBuffers(1, &m_IndexBuffer->GetRendererID());


		delete[] m_QuadVertexBuffer;
	}

	void Renderer::BeginFrame()
	{
		m_QuadIndexCount = 0;

	}

	void Renderer::EndFrame()
	{
		size_t buffer_size = 4 * sizeof(QuadVertex) * (m_QuadIndexCount / 6);
		m_VertexBuffer->SetData(m_QuadVertexBuffer, buffer_size);

		m_Shader->Bind();
		m_VertexArray->Bind();
		glDrawElements(GL_TRIANGLES, m_QuadIndexCount, GL_UNSIGNED_INT, nullptr);
	}

	void Renderer::DrawQuad(glm::vec2& position, glm::vec3& color)
	{
		glm::vec2 textCoords[4] = {
			{ 0.0f, 0.0f },
			{ 1.0f, 0.0f },
			{ 1.0f, 1.0f },
			{ 0.0f, 1.0f }
		};

		if (m_QuadIndexCount >= MaxIndices) {
			EndFrame();
			BeginFrame();
		}

		uint32_t VertexOffset = (m_QuadIndexCount / 6) * 4;
		for (int i = 0; i < 4; i++) {
			m_QuadVertexBuffer[VertexOffset + i].Position = m_QuadPositions[i] + position;
			m_QuadVertexBuffer[VertexOffset + i].Color = glm::vec4(color.r, color.g, color.b, 1.0f);
		}

		m_QuadIndexCount += 6;
	}

}