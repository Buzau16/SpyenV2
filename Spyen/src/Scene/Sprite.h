#pragma once
#include <Scene/Node.h>

namespace Spyen {
	class Sprite : public Node
	{
	public:
		Sprite() = default;
		virtual ~Sprite() = default;

		virtual void OnInit() override;
		virtual void OnUpdate(Timestep dt) override;
		virtual void OnRender(Renderer* renderer) override;

		constexpr Texture* GetTexture() const noexcept;
		void SetTexture(const std::filesystem::path& path) noexcept;
		void SetTexture(const Texture* texture);

		constexpr glm::vec3 GetColor() const noexcept;
		void SetColor(const glm::vec3& color) noexcept;

	protected:
		Texture* Texture = nullptr;
		glm::vec3 Color{ 0,0,0 };
	};

}