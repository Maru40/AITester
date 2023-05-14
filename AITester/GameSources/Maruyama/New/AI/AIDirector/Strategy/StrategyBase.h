#pragma once

#include "stdafx.h"
#include "StrategyBase.h"

class StrategyBase
{
public:
	StrategyBase();

	virtual ~StrategyBase() = default;

private:
	u32 mIndex;	//戦術番号インデックス
	
};