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

	//auto atPosition = camera->GetAt();
	auto position = camera->GetEye();
	position += GetComponent<InputerComponent>()->GetMoveInput() * mSpeed * delta;
	//atPosition += GetComponent<InputerComponent>()->GetMoveInput() * mSpeed * delta;
	auto atPosition = position;
	atPosition.y = 0.0f;
	atPosition.z += 0.01f;
	mAtObject->GetComponent<Transform>()->SetPosition(atPosition);

	position += PlayerInputer::GetDebugUpDownVector() * mSpeed * delta;

	camera->SetEye(position);
	camera->SetAt(mAtObject->GetComponent<Transform>()->GetPosition());
}