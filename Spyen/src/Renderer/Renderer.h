#pragma once

#include "SSBO.h"
#include "UniformBuffer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"
#include "Renderer/Framebuffer.h"
#include <Scene/SceneCamera.h>
#include <Scene/Components.h>
#include <span>
#include <Math/Vector/Vec.h>

namespace Spyen {
	// Credit to: https://www.youtube.com/@TheCherno for the rendering architecture
	struct QuadVertex {
		glm::vec2 Position;
		glm::vec4 Color;
		glm::vec2 TextureCoords;
		int TextureIndex;
	};

	struct LineVertex
	{
		glm::vec2 Position;
		glm::vec3 Color;
	};

	struct LightVertex {
		glm::vec2 Position;
		int Index;
	};

	struct LightData {
		glm::vec3 Color;
		float Radius;
		glm::vec2 Position;
		float Intensity;
		float _padding;
	};

	// Todo: Maybe split up the rendering to include some instancing where necessary
	enum class FramebufferTarget {
		NONE = 0, GEOMETRY, LIGHT, AMBIENT
	};

	class Renderer
	{
	public:
		Renderer();
		~Renderer();

		void BeginBatch();

		void BeginFrame(const FramebufferTarget& fb, const SceneCamera& camera, const uint32_t width, const uint32_t height);
		void EndFrame();

		// Draw Functions
		void DrawQuad(const glm::vec2& position, const glm::vec2& scale, float rotation, const Texture* texture);
		void DrawQuad(const glm::vec2& position, const glm::vec2& scale, float rotation, const glm::vec4& color);

		// Under the hood function kind of
		void DrawQuad(const glm::mat4& transform, const glm::vec4& color);
		void DrawQuad(const glm::mat4& transform, const Texture* texture);

		void DrawLine(const glm::vec2& p0, const glm::vec2& p1, const glm::vec4& color);

		void DrawLight(const glm::vec2& position, const glm::vec3& color, const float radius, const float intensity);

		void SetLineWidth(const float& width) { m_LineWidth = width; }

		void CompositeFinalImage();

		void UploadOccluderData(std::span<Vec2> vertices);

	private:
		bool IsQuadInFrustum(const Rectangle& rect);
		Framebuffer* GetCurrentFrameBuffer(const FramebufferTarget& target);

		QuadVertex* m_QuadVertexBufferBase = nullptr;
		QuadVertex* m_QuadVertexBufferPtr = nullptr;
		LineVertex* m_LineVertexBufferBase = nullptr;
		LineVertex* m_LineVertexBufferPtr = nullptr;
		LightVertex* m_LightVertexBufferBase = nullptr;
		LightVertex* m_LightVertexBufferPtr = nullptr;

		std::vector<uint64_t> m_TextureHandles;
		std::vector<LightData> m_LightDatas;
		Rectangle m_DrawingSpace;
		std::shared_ptr<VertexBuffer> m_QuadVertexBuffer = nullptr;
		std::shared_ptr<VertexBuffer> m_LightVertexBuffer = nullptr;
		std::shared_ptr<IndexBuffer> m_QuadIndexBuffer = nullptr;
		std::shared_ptr<VertexBuffer> m_LineVertexBuffer = nullptr;
		std::shared_ptr<VertexBuffer> m_CompositeVertexBuffer = nullptr;
		std::shared_ptr<IndexBuffer> m_CompositeIndexBuffer = nullptr;

		std::unique_ptr<Framebuffer> m_LightFramebuffer = nullptr;
		std::unique_ptr<Framebuffer> m_GeometryFramebuffer = nullptr;
		bool IsFramebufferInit = false;
		Framebuffer* m_CurrentFrameBuffer = nullptr;

		Shader m_QuadShader;
		Shader m_LineShader;
		Shader m_LightShader;
		Shader m_CompositeShader;
		VertexArray m_QuadVertexArray;
		VertexArray m_LineVertexArray;
		VertexArray m_LightVertexArray;
		VertexArray m_CompositeVertexArray;
		SSBO m_HandleBuffer;
		SSBO m_LightDataBuffer;
		SSBO m_OccluderDataBuffer;
		bool IsOccluderDataInit = false;
		UniformBuffer m_CameraBuffer;
		UniformBuffer m_OccluderCountBuffer;
		Texture m_WhiteTexture;
		glm::vec4 m_QuadPositions[4];
		uint32_t m_QuadIndexCount = 0;
		uint32_t m_LineVertexCount = 0;
		uint32_t m_LightIndexCount = 0;
		float m_LineWidth = 1.0f;
		uint32_t m_LightCount = 0;
	};

}

