#pragma once

namespace basecross
{
	namespace maru
	{
		class AstarNode;
	}
}

//�ŐV�Ŏ������g�̃m�[�h�Ǘ�
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
