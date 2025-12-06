#pragma once
#include <filesystem>
#include <memory>
#include <Renderer/Renderer.h>
#include <Renderer/Texture.h>
#include "Node.h"
#include <Time/TimeStep.h>
#include <glm/glm.hpp>
#include <Math/Math.h>


namespace Spyen {
	class Sprite : public Node
	{
	public:
		Sprite() = default;
		virtual ~Sprite();

		virtual void OnInit() override;
		virtual void OnUpdate(Timestep dt) override;
		virtual void OnRender(Renderer* renderer) override;
		virtual void OnEvent(Event& event) override;

		Spyen::Texture* GetTexture() const noexcept;
		void SetTexture(const std::filesystem::path& path);
		void SetTexture(Texture* texture);

		SP_SYNTHESIZE(Vec3, Color, Color);

		static std::unique_ptr<Sprite> Create();
	protected:
		Texture* Texture = nullptr;
		Vec3 Color{ 0,0,0 };
	private:
		bool IsTextureFromManager = false;
	};

}