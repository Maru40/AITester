#include "TacticBase.h"

#include "TacticMember.h"

#include "Maruyama/New/Component/Targeted_Ex.h"
#include "Maruyama/Utility/Utility.h"

using namespace basecross;

namespace AI
{
	namespace Tactic {

		TacticInfo::TacticInfo() :
			TacticInfo(nullptr, 0, 0)
		{}

		TacticInfo::TacticInfo(Targeted* const targeted, const u32 index, const u32 numAssigne) :
			targeted(targeted),
			index(index),
			numAssigne(numAssigne)
		{}

		TacticBase::TacticBase(const TacticInfo& info) :
			mInfo(info)
		{}

		void TacticBase::AssignMember(Member* const member) {
			mInfo.members.insert(member);
		}

		void TacticBase::UnAssignMember(Member* const member) {
			mInfo.members.erase(member);
		}

		bool TacticBase::HasMember(Member* const member) {
			return mInfo.members.find(member) != mInfo.members.end();
		}

	}
}