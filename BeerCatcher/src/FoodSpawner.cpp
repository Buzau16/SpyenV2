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
	if (!IsThereFood) {
		SpawnFood();
		IsThereFood = true;
	}
}

void FoodSpawner::OnEvent(Spyen::Event& event)
{
	Spyen::EventDispatcher dispatcher(event);
	dispatcher.Dispatch<Spyen::NodeHitEvent>(SP_BIND_EVENT_FUNC(OnFoodEaten));
}

void FoodSpawner::SpawnFood()
{
	auto food = Food::Create();
	food->SetPosition({ Spyen::Math::Random<uint32_t>(0, 1280), Spyen::Math::Random<uint32_t>(0, 720) });
	Spyen::Director::GetActiveScene()->AddNode(SP_MOVE(food));
}

bool FoodSpawner::OnFoodEaten(Spyen::NodeHitEvent& event)
{
	Node* target = event.GetTarget();

	if (SP_IS_SAME_TYPE(target, Player)) {
		// nu șterge nimic dacă nu e food
		return false;
	}

	Spyen::Director::GetActiveScene()->RemoveNode(target);
	SpawnFood();
	return true;
}
