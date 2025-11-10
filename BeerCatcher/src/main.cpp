#include <Core/Core.h>
#include <Scene/Entity.h>
#include <Window/Window.h>

#include "AssetManager/IAssetManager.h"
#include "Scene/Components.h"



constexpr uint32_t Width = 1280;
constexpr uint32_t Height = 720;

int main() {
	
	Spyen::Engine engine({ "Penis", Width, Height });

	Spyen::IAssetManager::LoadTexture("Box", "assets/textures/Box.png");

	auto scene = engine.CreateSceneA("Cox");
	auto ent = scene->CreateEntity("test");
	auto& c = ent.GetComponent<Spyen::TransformComponent>();
	c.Position = {Width / 2, Height / 2};
	c.Scale = { 100, 100 };
	ent.GetComponent<Spyen::RenderComponent>().Texture = Spyen::IAssetManager::GetTexture("Box");

	auto ente = scene->CreateEntity("collider");
	auto& comp = ente.GetComponent<Spyen::TransformComponent>();
	comp.Position = { Width / 4, Height / 2 };
	comp.Scale = { 100, 100 };
	ente.GetComponent<Spyen::RenderComponent>().Texture = Spyen::IAssetManager::GetTexture("Box");

	engine.Run();
}
