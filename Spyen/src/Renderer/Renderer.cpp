#include "spypch.h"
#include "Renderer.h"

#include <glad/glad.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/type_ptr.inl>

#include "BufferElement.h"
#include <glm/ext/matrix_transform.hpp>
#include <Scene/SceneCamera.h>
#include <Math/Math.h>

#include "RenderCommand.h"


namespace Spyen {
	constexpr uint32_t MaxQuads		= 10000;
	constexpr uint32_t MaxVertices	= MaxQuads * 4;
	constexpr uint32_t MaxIndices	= MaxQuads * 6;

	Renderer::Renderer() :
		m_QuadShader("QuadShader", "Shaders/QuadShader.vert", "Shaders/QuadShader.frag"),
		m_LineShader("LineShader", "Shaders/LineShader.vert", "Shaders/LineShader.frag"),
		m_CompositeShader("CompositeShader", "Shaders/CompositeShader.vert", "Shaders/CompositeShader.frag"),
		//m_LightShader("LightShader", "Shaders/LightShader.vert", "Shaders/LightShader.frag"),
		//m_SkyShader("SkyShader", "Shaders/SkyShader.vert", "Shaders/SkyShader.frag"),
		m_WhiteTexture({1,1,4}),
		m_HandleBuffer(nullptr, sizeof(uint64_t) * MaxQuads),
		m_CameraBuffer(sizeof(glm::mat4), 1),
		m_LightDataBuffer(nullptr, sizeof(LightData) * MaxQuads),
		m_LightCountBuffer(sizeof(uint32_t), 3)
	{
		// Initializing for the quads
		m_QuadVertexBufferBase = new QuadVertex[MaxVertices];
		m_QuadVertexArray.Bind();

		m_QuadVertexBuffer = std::make_shared<VertexBuffer>(nullptr, MaxVertices * sizeof(QuadVertex));
		m_QuadVertexBuffer->Bind();
		m_QuadVertexBuffer->SetLayout({
			{ ShaderDataType::Float2, "a_Position"},
			{ ShaderDataType::Float4, "a_Color"},
			{ ShaderDataType::Float2, "a_TexCoord"},
			{ ShaderDataType::Int, "a_TexIndex"}
			});
		m_QuadVertexArray.AddVertexBuffer(m_QuadVertexBuffer);

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
		m_QuadVertexArray.AddIndexBuffer(m_QuadIndexBuffer);
		delete[] indices;

		// Initializing for the Lines
		m_LineVertexBufferBase = new LineVertex[MaxVertices];
		m_LineVertexArray.Bind();

		m_LineVertexBuffer = std::make_shared<VertexBuffer>(nullptr, MaxVertices * sizeof(LineVertex));
		m_LineVertexBuffer->SetLayout({
			{ShaderDataType::Float2, "a_Position"},
			{ShaderDataType::Float4, "a_Color"}
		});
		m_LineVertexArray.AddVertexBuffer(m_LineVertexBuffer);

		m_LightVertexBufferBase = new LightVertex[MaxVertices];
		m_LightVertexArray.Bind();
		m_LightVertexBuffer = std::make_shared<VertexBuffer>(nullptr, MaxVertices * sizeof(LightVertex));
		m_LightVertexBuffer->SetLayout({
			{ ShaderDataType::Float2, "a_Position"},
			{ ShaderDataType::Float3, "a_Color"},
			{ ShaderDataType::Float, "a_Radius"},
			{ ShaderDataType::Float, "a_Intensity"}
			});
		m_LightVertexArray.AddVertexBuffer(m_LightVertexBuffer);
		m_LightVertexArray.AddIndexBuffer(m_QuadIndexBuffer);

		// Create a white texture
		uint32_t whiteTextureData = 0xffffffff;
		m_WhiteTexture.SetData(&whiteTextureData, sizeof(uint32_t));
		m_TextureHandles.push_back(m_WhiteTexture.GetTextureHandle());


		// compositing
		m_CompositeVertexArray.Bind();
		float fullscreen_quad[] = {
			-1.f, -1.f,
			-1.f,  1.f,
			 1.f,  1.f,
			 1.f, -1.f
		};
		m_CompositeVertexBuffer = std::make_shared<VertexBuffer>(fullscreen_quad, sizeof(fullscreen_quad));
		m_CompositeVertexBuffer->SetLayout({
			{ ShaderDataType::Float2, "a_Position"}
			});
		m_CompositeVertexArray.AddVertexBuffer(m_CompositeVertexBuffer);
		uint32_t fsindices[6] = {
			0, 2, 1,  // First triangle
			0, 3, 2   // Second triangle
		};
		m_CompositeIndexBuffer = std::make_shared<IndexBuffer>(fsindices, 6);
		m_CompositeVertexArray.AddIndexBuffer(m_CompositeIndexBuffer);

		SPY_CORE_INFO("Renderer Loaded!");
		SPY_CORE_INFO("  Vendor: {0}", (const char*)glGetString(GL_VENDOR));
		SPY_CORE_INFO("  Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		SPY_CORE_INFO("  Version: {0}", (const char*)glGetString(GL_VERSION));
	}

	Renderer::~Renderer()
	{
		delete[] m_QuadVertexBufferBase;
		delete[] m_LineVertexBufferBase;
		delete[] m_LightVertexBufferBase;
	}

	void Renderer::BeginBatch()
	{
		m_QuadIndexCount = 0;
		m_QuadVertexBufferPtr = m_QuadVertexBufferBase;

		m_LineVertexCount = 0;
		m_LineVertexBufferPtr = m_LineVertexBufferBase;

		m_LightCount = 0;
		m_LightIndexCount = 0;
		m_LineVertexBufferPtr = m_LineVertexBufferBase;

		m_LightDatas.clear();

		m_TextureHandles.clear();
		m_TextureHandles.push_back(m_WhiteTexture.GetTextureHandle());
	}

	void Renderer::BeginFrame(const SceneCamera& camera, const uint32_t width, const uint32_t height)
	{
		m_CameraBuffer.SetData(glm::value_ptr(camera.GetViewProjection()), sizeof(glm::mat4));
		m_DrawingSpace = { {width / 2, height / 2}, {width, height}, 0.f };

		BeginBatch();
	}

	void Renderer::EndFrame()
	{
		if (m_QuadIndexCount)
		{
			GLsizeiptr buffer_size = reinterpret_cast<uint8_t*>(m_QuadVertexBufferPtr) - reinterpret_cast<uint8_t*>(m_QuadVertexBufferBase);
			m_QuadVertexBuffer->SetData(m_QuadVertexBufferBase, buffer_size);

			m_QuadShader.Bind();

			m_HandleBuffer.Bind(0);
			m_HandleBuffer.SetData(m_TextureHandles.data(), sizeof(uint64_t) * m_TextureHandles.size());
			m_QuadShader.SetUniformHandles("u_Textures", m_TextureHandles.data(), static_cast<uint32_t>(m_TextureHandles.size()));

			RenderCommand::DrawIndexed(&m_QuadVertexArray, m_QuadIndexCount);
			m_QuadShader.Unbind();
		}
		if (m_LineVertexCount)
		{
			size_t buffer_size = reinterpret_cast<uint8_t*>(m_LineVertexBufferPtr) - reinterpret_cast<uint8_t*>(m_LineVertexBufferBase);
			m_LineVertexBuffer->SetData(m_LineVertexBufferBase, buffer_size);

			m_LineShader.Bind();
			RenderCommand::SetLineWidth(m_LineWidth);
			RenderCommand::DrawLines(&m_LineVertexArray, static_cast<uint32_t>(buffer_size));
			m_LineShader.Unbind();
		}
		/*if (m_LightIndexCount) {
			size_t buffer_size = reinterpret_cast<uint8_t*>(m_LightVertexBufferPtr) - reinterpret_cast<uint8_t*>(m_LightVertexBufferBase);
			m_LightVertexBuffer->SetData(m_LightVertexBufferBase, buffer_size);

			m_LightShader.Bind();

			m_LightDataBuffer.Bind(2);
			m_LightDataBuffer.SetData(m_LightDatas.data(), m_LightDatas.size() * sizeof(LightData));
			m_LightCountBuffer.SetData(&m_LightCount, sizeof(uint32_t) * m_LightCount);


			RenderCommand::DrawIndexed(&m_LightVertexArray, m_LightIndexCount);
			m_LightShader.Unbind();
		}*/
		
	}

	void Renderer::DrawQuad(const glm::vec2& position, const glm::vec2& scale, float rotation, const Texture* texture)
	{
		const Spyen::Rectangle quad = Rectangle{Math::ToSpyenVec2(position), Math::ToSpyenVec2(scale), rotation};
		if (!IsQuadInFrustum(quad)) {
			//SPY_CORE_INFO("Culling quad at: {},{}", quad.Position.x, quad.Position.y);
			return;
		}
		if (m_QuadIndexCount >= MaxIndices) {
			EndFrame();
			BeginBatch();
		}

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(position, 1.0f)) *
			glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f)) *
			glm::scale(glm::mat4(1.0f), glm::vec3(scale.x, scale.y, 1.0f));

		DrawQuad(transform, texture);
	}

	void Renderer::DrawQuad(const glm::vec2& position, const glm::vec2& scale, float rotation, const glm::vec4& color)
	{
		const Rectangle quad = Rectangle{ Math::ToSpyenVec2(position), Math::ToSpyenVec2(scale), rotation };
		if (!IsQuadInFrustum(quad)) {
			//SPY_CORE_INFO("Culling quad at: {},{}", quad.Position.x, quad.Position.y);
			return;
		}
		if (m_QuadIndexCount >= MaxIndices) {
			EndFrame();
			BeginBatch();
		}

		glm::mat4 transform =	glm::translate(glm::mat4(1.0f), glm::vec3(position, 1.0f))*
								glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f))*
								glm::scale(glm::mat4(1.0f), glm::vec3(scale.x, scale.y, 1.0f));


		DrawQuad(transform, color);
	}

	void Renderer::DrawQuad(const glm::mat4& transform, const glm::vec4& color)
	{
		glm::vec2 textCoords[4] = {
			{ 0.0f, 0.0f },
			{ 1.0f, 0.0f },
			{ 1.0f, 1.0f },
			{ 0.0f, 1.0f }
		};

		for (int i = 0; i < 4; i++) {
			m_QuadVertexBufferPtr->Position = transform * m_QuadPositions[i];
			m_QuadVertexBufferPtr->Color = color;
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

		uint64_t handle = texture ? texture->GetTextureHandle() : m_WhiteTexture.GetTextureHandle();
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
			m_QuadVertexBufferPtr->Color = {1.0f, 1.0f, 1.0f, 1.f};
			m_QuadVertexBufferPtr->TextureCoords = textCoords[i];
			m_QuadVertexBufferPtr->TextureIndex = texIdx;
			m_QuadVertexBufferPtr++;
		}
		m_QuadIndexCount += 6;
	}

	void Renderer::DrawLine(const glm::vec2& p0, const glm::vec2& p1, const glm::vec4& color)
	{
		m_LineVertexBufferPtr->Position = p0;
		m_LineVertexBufferPtr->Color = color;
		m_LineVertexBufferPtr++;

		m_LineVertexBufferPtr->Position = p1;
		m_LineVertexBufferPtr->Color = color;
		m_LineVertexBufferPtr++;

		m_LineVertexCount += 2;
	}
	void Renderer::DrawLight(const glm::vec2& position, const glm::vec3& color, const float radius, const float intensity)
	{
		// culling needs to be different as i light offscreen can have an affect on the final composite
		if (m_LightIndexCount >= MaxIndices) {
			EndFrame();
			BeginBatch();
		}

		m_LightDatas.push_back({ color, radius, intensity });

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(position, 1.0f));

		for (int i = 0; i < 4; i++) {
			m_LightVertexBufferPtr->Position = transform * m_QuadPositions[i];
			m_LightVertexBufferPtr++;
		}

		m_QuadIndexCount += 6;
		m_LightCount++;
	}

	void Renderer::CompositeFinalImage(const Framebuffer& geometry, const Framebuffer& ambient)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, m_DrawingSpace.Scale.x * 2, m_DrawingSpace.Scale.y * 2);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		m_CompositeShader.Bind();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, geometry.GetColorAttachment());

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, ambient.GetColorAttachment());

		m_CompositeShader.SetUniform1i("g_Geometry", 0);
		m_CompositeShader.SetUniform1i("g_Ambient", 1);

		RenderCommand::DrawIndexed(&m_CompositeVertexArray, 6);
		
		m_CompositeShader.Unbind();
	}

	bool Renderer::IsQuadInFrustum(const Rectangle& rect)
	{
		return Math::IsColliding(rect, m_DrawingSpace);
	}
}
