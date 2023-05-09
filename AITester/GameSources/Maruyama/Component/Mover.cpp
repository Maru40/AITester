#include "Mover.h"

#include "../../PlayerInputer.h"

Mover::Mover(const std::shared_ptr<basecross::GameObject>& owner):
	Component(owner),
	mSpeed(10.0f)
{}

void
Mover::OnCreate()
{
	//mInputer = GetGameObject()->GetComponent<PlayerInputer>();
}

void
Mover::OnUpdate()
{	
	auto delta = basecross::App::GetApp()->GetElapsedTime();
	auto input = basecross::PlayerInputer::GetInstance()->GetMoveDirection();

	if (input.length()) {
		int i = 0;
	}

	//“ü—Í‚É‡‚í‚¹‚ÄˆÚ“®‚·‚éB
	auto position = transform->GetPosition();
	position += input.GetNormalized() * mSpeed * delta;
	transform->SetPosition(position);
}