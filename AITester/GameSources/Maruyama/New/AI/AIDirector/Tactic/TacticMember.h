#pragma once

namespace AI
{

	class TacticMember : public basecross::Component
	{
	public:
		TacticMember(const std::shared_ptr<basecross::GameObject>& owner);

		~TacticMember() = default;
	};

}