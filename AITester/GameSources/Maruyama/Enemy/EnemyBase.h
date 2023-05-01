#pragma once

#include "stdafx.h"
#include "Project.h"

class EnemyBase : public basecross::Component
{
public:
	//using namespace basecross;

public:
	EnemyBase(const std::shared_ptr<basecross::GameObject>& owner);
	virtual ~EnemyBase() = default;
};