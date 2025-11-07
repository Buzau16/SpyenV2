#include <print>
#include <Core/Core.h>
#include <Scene/Entity.h>
#include <Window/Window.h>

#include "AssetManager/IAssetManager.h"
#include "Scene/Components.h"


int main() {
	Spyen::Engine engine({ "Penis", 1280, 720 });

	Spyen::IAssetManager::LoadTexture("Box", "assets/textures/Box.png");

	auto scene = engine.CreateSceneA("Cox");
	auto ent = scene->CreateEntity("test");
	auto& c = ent.GetComponent<Spyen::TransformComponent>();
	c.Position = {640.f, 360.f};
	c.Scale = 100.f;
	ent.GetComponent<Spyen::RenderComponent>().Texture = Spyen::IAssetManager::GetTexture("Box");

	engine.Run();
}
