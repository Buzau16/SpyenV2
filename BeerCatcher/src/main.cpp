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
	ent.SetPosition({ Width / 2, Height / 2 });
	ent.SetTexture(Spyen::IAssetManager::GetTexture("Box"));

	auto ente = scene->CreateEntity("collider");
	ente.SetPosition({ Width / 1.5f, Height / 2 });
	ente.SetTexture(Spyen::IAssetManager::GetTexture("Box"));

	engine.Run();
}
