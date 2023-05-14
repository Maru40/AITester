#pragma once

#include "stdafx.h"

class InputerComponent;

class InputMover : public basecross::Component
{
public:
	InputMover(const std::shared_ptr<basecross::GameObject>& owner);

	~InputMover() = default;

	void OnCreate() override;
	void OnUpdate() override;

	void MoveUpdate(const Vector& input);
	
public:
	void SetSpeed(const f32 speed) { mSpeed = speed; }
	f32 GetSpeed() const { return mSpeed; }

private:
	InputerComponent* mInput = nullptr;
	basecross::Transform* mTransform = nullptr;

	f32 mSpeed;
};