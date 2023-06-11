#pragma once

namespace AI
{
	class AIDirector;

	namespace Coordinator
	{
		class Member;

		class CoordinatorBase
		{
		public:
			friend AIDirector;

		public:
			CoordinatorBase(AIDirector* const director);

			virtual ~CoordinatorBase() = default;

			//���N�G�X�g
			virtual void Request(Member* const member) = 0;

			//�����o�[�̒ǉ�
			void AssignMember(Member* const member);

			//�����o�[�̍폜
			void UnssignMember(Member* const member);

			//�����o�[�����݂��邩�ǂ���
			bool HasMember(Member* const member) const;

		private:

			virtual void Awake() {}
			virtual void Start() {}
			virtual bool Update() { return true; }
			virtual void Finalize() {}

		private:
			AIDirector* mDirector = nullptr;

			std::unordered_set<Member*> mMembers;
		};
	}
}