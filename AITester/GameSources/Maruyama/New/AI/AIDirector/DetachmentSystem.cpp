#include "DetachmentSystem.h"

DetachmentSystem::DetachmentSystem()
{
	
}

//�헪�Ƀ����o�[������U��
void DetachmentSystem::AssignMembersToStrategies()
{
	//�����ɏ]���āA�헪�Ƀ����o�[������U��B

}

void DetachmentSystem::AsigneMember(Member* const member) { mMembers.push_back(member); }

void DetachmentSystem::AddStrategy(StrategyBase* const strategy) { mStrategys.push_back(strategy); }