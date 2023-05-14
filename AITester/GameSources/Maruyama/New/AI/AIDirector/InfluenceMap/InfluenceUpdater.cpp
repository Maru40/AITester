#include "InfluenceUpdater.h"

#include "Maruyama/Enemy/Component/EyeSearchRange.h"

#include "Maruyama/Enemy/Component/SelfAstarNodeController.h"
#include "Maruyama/Enemy/Component/SelfAstarNodeController_Ex.h"

using namespace basecross;

namespace AI {

	InfluenceUpdater::InfluenceUpdater(const std::shared_ptr<basecross::GameObject>& owner):
		Component(owner)
	{}

	void InfluenceUpdater::OnLateStart()
	{
		auto object = GetGameObject();

		mEye = object->GetComponent<EyeSearchRange>().get();
	}

	InfluenceUpdater::Eye* InfluenceUpdater::GetEye() const { return mEye; }

	std::shared_ptr<InfluenceUpdater::AstarNode> InfluenceUpdater::GetSelfNode() const { return nullptr; }
}