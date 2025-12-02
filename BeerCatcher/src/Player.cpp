#include "Player.h"
#include <AssetManager/IAssetManager.h>
#include <Core/Director.h>

void Player::OnInit()
{
	Spyen::Node::OnInit();
	SetTexture(Spyen::IAssetManager::GetTexture("Box"));
	auto canvas = Spyen::Director::GetWindowDimensions();
	SetPosition(Spyen::Vec2{ canvas.x / 2.0f, canvas.y / 2.0f });
	SetScale({ 100, 100 });
}
