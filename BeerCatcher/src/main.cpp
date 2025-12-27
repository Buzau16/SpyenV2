#include <Spyen.h>

#include "PlayerScript.h"
#include "FoodScript.h"

#include <iostream>

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

	auto box = scene->CreateEntity("food");
	box.AddComponent<Spyen::BoxColliderComponent>();
	box.AddComponent<Spyen::SpriteRenderComponent>().Texture = Spyen::IAssetManager::GetTexture("Food");
	box.GetComponent<Spyen::TransformComponent>().Position = { 400, 400 };
	SP_ADD_SCRIPT(box, FoodScript);

	auto sky = scene->CreateEntity();
	auto& ambient = sky.AddComponent<Spyen::SkyComponent>();
	ambient.Color = { 0.1, 0.06, 0.3 };
	ambient.LightIntensity = 1.f;

	// test lights
	{
		auto light = scene->CreateEntity();
		light.GetComponent<Spyen::TransformComponent>().Position = { 0, 720 };
		auto& lc = light.AddComponent<Spyen::LightComponent>();
		lc.Color = { 0.99, 0.77, 0.49 };
		lc.Intensity = 1.f;
		lc.Radius = 800.f;
	}
	{
		auto light = scene->CreateEntity();
		light.GetComponent<Spyen::TransformComponent>().Position = { 800, 200 };
		auto& lc = light.AddComponent<Spyen::LightComponent>();
		lc.Color = { 0.47, 0.2, 0.94 };
		lc.Intensity = 1.f;
		lc.Radius = 400.f;
	}
	{
		auto light = scene->CreateEntity();
		light.GetComponent<Spyen::TransformComponent>().Position = { 600, 200 };
		auto& lc = light.AddComponent<Spyen::LightComponent>();
		//lc.Color = { 0.1f, 1.f, 0.5f };
		lc.Intensity = 1.f;
		lc.Radius = 200.f;

	}
	Spyen::Director::AddScene("main", std::move(scene));
	
	Spyen::Director::SetActiveScene("main");

	engine.Run();
}
