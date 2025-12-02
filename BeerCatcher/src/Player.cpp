#include "Player.h"
#include <AssetManager/IAssetManager.h>
#include <Core/Director.h>
#include <Math/Math.h>

void Player::OnInit()
{
	Spyen::Node::OnInit();
	SetTexture(Spyen::IAssetManager::GetTexture("Box"));
	auto canvas = Spyen::Director::GetWindowDimensions();
	SetPosition(Spyen::Vec2{canvas.x / 2.f, canvas.y / 2.f});
	SetScale({ 100.f, 100.f });
}
