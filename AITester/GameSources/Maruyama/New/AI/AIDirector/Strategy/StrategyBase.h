#pragma once

#include "stdafx.h"
#include "StrategyBase.h"

class StrategyBase
{
public:
	StrategyBase();

	virtual ~StrategyBase() = default;

private:
	u32 mIndex;	//��p�ԍ��C���f�b�N�X
	
};