#pragma once
#include <Scene/Node.h>
#include <Renderer/Texture.h>
#include <Core/Defines.h>

namespace Spyen {
	class Sprite : public Node
	{
	public:
		Sprite() = default;
		virtual ~Sprite();

		virtual void OnInit() {};
		virtual void OnUpdate(Timestep dt) {};
		virtual void OnRender(Renderer* renderer) override;

		constexpr Texture* GetTexture() const noexcept;
		void SetTexture(const std::filesystem::path& path);
		void SetTexture(Texture* texture);

		SP_SYNTHESIZE(glm::vec3, Color, Color);

		static std::unique_ptr<Sprite> Create();
	protected:
		Texture* Texture = nullptr;
		glm::vec3 Color{ 0,0,0 };
	private:
		bool IsTextureFromManager = false;
	};

}