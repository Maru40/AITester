#pragma once

#include "stdafx.h"
#include "Project.h"

class I_Inputer
{
public:
	virtual ~I_Inputer() = default;

	virtual basecross::bsm::Vec3 GetInputVec() const = 0;
	
	virtual bool IsAttack() const = 0;
};