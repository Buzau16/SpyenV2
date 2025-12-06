#include "spypch.h"
#include "Sprite.h"
#include <Renderer/Renderer.h>


namespace Spyen {
	Sprite::~Sprite()
	{
		if (IsTextureFromManager)
			this->Texture = nullptr;
		else delete this->Texture;
	}

	void Sprite::OnInit()
	{
		Node::OnInit();
	}

	void Sprite::OnUpdate(Timestep dt)
	{
		Node::OnUpdate(dt);
	}

	void Sprite::OnEvent(Event& event)
	{
		Node::OnEvent(event);
	}

	void Sprite::OnRender(Renderer * renderer)
	{
		if (Sprite::Texture) {
			renderer->DrawQuad(Math::ToGLMVec2(Position), Math::ToGLMVec2(Scale), Rotation, Sprite::Texture);
		}
		else {
			renderer->DrawQuad(Math::ToGLMVec2(Position), Math::ToGLMVec2(Scale), Rotation, Math::ToGLMVec3(Color));
		}

		Node::OnRender(renderer);
	}

	Texture* Sprite::GetTexture() const noexcept
	{
		return this->Texture;
	}

	void Sprite::SetTexture(const std::filesystem::path& path)
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
