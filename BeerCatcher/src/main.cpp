#include <print>
#include <Core/Core.h>
#include <Scene/Entity.h>
#include <Window/Window.h>

#include "Scene/Components.h"


int main() {
	Spyen::Engine engine({ "Penis", 1280, 720 });

	auto scene = engine.CreateSceneA("Cox");
	auto ent = scene->CreateEntity("test");
	ent.AddComponent<Spyen::Components::Transform>();
	auto& comp = ent.GetComponent<Spyen::Components::Transform>();
	comp.Position = { 640.f, 360.f };
	comp.Scale = 100.f;
	ent.AddComponent<Spyen::Components::Render>();
	ent.GetComponent<Spyen::Components::Render>().Texture = new Spyen::Texture("assets/textures/Box.png");

	engine.Run();
}
