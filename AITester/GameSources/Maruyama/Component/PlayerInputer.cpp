#include "PlayerInputer.h"
#include "MathHelper.h"

using namespace basecross;
using namespace basecross::bsm;

using namespace itbs::Input;

PlayerInputer::PlayerInputer(const std::shared_ptr<GameObject>& owner):
	Component(owner)
{}

Vec3 
PlayerInputer::GetInputVec() const
{
	static const auto& inputDevice = App::GetApp()->GetMyInputDevice();
	static const auto& keyBoard = inputDevice->GetKeyBoard();
	static const auto& xinput = inputDevice->GetXInputGamePad();

	Vec3 direction;

	if (keyBoard.IsInputPush(KeyCode::D))
	{
		direction.x += 1;
	}

	if (keyBoard.IsInputPush(KeyCode::A))
	{
		direction.x -= 1;
	}

	if (keyBoard.IsInputPush(KeyCode::W))
	{
		direction.z += 1;
	}

	if (keyBoard.IsInputPush(KeyCode::S))
	{
		direction.z -= 1;
	}


	direction.x += xinput.GetLeftThumb().x;
	direction.z += xinput.GetLeftThumb().y;

	direction.x = itbs::Math::MyMath::Clamp(direction.x, -1.0f, 1.0f);

	direction.z = itbs::Math::MyMath::Clamp(direction.z, -1.0f, 1.0f);

	if (direction.length() > 1.0f)
	{
		direction.normalize();
	}

	return direction;
}

bool 
PlayerInputer::IsAttack() const
{
	return App::GetApp()->GetMyInputDevice()->GetKeyBoard().IsInputPush(KeyCode::Enter) ||
		App::GetApp()->GetMyInputDevice()->GetXInputGamePad().IsInputPush(XInputCode::A);
}