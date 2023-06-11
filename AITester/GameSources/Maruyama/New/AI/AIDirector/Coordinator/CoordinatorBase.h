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

			//リクエスト
			virtual void Request(Member* const member) = 0;

			//メンバーの追加
			void AssignMember(Member* const member);

			//メンバーの削除
			void UnssignMember(Member* const member);

			//メンバーが存在するかどうか
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