#include "FoodSpawner.h"
#include <Core/Director.h>
#include "Food.h"
#include "Player.h"

void FoodSpawner::OnInit()
{
	SetName("Spawner");
	//SpawnFood();
	Node::OnInit();
}

void FoodSpawner::OnUpdate(Spyen::Timestep dt)
{

}

void FoodSpawner::OnEvent(Spyen::Event& event)
{
	Spyen::EventDispatcher dispatcher(event);
	dispatcher.Dispatch<Spyen::NodeHitEvent>(SP_BIND_EVENT_FUNC(OnFoodEaten));
}

void FoodSpawner::SpawnFood()
{
	auto food = Food::Create();
	food->SetPosition({ Spyen::Math::Random<float>(0, 1280), Spyen::Math::Random<float>(0, 720) });
	Spyen::Director::GetActiveScene()->AddNode(SP_MOVE(food));
}

bool FoodSpawner::OnFoodEaten(Spyen::NodeHitEvent& event)
{
	//if (typeid(*event.GetNode()) == typeid(Player)) {
		Spyen::Director::GetActiveScene()->RemoveNode(event.GetTarget());
		SpawnFood();
		return true;
	//}
	return false;
}
