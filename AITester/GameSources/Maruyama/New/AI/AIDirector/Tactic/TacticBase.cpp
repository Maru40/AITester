#include "TacticBase.h"

#include "TacticMember.h"

#include "Maruyama/New/Component/Targeted_Ex.h"
#include "Maruyama/Utility/Utility.h"

using namespace basecross;

namespace AI
{

	TacticInfo::TacticInfo() :
		TacticInfo(nullptr, 0, 0)
	{}

	TacticInfo::TacticInfo(Targeted* const targeted, const u32 index, const u32 numAssigne) :
		targeted(targeted),
		index(index),
		numAssigne(numAssigne)
	{}

	TacticBase::TacticBase()
	{
		
	}

	void TacticBase::AssignMember(TacticMember* const member) { mInfo.members.push_back(member); }

	void TacticBase::UnAssignMember(TacticMember* const member) { maru::Utility::RemoveVec(mInfo.members, member); }

}