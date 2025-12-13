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
	SetTexture(Spyen::IAssetManager::GetTexture("Food"));
	SetTag("Food");
	AddRigidBody();
//	RGetRigidBody().SetVelocity({10.f,0.f});
}
