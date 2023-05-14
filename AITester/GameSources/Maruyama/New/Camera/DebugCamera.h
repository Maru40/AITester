#pragma once

class DebugCamera : public basecross::GameObject
{
public:
	DebugCamera(const std::shared_ptr<basecross::Stage>& stage);

	~DebugCamera() = default;

	void OnCreate() override;
	void OnUpdate() override;

private:
	f32 mSpeed;

	basecross::GameObject* mAtObject = nullptr;
};