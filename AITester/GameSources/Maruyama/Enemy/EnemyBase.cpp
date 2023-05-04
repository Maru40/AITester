#include "stdafx.h"
#include "Project.h"

#include "EnemyBase.h"

namespace Enemy
{

	EnemyBase::EnemyBase(const std::shared_ptr<basecross::GameObject>& owner) :
		Component(owner)
	{}

}
