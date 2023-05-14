#pragma once

namespace AI
{
	class StrategyBase;
	class StrategyMember;

	class DetachmentSystem
	{
	public:
		using Member = StrategyMember;

	public:
		DetachmentSystem();

		virtual ~DetachmentSystem() = default;

		/// <summary>
		/// 戦略にメンバーを割り振り
		/// </summary>
		void AssignMembersToStrategies();

		/// <summary>
		/// メンバーの追加
		/// </summary>
		/// <param name="member"></param>
		void AsigneMember(Member* const member);

		/// <summary>
		/// 戦略の追加
		/// </summary>
		/// <param name="strategy">戦略</param>
		void AddStrategy(StrategyBase* const strategy);

	private:
		std::vector<Member*> mMembers;			//メンバー一覧

		std::vector<StrategyBase*> mStrategys;	//戦略一覧
	};
}
