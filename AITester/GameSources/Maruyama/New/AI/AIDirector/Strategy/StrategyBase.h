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
	Targeted* mTarget = nullptr;			//��p�̃^�[�Q�b�g
	u32 mIndex = 0;							//��p�ԍ��C���f�b�N�X
	u32 mNumAssigne = 0;					//�A�T�C�����鐔
	std::vector<StrategyMember*> mMembers;	//�A�T�C�����Ă��郁���o�[
};