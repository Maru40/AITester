#pragma once

namespace basecross
{
	class EyeSearchRange;

	namespace maru
	{
		class AstarNode;
	}
}

class SelfAstarNodeManager;

namespace AI
{

	class InfluenceUpdater : public basecross::Component
	{
	public:
		using Eye = basecross::EyeSearchRange;
		using AstarNode = basecross::maru::AstarNode;

	public:
		InfluenceUpdater(const std::shared_ptr<basecross::GameObject>& owner);

		~InfluenceUpdater() = default;

		void OnLateStart() override;

		//���E�̎擾
		Eye* GetEye() const;

		//�������g�̃m�[�h�̎擾
		AstarNode* GetSelfNode() const;

	private:
		Eye* mEye = nullptr;
		SelfAstarNodeManager* mSelfAstarNodeManager = nullptr;
	};

}