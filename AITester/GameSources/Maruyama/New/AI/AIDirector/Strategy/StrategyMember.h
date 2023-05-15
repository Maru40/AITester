#pragma once

namespace AI
{

	class StrategyMember : public basecross::Component
	{
	public:
		StrategyMember(const std::shared_ptr<basecross::GameObject>& owner);

		~StrategyMember() = default;
	};

}