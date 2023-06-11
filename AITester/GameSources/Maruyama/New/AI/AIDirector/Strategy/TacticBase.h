#pragma once

#include "stdafx.h"

class Targeted;

namespace AI
{

	class StrategyMember;

	struct TacticInfo
	{
		Targeted* targeted = nullptr;			//戦術のターゲット
		u32 index = 0;							//戦術番号インデックス
		u32 numAssigne = 0;						//アサインする数
		std::vector<StrategyMember*> members;	//アサインしているメンバー

		TacticInfo();
		TacticInfo(Targeted* const targeted, const u32 index, const u32 numAssigne);
	};

	class TacticBase
	{
	public:
		using Info = TacticInfo;

	public:
		TacticBase();

		virtual ~TacticBase() = default;

		void AssignMember(StrategyMember* const member);
		void UnAssignMember(StrategyMember* const member);

	private:
		Info mInfo;
	};

}