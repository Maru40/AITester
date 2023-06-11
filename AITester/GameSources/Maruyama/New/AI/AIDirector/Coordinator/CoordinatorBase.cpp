#include "CoordinatorBase.h"

#include "CoordinatorMember.h"

namespace AI
{
	namespace Coordinator
	{
		CoordinatorBase::CoordinatorBase(AIDirector* const director) :
			mDirector(director)
		{}

		void CoordinatorBase::AssignMember(Member* const member)
		{
			//�����o�[�����݂���Ȃ�
			if (HasMember(member)) {
				return;
			}

			//���łɃR�[�f�B�l�[�^�ɏ������Ă���Ȃ�
			if (auto coordinator = member->GetCurrentCoordinator()) {
				coordinator->UnssignMember(member);
			}

			mMembers.insert(member);
			member->SetCurrentCoordinator(this);
		}

		void CoordinatorBase::UnssignMember(Member* const member)
		{
			//�����o�[�����݂��Ȃ��Ȃ�
			if (!HasMember(member)) {
				return;
			}

			member->SetCurrentCoordinator(nullptr);
			mMembers.erase(member);
		}

		bool CoordinatorBase::HasMember(Member* const member) const { return mMembers.find(member) != mMembers.end(); }

	}
}