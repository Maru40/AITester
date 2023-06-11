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
			Targeted* targeted = nullptr;				//戦術のターゲット
			u32 index = 0;								//戦術番号インデックス
			u32 numAssigne = 0;							//アサインする数
			std::unordered_set<Member*> members;	//アサインしているメンバー

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