#pragma once

namespace AI
{
	class AIControllerBase : public basecross::Component
	{
	public:
		AIControllerBase(const std::shared_ptr<basecross::GameObject>& owner);

		virtual ~AIControllerBase();
	};
}
