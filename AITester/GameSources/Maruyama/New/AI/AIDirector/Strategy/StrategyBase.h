#pragma once

#include "stdafx.h"
#include "StrategyBase.h"

class Targeted;
class StrategyMember;

class StrategyBase
{
public:

public:
	StrategyBase();

	virtual ~StrategyBase() = default;

	void Assign(StrategyMember* const member);
	void UnAssign(StrategyMember* const member);

private:
	Targeted* mTarget = nullptr;			//戦術のターゲット
	u32 mIndex = 0;							//戦術番号インデックス
	u32 mNumAssigne = 0;					//アサインする数
	std::vector<StrategyMember*> mMembers;	//アサインしているメンバー
};