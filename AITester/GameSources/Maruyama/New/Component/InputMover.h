#pragma once

#include "stdafx.h"

class InputerComponent;

namespace basecross
{
	class RotationController;
}

class InputMover : public basecross::Component
{
public:
	InputMover(const std::shared_ptr<basecross::GameObject>& owner);

	~InputMover() = default;

	void OnCreate() override;
	void OnLateStart() override;
	void OnUpdate() override;

	void MoveUpdate(const Vector& input);
	
public:
	void SetSpeed(const f32 speed) { mSpeed = speed; }
	f32 GetSpeed() const { return mSpeed; }

private:
	InputerComponent* mInput = nullptr;
	basecross::Transform* mTransform = nullptr;
	basecross::RotationController* mRotationController = nullptr;

	f32 mSpeed;
};