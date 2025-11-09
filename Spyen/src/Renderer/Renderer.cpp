#include "Renderer.h"

#include <glad/glad.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/type_ptr.inl>

#include "BufferElement.h"


namespace Spyen {
	constexpr uint32_t MaxQuads		= 10000;
	constexpr uint32_t MaxVertices	= MaxQuads * 4;
	constexpr uint32_t MaxIndices	= MaxQuads * 6;

	Renderer::Renderer()
	{
		SPY_CORE_INFO("Initializing the renderer!");

		// Initializing for the quads
		m_QuadVertexBufferBase = new QuadVertex[MaxVertices];
		m_QuadVertexArray = std::make_unique<VertexArray>();
		m_QuadVertexArray->Bind();

		m_QuadVertexBuffer = std::make_shared<VertexBuffer>(nullptr, MaxVertices * sizeof(QuadVertex));
		m_QuadVertexBuffer->Bind();
		m_QuadVertexBuffer->SetLayout({
			{ ShaderDataType::Float2, "a_Position"},
			{ ShaderDataType::Float3, "a_Color"},
			{ ShaderDataType::Float2, "a_TexCoord"},
			{ ShaderDataType::Int, "a_TexIndex"}
			});
		m_QuadVertexArray->AddVertexBuffer(m_QuadVertexBuffer);

		m_QuadPositions[1] = { 0.5f, -0.5f, 1.f, 1.0f };
		m_QuadPositions[0] = { -0.5f, -0.5f, 1.0f, 1.0f };
		m_QuadPositions[2] = { 0.5f, 0.5f, 1.0f, 1.0f };
		m_QuadPositions[3] = { -0.5f, 0.5f, 1.0f, 1.0f };

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
		m_QuadIndexBuffer = std::make_shared<IndexBuffer>(indices, MaxIndices);
		m_QuadVertexArray->AddIndexBuffer(m_QuadIndexBuffer);
		delete[] indices;

		m_QuadShader = std::make_unique<Shader>("QuadShader", "Shaders/QuadShader.vert", "Shaders/QuadShader.frag");

		m_QuadShader->Bind();

		// Initializing for the Lines
		m_LineVertexBufferBase = new LineVertex[MaxVertices];
		m_LineVertexArray = std::make_unique<VertexArray>();
		m_LineVertexArray->Bind();

		m_LineVertexBuffer = std::make_shared<VertexBuffer>(nullptr, MaxVertices * sizeof(LineVertex));
		m_LineVertexBuffer->SetLayout({
			{ShaderDataType::Float2, "a_Position"},
			{ShaderDataType::Float3, "a_Color"}
		});
		m_LineVertexArray->AddVertexBuffer(m_LineVertexBuffer);

		m_LineShader = std::make_unique<Shader>("LineShader", "Shaders/LineShader.vert", "Shaders/LineShader.frag");


		// Make a ssbo for texture handles
		m_HandleBuffer = std::make_unique<SSBO>(nullptr, sizeof(uint64_t) * MaxQuads);

		// Create a white texture
		TextureSpecification specs = {.Width = 1, .Height = 1, .BitDepth = 4};
		m_WhiteTexture = std::make_unique <Texture>(specs);
		uint32_t whiteTextureData = 0xffffffff;
		m_WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));
		m_TextureHandles.push_back(m_WhiteTexture->GetTextureHandle());

		m_Camera = std::make_unique<Camera>(glm::vec2{ 0.0f, 0.0f }, 1.0f, glm::ivec2{ 1280, 720 });

		m_CameraBuffer = std::make_unique<UniformBuffer>(sizeof(glm::mat4), 1);

		SPY_CORE_INFO("Renderer loaded!");
		SPY_CORE_INFO("OpenGL Version: {}", (const char*)glGetString(GL_VERSION));
		SPY_CORE_INFO("GPU: {}", (const char*)glGetString(GL_RENDERER));
	}

	Renderer::~Renderer()
	{
		glDeleteVertexArrays(1, &m_QuadVertexArray->GetRendererID());
		glDeleteBuffers(1, &m_QuadVertexBuffer->GetRendererID());
		glDeleteBuffers(1, &m_QuadIndexBuffer->GetRendererID());

		glDeleteVertexArrays(1, &m_LineVertexArray->GetRendererID());
		glDeleteBuffers(1, &m_LineVertexBuffer->GetRendererID());


		delete[] m_QuadVertexBufferBase;
		delete[] m_LineVertexBufferBase;
	}

	void Renderer::BeginFrame()
	{
		m_QuadIndexCount = 0;
		m_QuadVertexBufferPtr = m_QuadVertexBufferBase;

		m_LineVertexCount = 0;
		m_LineVertexBufferPtr = m_LineVertexBufferBase;
	}

	void Renderer::EndFrame()
	{
		
		// Set SSBO data
		m_HandleBuffer->Bind(0);
		m_HandleBuffer->SetData(m_TextureHandles.data(), sizeof(uint64_t) * m_TextureHandles.size());
		m_QuadShader->SetUniformHandles("u_Textures", m_TextureHandles.data(), m_TextureHandles.size());

		m_CameraBuffer->SetData(glm::value_ptr(m_Camera->GetViewProjMatrix()), sizeof(glm::mat4));

		if (m_QuadIndexCount)
		{
			size_t buffer_size = reinterpret_cast<uint8_t*>(m_QuadVertexBufferPtr) - reinterpret_cast<uint8_t*>(m_QuadVertexBufferBase);
			m_QuadVertexBuffer->SetData(m_QuadVertexBufferBase, buffer_size);

			m_QuadShader->Bind();
			

			m_QuadVertexArray->Bind();
			m_QuadVertexBuffer->Bind();
			m_QuadIndexBuffer->Bind();
			glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_QuadIndexCount), GL_UNSIGNED_INT, nullptr);
		}
		if (m_LineVertexCount)
		{
			size_t buffer_size = reinterpret_cast<uint8_t*>(m_LineVertexBufferPtr) - reinterpret_cast<uint8_t*>(m_LineVertexBufferBase);
			m_LineVertexBuffer->SetData(m_LineVertexBufferBase, buffer_size);

			m_LineShader->Bind();
			m_LineVertexArray->Bind();
			glLineWidth(m_LineWidth);
			glDrawArrays(GL_LINES, 0, m_LineVertexCount);
		}
		
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

		for (int i = 0; i < 4; i++) {
			m_QuadVertexBufferPtr->Position = transform * m_QuadPositions[i];
			m_QuadVertexBufferPtr->Color = glm::vec4(color.r, color.g, color.b, 1.0f);
			m_QuadVertexBufferPtr->TextureCoords = textCoords[i];
			m_QuadVertexBufferPtr->TextureIndex = 0;
			m_QuadVertexBufferPtr++;
		}

		m_QuadIndexCount += 6;
	}

	void Renderer::DrawQuad(const glm::mat4& transform, const Texture* texture)
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
			m_QuadVertexBufferPtr->Position = transform * m_QuadPositions[i];
			m_QuadVertexBufferPtr->Color = {1.0f, 1.0f, 1.0f};
			m_QuadVertexBufferPtr->TextureCoords = textCoords[i];
			m_QuadVertexBufferPtr->TextureIndex = texIdx;
			m_QuadVertexBufferPtr++;
		}
		m_QuadIndexCount += 6;
	}

	void Renderer::	DrawLine(const glm::vec2& p0, const glm::vec2& p1, const glm::vec3& color)
	{
		m_LineVertexBufferPtr->Position = p0;
		m_LineVertexBufferPtr->Color = color;
		m_LineVertexBufferPtr++;

		m_LineVertexBufferPtr->Position = p1;
		m_LineVertexBufferPtr->Color = color;
		m_LineVertexBufferPtr++;

		m_LineVertexCount += 2;
	}
}
