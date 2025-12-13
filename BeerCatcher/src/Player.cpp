#include "Player.h"
#include <AssetManager/IAssetManager.h>
#include <Audio/IAudioEngine.h>
#include <Core/Director.h>
#include <Math/Math.h>
#include <Input/Input.h>
#include <Core/Defines.h>
#include "FoodSpawner.h"
#include <Events/NodeEvents.h>

void Player::OnInit()
{
	
	SetTexture(Spyen::IAssetManager::GetTexture("Box"));
	auto canvas = Spyen::Director::GetWindowDimensions();
	SetPosition(Spyen::Vec2{canvas.x / 2, canvas.y / 2});
	SetScale({ 100.f, 100.f });

	AddRigidBody();

	Spyen::Sprite::OnInit();
}

void Player::OnUpdate(Spyen::Timestep dt)
{
	if (Spyen::Input::IsKeyDown(Spyen::Key::W)) {
		Position.y += 250.f * dt;
	}
	if (Spyen::Input::IsKeyDown(Spyen::Key::S)) {
		Position.y -= 250.f * dt;
	}
	if (Spyen::Input::IsKeyDown(Spyen::Key::A)) {
		Position.x -= 250.f * dt;
	}
	if (Spyen::Input::IsKeyDown(Spyen::Key::D)) {
		Position.x += 250.f * dt;
	}

	if (Spyen::Input::IsKeyDown(Spyen::Key::Space)) {
		SP_AS(Spyen::Director::GetActiveScene()->GetNode("Spawner"), FoodSpawner)->SpawnFood();
	}	

	Node::OnUpdate(dt);

}
