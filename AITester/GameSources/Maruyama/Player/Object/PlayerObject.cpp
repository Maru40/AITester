#include "PlayerObject.h"

#include "Maruyama/Player/Component/Player.h"

using namespace basecross;

PlayerObject::PlayerObject(const std::shared_ptr<basecross::Stage>& stage):
	GameObject(stage)
{}

void PlayerObject::OnCreate()
{
	AddComponent<Player>();
}