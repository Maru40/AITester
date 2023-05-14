#include "stdafx.h"
#include "AIControllerBase.h"

using namespace basecross;

namespace AI
{

	AIControllerBase::AIControllerBase(const std::shared_ptr<GameObject>& owner):
		Component(owner)
	{}

	AIControllerBase::~AIControllerBase()
	{}

}