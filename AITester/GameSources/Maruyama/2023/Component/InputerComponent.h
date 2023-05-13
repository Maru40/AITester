#pragma once

#include "../Interface/I_Inputer.h"

class InputerComponent : public basecross::Component, public I_Inputer
{
public:
	InputerComponent(const std::shared_ptr<basecross::GameObject>& owner);

	~InputerComponent() = default;

	void OnCreate() override;

	Vector GetMoveInput() override;
};