#include "InputerComponent.h"

#include "Patch/PlayerInputer.h"

using namespace basecross;

InputerComponent::InputerComponent(const std::shared_ptr<basecross::GameObject>& owner):
	Component(owner)
{}

void
InputerComponent::OnCreate()
{

}

Vector 
InputerComponent::GetMoveInput()
{
	auto vec2 = PlayerInputer::GetInstance()->GetMoveDirection();

	Vector result = Vector(vec2.x, 0.0f, vec2.y);
	return result;
}