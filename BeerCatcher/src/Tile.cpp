#include "Tile.h"
#include <AssetManager/IAssetManager.h>
#include <Core/Director.h>
#include <Math/Math.h>
#include <Input/Input.h>

void Tile::OnInit()
{
	SetTexture(Spyen::IAssetManager::GetTexture("Tile"));
	auto canvas = Spyen::Director::GetWindowDimensions();
	SetPosition(Spyen::Vec2{ canvas.x / 2.f, canvas.y / 2.f });
	SetScale({ 100.f, 100.f });
	SetName("Tile");

	Spyen::Sprite::OnInit();
}
