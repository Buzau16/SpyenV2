#include "Player.h"
#include <AssetManager/IAssetManager.h>
#include <Audio/IAudioEngine.h>
#include <Core/Director.h>
#include <Math/Math.h>
#include <Input/Input.h>

void Player::OnInit()
{
	
	SetTexture(Spyen::IAssetManager::GetTexture("Box"));
	auto canvas = Spyen::Director::GetWindowDimensions();
	SetPosition(Spyen::Vec2{canvas.x / 2.f, canvas.y / 2.f});
	SetScale({ 100.f, 100.f });

	Spyen::Sprite::OnInit();
}

void Player::OnUpdate(Spyen::Timestep dt)
{
	if (Spyen::Input::IsKeyDown(Spyen::Key::W)) {
		Position.y += 100.f * dt;
	}
	if (Spyen::Input::IsKeyDown(Spyen::Key::S)) {
		Position.y -= 100.f * dt;
	}
	if (Spyen::Input::IsKeyDown(Spyen::Key::A)) {
		Position.x -= 100.f * dt;
	}
	if (Spyen::Input::IsKeyDown(Spyen::Key::D)) {
		Position.x += 100.f * dt;
	}
	if (Spyen::Input::IsMouseButtonDown(Spyen::Mouse::ButtonLeft)) {
		Spyen::IAudioEngine::PlaySound("shot");
		auto tile = Spyen::Director::GetActiveScene()->GetNodeGraph().GetNode("Tile");
		auto pos = Spyen::Director::GetActiveScene()->GetNodeGraph().GetNode("Tile")->GetPosition();
		auto size = Spyen::Director::GetActiveScene()->GetNodeGraph().GetNode("Tile")->GetScale();
		auto mx = Spyen::Input::GetMouseX();
		auto my = Spyen::Input::GetMouseY();
		if (mx > pos.x - size.x && mx < pos.x + size.x && my > pos.y - size.y && my < pos.y + size.y) {
			SPY_INFO("Shot!");
		}

	}

}
