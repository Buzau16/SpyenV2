#include "Sprite.h"
#include <Renderer/Renderer.h>


namespace Spyen {
	Sprite::~Sprite()
	{
		if (IsTextureFromManager)
			this->Texture = nullptr;
		else delete this->Texture;
	}

	void Sprite::OnRender(Renderer * renderer)
	{
		if (Sprite::Texture) {
			renderer->DrawQuad(Position, Scale, Rotation, Sprite::Texture);
		}
		else {
			renderer->DrawQuad(Position, Scale, Rotation, Color);
		}
	}

	constexpr Texture* Sprite::GetTexture() const noexcept
	{
		return this->Texture;
	}

	void Sprite::SetTexture(const std::filesystem::path& path) noexcept
	{
		if (this->Texture) {
			delete this->Texture;
		}

		this->Texture = Texture::Create(path);
	}

	void Sprite::SetTexture(Spyen::Texture* texture)
	{
		IsTextureFromManager = true;
		Texture = texture;
	}
	std::unique_ptr<Sprite> Sprite::Create()
	{
		return std::make_unique<Sprite>();
	}
};
