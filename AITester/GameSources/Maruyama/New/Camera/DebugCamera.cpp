#include "DebugCamera.h"

#include "Patch/PlayerInputer.h"
#include "Maruyama/New/Component/InputerComponent.h"

using namespace basecross;

DebugCamera::DebugCamera(const std::shared_ptr<Stage>& stage):
	GameObject(stage),
	mSpeed(35.0f)
{

}

void DebugCamera::OnCreate()
{
	AddComponent<InputerComponent>();

	auto stage = GetStage();
	mAtObject = stage->AddGameObject<GameObject>().get();
}

void DebugCamera::OnUpdate()
{
	auto delta = App::GetApp()->GetElapsedTime();
	auto camera = GetStage()->GetView()->GetTargetCamera();

	//EyePosition‚ð§Œä
	auto position = camera->GetEye();
	position += PlayerInputer::GetDebugCameraMoveVector() * mSpeed * delta;
	position += PlayerInputer::GetDebugUpDownVector() * mSpeed * delta;

	//AtPositon‚ð§Œä
	auto atPosition = position;
	atPosition.y = 0.0f;
	atPosition.z += 0.01f;
	mAtObject->GetComponent<Transform>()->SetPosition(atPosition);

	camera->SetEye(position);
	camera->SetAt(mAtObject->GetComponent<Transform>()->GetPosition());
}