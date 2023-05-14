#include "DetachmentSystem.h"

DetachmentSystem::DetachmentSystem()
{
	
}

//戦略にメンバーを割り振り
void DetachmentSystem::AssignMembersToStrategies()
{
	//条件に従って、戦略にメンバーを割り振る。

}

void DetachmentSystem::AsigneMember(Member* const member) { mMembers.push_back(member); }

void DetachmentSystem::AddStrategy(StrategyBase* const strategy) { mStrategys.push_back(strategy); }