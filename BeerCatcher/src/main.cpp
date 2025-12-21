#include <Spyen.h>

#include "PlayerScript.h"

constexpr uint32_t Width = 1280;
constexpr uint32_t Height = 720;

int main() {
	
	Spyen::Engine engine(Width, Height, "Penis");

	Spyen::IAssetManager::LoadTexture("Box", "assets/textures/Player.png");
	Spyen::IAssetManager::LoadTexture("Food", "assets/textures/Apple.png");
	Spyen::IAssetManager::LoadSound("shot", "assets/sounds/shot.mp3");


	auto scene = Spyen::Scene::Create();

	auto entity = scene->CreateEntity("Player");
	entity.AddComponent<Spyen::SpriteRenderComponent>().Texture = Spyen::IAssetManager::GetTexture("Box");
	entity.AddComponent<Spyen::BoxColliderComponent>();
	entity.GetComponent<Spyen::TransformComponent>().Position = { 200, 200 };
	SP_ADD_SCRIPT(entity, PlayerScript);

	auto box = scene->CreateEntity();
	box.AddComponent<Spyen::BoxColliderComponent>();
	box.AddComponent<Spyen::SpriteRenderComponent>().Texture = Spyen::IAssetManager::GetTexture("Food");
	box.GetComponent<Spyen::TransformComponent>().Position = { 200, 200 };

	Spyen::Director::AddScene("main", std::move(scene));
	
	Spyen::Director::SetActiveScene("main");

	engine.Run();
}
