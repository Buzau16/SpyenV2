#include <Core/Core.h>
#include <Window/Window.h>

#include "AssetManager/IAssetManager.h"
#include "Scene/Components.h"
#include <Core/Director.h>

#include "Player.h"
#include "FoodSpawner.h"
#include "Food.h"
#include "TransitionScript.h"
#include <Core/Defines.h>

constexpr uint32_t Width = 1280;
constexpr uint32_t Height = 720;

int main() {
	
	Spyen::Engine engine(Width, Height, "Penis");

	Spyen::IAssetManager::LoadTexture("Box", "assets/textures/Box.png");
	Spyen::IAssetManager::LoadTexture("Tile", "assets/textures/Tile.png");
	Spyen::IAssetManager::LoadSound("shot", "assets/sounds/shot.mp3");

	auto scene = Spyen::Scene::Create();
	scene->GetCamera().SetCameraType(Spyen::CameraType::Orthographic);
	auto foodspawner = FoodSpawner::Create();
	auto player = Player::Create();
	
	//scene->AddNode(SP_CREATE_MOVE(Food));
	scene->AddNode(SP_MOVE(foodspawner));
	scene->AddNode(SP_MOVE(player));

	scene->SetName("main");

	auto start = Spyen::Scene::Create();
	//start->AddNode(SP_CREATE_MOVE(Food));
	start->AddNode(SP_CREATE_MOVE(TransitionScript));

	start->SetName("start");
	

	Spyen::Director::AddScene("main", std::move(scene));
	Spyen::Director::AddScene("start", std::move(start));
	Spyen::Director::SetActiveScene("main");

	engine.Run();
}
