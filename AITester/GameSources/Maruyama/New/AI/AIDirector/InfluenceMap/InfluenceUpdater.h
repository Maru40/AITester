#pragma once

namespace basecross
{
	class EyeSearchRange;

	namespace maru
	{
		class AstarNode;
	}
}

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

		//‹ŠE‚Ìæ“¾
		Eye* GetEye() const;

		//©•ª©g‚Ìƒm[ƒh‚Ìæ“¾
		std::shared_ptr<AstarNode> GetSelfNode() const;

	private:
		Eye* mEye = nullptr;
		
	};

}