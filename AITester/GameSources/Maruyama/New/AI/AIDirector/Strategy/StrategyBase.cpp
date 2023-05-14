#include "StrategyBase.h"

#include "StrategyMember.h"

#include "Maruyama/New/Component/Targeted_Ex.h"
#include "Maruyama/Utility/Utility.h"

using namespace basecross;

namespace AI
{

	StrategyParameter::StrategyParameter() :
		StrategyParameter(nullptr, 0, 0)
	{}

	StrategyParameter::StrategyParameter(Targeted* const targeted, const u32 index, const u32 numAssigne) :
		targeted(targeted),
		index(index),
		numAssigne(numAssigne)
	{}



	StrategyBase::StrategyBase()
	{

	}

	void StrategyBase::AssignMember(StrategyMember* const member) { mParam.members.push_back(member); }

	void StrategyBase::UnAssignMember(StrategyMember* const member) { maru::Utility::RemoveVec(mParam.members, member); }

}