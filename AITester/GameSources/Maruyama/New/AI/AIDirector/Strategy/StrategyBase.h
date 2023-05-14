#pragma once

#include "stdafx.h"
#include "StrategyBase.h"

class Targeted;
class StrategyMember;

struct StrategyParameter
{
	Targeted* targeted = nullptr;			//戦術のターゲット
	u32 index = 0;							//戦術番号インデックス
	u32 numAssigne = 0;						//アサインする数
	std::vector<StrategyMember*> members;	//アサインしているメンバー

	StrategyParameter();
	StrategyParameter(Targeted* const targeted, const u32 index, const u32 numAssigne);
};

class StrategyBase
{
public:
	using Parameter = StrategyParameter;

public:
	StrategyBase();

	virtual ~StrategyBase() = default;

	void AssignMember(StrategyMember* const member);
	void UnAssignMember(StrategyMember* const member);

private:
	Parameter mParam;
};