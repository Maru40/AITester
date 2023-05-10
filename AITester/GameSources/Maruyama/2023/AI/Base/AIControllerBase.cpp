#include "stdafx.h"
#include "AIControllerBase.h"

namespace AI
{
	using namespace basecross;

	AIControllerBase::AIControllerBase(const std::shared_ptr<GameObject>& owner):
		Component(owner)
	{}

	AIControllerBase::~AIControllerBase()
	{}

}