#include <Core/Core.h>
#include <Window/Window.h>

#include "AssetManager/IAssetManager.h"
#include "Scene/Components.h"
#include <Core/Director.h>

#include "Player.h"
#include "Tile.h"
#include <Core/Defines.h>

constexpr uint32_t Width = 1280;
constexpr uint32_t Height = 720;

int main() {
	
	Spyen::Engine engine({ "Penis", Width, Height });

	Spyen::IAssetManager::LoadTexture("Box", "assets/textures/Box.png");
	Spyen::IAssetManager::LoadTexture("Tile", "assets/textures/Tile.png");
	Spyen::IAssetManager::LoadSound("shot", "assets/sounds/shot.mp3");

	auto scene = Spyen::Scene::Create();
	scene->GetCamera().SetCameraType(Spyen::CameraType::Orthographic);
	auto player = Player::Create();
	scene->AddNode(SP_MOVE(player));
	scene->AddNode(SP_CREATE_MOVE(Tile));

	Spyen::Director::AddScene("main", std::move(scene));
	Spyen::Director::SetActiveScene("main");

	engine.Run();
}
