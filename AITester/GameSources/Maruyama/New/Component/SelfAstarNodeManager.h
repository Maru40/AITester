#pragma once

namespace basecross
{
	namespace maru
	{
		class AstarNode;
	}
}

//最新版自分自身のノード管理
class SelfAstarNodeManager : public basecross::Component
{
public:
	using AstarNode = basecross::maru::AstarNode;

public:
	SelfAstarNodeManager(const std::shared_ptr<basecross::GameObject>& owner);

	~SelfAstarNodeManager() = default;

	void OnCreate() override;

	void SetCurrentNode(AstarNode* const node);

	AstarNode* GetCurrentNode() const;

private:
	AstarNode* mCurrentNode = nullptr;

};
