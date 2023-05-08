#pragma once

class PlayerObject : public basecross::GameObject
{
public:
	PlayerObject(const std::shared_ptr<basecross::Stage>& stage);

	virtual ~PlayerObject() = default;

	void OnCreate() override;

private:

};