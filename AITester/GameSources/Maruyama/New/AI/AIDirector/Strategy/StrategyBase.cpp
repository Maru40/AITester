#include "StrategyBase.h"

#include "StrategyMember.h"

#include "Maruyama/Utility/Utility.h"

using namespace basecross;

StrategyBase::StrategyBase()
{

}

void StrategyBase::Assign(StrategyMember* const member) { mMembers.push_back(member); }

void StrategyBase::UnAssign(StrategyMember* const member) { maru::Utility::RemoveVec(mMembers, member); }