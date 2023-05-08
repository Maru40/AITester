#pragma once

class Mover : public basecross::Component
{
public:
	Mover(const std::shared_ptr<basecross::GameObject>& owner);

	void OnCreate() override;
	void OnUpdate() override;
};