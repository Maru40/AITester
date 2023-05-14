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
		/// �헪�Ƀ����o�[������U��
		/// </summary>
		void AssignMembersToStrategies();

		/// <summary>
		/// �����o�[�̒ǉ�
		/// </summary>
		/// <param name="member"></param>
		void AsigneMember(Member* const member);

		/// <summary>
		/// �헪�̒ǉ�
		/// </summary>
		/// <param name="strategy">�헪</param>
		void AddStrategy(StrategyBase* const strategy);

	private:
		std::vector<Member*> mMembers;			//�����o�[�ꗗ

		std::vector<StrategyBase*> mStrategys;	//�헪�ꗗ
	};
}
