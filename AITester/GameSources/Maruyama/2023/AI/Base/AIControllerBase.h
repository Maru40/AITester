#pragma once

namespace AI
{
	class AIControllerBase : basecross::Component
	{
	public:
		AIControllerBase(const std::shared_ptr<basecross::GameObject>& owner);

		virtual ~AIControllerBase();
	};
}
