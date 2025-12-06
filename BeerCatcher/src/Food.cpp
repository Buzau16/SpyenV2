#include "Food.h"
#include <AssetManager/IAssetManager.h>
#include <Audio/IAudioEngine.h>
#include <Core/Director.h>
#include <Math/Math.h>
#include <Input/Input.h>
#include <Core/Defines.h>
#include <Events/NodeEvents.h>
#include "Player.h"

void Food::OnInit()
{
	SetTexture(Spyen::IAssetManager::GetTexture("Tile"));
	SetTag("Food");
	//SetPosition({ 640, 340 });
}

//void Food::OnEvent(Spyen::Event& event)
//{
//	Spyen::EventDispatcher dispatcher(event);
//	dispatcher.Dispatch<Spyen::NodeHitEvent>(SP_BIND_EVENT_FUNC(DestroySelf));
//}
//
//void Food::OnUpdate(Spyen::Timestep dt)
//{
//}
//
//bool Food::DestroySelf(Spyen::NodeHitEvent e) {
//	Spyen::Director::GetActiveScene()->RemoveNode(this);
//	return true;
//}
