#pragma once

#include "stdafx.h"
#include "GameStageBase.h"

class MainStage : basecross::GameStageBase
{
public:
	MainStage(std::uint64_t seed = 0);
	virtual ~MainStage() = default;

	void OnCreate() override;

	void OnUpdate() override;

private:
	void CreateLightView();
};