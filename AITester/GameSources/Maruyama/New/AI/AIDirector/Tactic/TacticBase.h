#pragma once

#include "stdafx.h"

class Targeted;

namespace AI
{
	namespace Tactic
	{
		class Member;

		struct TacticInfo
		{
			Targeted* targeted = nullptr;				//��p�̃^�[�Q�b�g
			u32 index = 0;								//��p�ԍ��C���f�b�N�X
			u32 numAssigne = 0;							//�A�T�C�����鐔
			std::unordered_set<Member*> members;	//�A�T�C�����Ă��郁���o�[

			TacticInfo();
			TacticInfo(Targeted* const targeted, const u32 index, const u32 numAssigne);
		};

		class TacticBase
		{
		public:
			using Info = TacticInfo;

		public:
			TacticBase(const TacticInfo& info);
			virtual ~TacticBase() = default;

			void AssignMember(Member* const member);
			void UnAssignMember(Member* const member);

			bool HasMember(Member* const member);

		private:
			Info mInfo;

		};
	}
}