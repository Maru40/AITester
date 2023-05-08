#pragma once

#include "stdafx.h"
#include "Project.h"

#include "Maruyama/Interface/I_Inputer.h"

class PlayerInputer : public basecross::Component, public I_Inputer
{
public:
	PlayerInputer(const std::shared_ptr<basecross::GameObject>& owner);

	void OnCreate() override {};
	void OnUpdate() override {};

	basecross::bsm::Vec3 GetInputVec() const override;

	bool IsAttack() const override;
};