#pragma once


class Player : public basecross::Component
{
public:
	Player(const std::shared_ptr<basecross::GameObject>& owner);
};