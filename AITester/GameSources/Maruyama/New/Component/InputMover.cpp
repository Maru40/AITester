#include "InputMover.h"
#include "Maruyama/New/Component/InputerComponent.h"

using namespace basecross;

InputMover::InputMover(const std::shared_ptr<GameObject>& owner):
	Component(owner),
	mSpeed(5.0f)
{}

void 
InputMover::OnCreate()
{
	mInput = GetGameObject()->GetComponent<InputerComponent>().get();
	mTransform = GetGameObject()->GetComponent<Transform>().get();
}

void 
InputMover::OnUpdate()
{
	MoveUpdate(mInput->GetMoveInput());
}

void 
InputMover::MoveUpdate(const Vector& input)
{
	auto delta = App::GetApp()->GetElapsedTime();
	auto position = mTransform->GetPosition();

	position += input * mSpeed * delta;
	mTransform->SetPosition(position);
}