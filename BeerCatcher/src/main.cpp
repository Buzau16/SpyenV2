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

	Spyen::IAssetManager::LoadTexture("Box", "assets/textures/Player.png");
	Spyen::IAssetManager::LoadTexture("Food", "assets/textures/Apple.png");
	Spyen::IAssetManager::LoadSound("shot", "assets/sounds/shot.mp3");

	auto scene = Spyen::Scene::Create();
	scene->GetCamera().SetCameraType(Spyen::CameraType::Orthographic);
	auto foodspawner = FoodSpawner::Create();
	auto player = Player::Create();
	
	scene->AddNode(SP_MOVE(foodspawner));
	scene->AddNode(SP_MOVE(player));

	scene->SetName("main");

	Spyen::Director::AddScene("main", std::move(scene));
	Spyen::Director::SetActiveScene("main");

	engine.Run();
}
