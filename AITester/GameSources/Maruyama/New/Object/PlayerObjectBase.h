#pragma once

#include "Watanabe/Shader/BoneModelDraw.h"
#include "Watanabe/UI/DirectionWithHasBallUI.h"

class PlayerObjectBase : public basecross::GameObject
{
public:
	using DrawComp = basecross::BoneModelDraw;

public:
	PlayerObjectBase(const std::shared_ptr<basecross::Stage>& stage);

	virtual ~PlayerObjectBase() = default;

	void OnCreate() override;
	void OnUpdate() override;

protected:
	virtual void CreateModel();

	virtual void CreateCollision();
};