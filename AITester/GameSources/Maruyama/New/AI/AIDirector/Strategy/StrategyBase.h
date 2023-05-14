#pragma once

#include "stdafx.h"
#include "StrategyBase.h"

class Targeted;
class StrategyMember;

struct StrategyParameter
{
	Targeted* targeted = nullptr;			//��p�̃^�[�Q�b�g
	u32 index = 0;							//��p�ԍ��C���f�b�N�X
	u32 numAssigne = 0;						//�A�T�C�����鐔
	std::vector<StrategyMember*> members;	//�A�T�C�����Ă��郁���o�[

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