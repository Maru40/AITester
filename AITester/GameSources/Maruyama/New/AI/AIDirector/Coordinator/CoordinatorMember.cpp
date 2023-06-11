#include "CoordinatorMember.h"

namespace AI
{
	namespace Coordinator
	{
		using namespace basecross;

		Member::Member(const std::shared_ptr<basecross::GameObject>& owner):
			Component(owner)
		{}

		void Member::SetCurrentCoordinator(CoordinatorBase* coordinator) { mCurrentCoordinator = coordinator; }

		CoordinatorBase* Member::GetCurrentCoordinator() const { return mCurrentCoordinator; }

	}
}