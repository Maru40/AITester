#include "TacticMember.h"

namespace AI
{
	namespace Tactic 
	{

		Member::Member(const std::shared_ptr<basecross::GameObject>& owner) :
			Component(owner)
		{}

	}
}