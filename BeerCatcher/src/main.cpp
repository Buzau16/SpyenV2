#include <Spyen.h>

constexpr uint32_t Width = 1280;
constexpr uint32_t Height = 720;

int main() {
	
	Spyen::Engine engine(Width, Height, "Penis");

	Spyen::IAssetManager::LoadTexture("Box", "assets/textures/Player.png");
	Spyen::IAssetManager::LoadTexture("Food", "assets/textures/Apple.png");
	Spyen::IAssetManager::LoadSound("shot", "assets/sounds/shot.mp3");

	
	Spyen::Director::SetActiveScene("main");

	engine.Run();
}
