#include "PlayerObject.h"

#include "Maruyama/Player/Component/Player.h"

#include "Maruyama/Component/Mover.h"

#include "Maruyama/Camera/SeekTPS.h"

using namespace basecross;

PlayerObject::PlayerObject(const std::shared_ptr<basecross::Stage>& stage):
	GameObject(stage)
{}

void PlayerObject::OnCreate()
{
	AddComponent<Player>();
	//AddComponent<PlayerInputer>();
	AddComponent<Mover>();

	auto draw = AddComponent<BcPNTStaticDraw>();
	draw->SetMeshResource(L"DEFAULT_CUBE");

	//カメラセッティング
	//auto cameraObject = GetStage()->AddGameObject<GameObject>();
	//cameraObject->AddComponent<SeekTPS>(GetThis<PlayerObject>());
	//auto camera = GetStage()->GetView()->GetTargetCamera();
	//camera->SetCameraObject(cameraObject);
}