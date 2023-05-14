#include "stdafx.h"
#include "AIPlayerController.h"

using namespace basecross;

namespace AI
{
	namespace AIPlayer
	{
		Controller::Controller(const std::shared_ptr<basecross::GameObject>& owner) :
			AIControllerBase(owner)
		{}

		Controller::~Controller() {}

	}
}

