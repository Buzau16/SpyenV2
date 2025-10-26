#include "Renderer.h"

#include <glad/glad.h>

#include "BufferElement.h"


namespace Spyen {
	constexpr uint32_t MaxQuads		= 10000;
	constexpr uint32_t MaxVertices	= MaxQuads * 4;
	constexpr uint32_t MaxIndices	= MaxQuads * 6;

	Renderer::Renderer(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		SPY_CORE_INFO("Initializing the renderer!");

		m_QuadVertexBuffer = new QuadVertex[MaxVertices];
		m_VertexArray = std::make_unique<VertexArray>();
		m_VertexArray->Bind();

		m_VertexBuffer = std::make_shared<VertexBuffer>(nullptr, MaxVertices * sizeof(QuadVertex));
		m_VertexBuffer->Bind();
		m_VertexBuffer->SetLayout({
			{ ShaderDataType::Float2, "a_Position"},
			{ ShaderDataType::Float3, "a_Color"},
			{ ShaderDataType::Float2, "a_TexCoord"},
			{ ShaderDataType::Int, "a_TexIndex"},
			{ ShaderDataType::Int, "a_TrxIndex"}
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

		m_Shader = std::make_unique<Shader>("QuadShader", vertexSrc, fragmentSrc);
		m_Shader->Bind();

		// Make a ssbo for texture handles
		m_HandleBuffer = std::make_unique<SSBO>(nullptr, sizeof(uint64_t) * MaxQuads);

		// Make a ssbo for all the transformation matrices
		m_TransformBuffer = std::make_unique<SSBO>(nullptr, sizeof(glm::mat4) * MaxQuads);

		// Create a white texture
		TextureSpecification specs = {.Width = 1, .Height = 1, .BitDepth = 4};
		m_WhiteTexture = std::make_unique<Texture>(specs);
		uint32_t whiteTextureData = 0xffffffff;
		m_WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));
		m_TextureHandles.push_back(m_WhiteTexture->GetTextureHandle());

		SPY_CORE_INFO("Renderer loaded!");
		SPY_CORE_INFO("OpenGL Version: {}", (const char*)glGetString(GL_VERSION));
		SPY_CORE_INFO("GPU: {}", (const char*)glGetString(GL_RENDERER));
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
		uint32_t buffer_size = 4 * sizeof(QuadVertex) * (m_QuadIndexCount / 6);
		m_VertexBuffer->SetData(m_QuadVertexBuffer, buffer_size);

		// Set SSBO data
		m_HandleBuffer->Bind(0);
		m_HandleBuffer->SetData(m_TextureHandles.data(), sizeof(uint64_t) * m_TextureHandles.size());
		m_Shader->SetUniformHandles("u_Textures", m_TextureHandles.data(), m_TextureHandles.size());

		m_TransformBuffer->Bind(1);
		m_TransformBuffer->SetData(m_TransformationMatrices.data(), sizeof(glm::mat4) * m_TransformationMatrices.size());

		m_Shader->Bind();
		m_VertexArray->Bind();
		glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_QuadIndexCount), GL_UNSIGNED_INT, nullptr);
	}

	void Renderer::DrawQuad(const glm::vec2& position, const glm::vec3& color)
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
			m_QuadVertexBuffer[VertexOffset + i].TextureCoords = textCoords[i];
			m_QuadVertexBuffer[VertexOffset + i].TextureIndex = 0;
		}

		m_QuadIndexCount += 6;
	}

	void Renderer::DrawQuad(const glm::vec2& position, const std::shared_ptr<Texture>& texture)
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
		uint64_t handle = texture ? texture->GetTextureHandle() : m_WhiteTexture->GetTextureHandle();
		uint32_t texIdx = 0;

		auto it = std::ranges::find(m_TextureHandles, handle);
		if (it != m_TextureHandles.end())
		{
			texIdx = static_cast<uint32_t>(std::distance(m_TextureHandles.begin(), it));
		}
		else
		{
			texIdx = static_cast<uint32_t>(m_TextureHandles.size());
			m_TextureHandles.push_back(handle);
		}

		uint32_t VertexOffset = (m_QuadIndexCount / 6) * 4;
		for (int i = 0; i < 4; i++) {
			m_QuadVertexBuffer[VertexOffset + i].Position = m_QuadPositions[i] + position;
			m_QuadVertexBuffer[VertexOffset + i].Color = glm::vec4(1.0f);
			m_QuadVertexBuffer[VertexOffset + i].TextureCoords = textCoords[i];
			m_QuadVertexBuffer[VertexOffset + i].TextureIndex = texIdx;
		}
		m_QuadIndexCount += 6;
	}

	void Renderer::DrawQuad(const glm::mat4& transform, const glm::vec3& color)
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

			m_QuadVertexBuffer[VertexOffset + i].Position = m_QuadPositions[i];
			m_QuadVertexBuffer[VertexOffset + i].Color = glm::vec4(color.r, color.g, color.b, 1.0f);
			m_QuadVertexBuffer[VertexOffset + i].TextureCoords = textCoords[i];
			m_QuadVertexBuffer[VertexOffset + i].TextureIndex = 0;
			m_QuadVertexBuffer[VertexOffset + i].TransformIndex = static_cast<int>(m_QuadIndexCount) / 6; // Gets the number of quads based on the number of indices
		}

		m_QuadIndexCount += 6;
		m_TransformationMatrices.push_back(transform);
	}

	void Renderer::DrawQuad(const glm::mat4& transform, const std::shared_ptr<Texture>& texture)
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
		uint64_t handle = texture ? texture->GetTextureHandle() : m_WhiteTexture->GetTextureHandle();
		uint32_t texIdx = 0;

		auto it = std::ranges::find(m_TextureHandles, handle);
		if (it != m_TextureHandles.end())
		{
			texIdx = static_cast<uint32_t>(std::distance(m_TextureHandles.begin(), it));
		}
		else
		{
			texIdx = static_cast<uint32_t>(m_TextureHandles.size());
			m_TextureHandles.push_back(handle);
		}

		uint32_t VertexOffset = (m_QuadIndexCount / 6) * 4;
		for (int i = 0; i < 4; i++) {
			m_QuadVertexBuffer[VertexOffset + i].Position = m_QuadPositions[i];
			m_QuadVertexBuffer[VertexOffset + i].Color = glm::vec4(1.0f);
			m_QuadVertexBuffer[VertexOffset + i].TextureCoords = textCoords[i];
			m_QuadVertexBuffer[VertexOffset + i].TextureIndex = texIdx;
			m_QuadVertexBuffer[VertexOffset + i].TransformIndex = static_cast<int>(m_QuadIndexCount) / 6; // Gets the number of quads based on the number of indices
		}
		m_QuadIndexCount += 6;
		m_TransformationMatrices.push_back(transform);
	}
}
