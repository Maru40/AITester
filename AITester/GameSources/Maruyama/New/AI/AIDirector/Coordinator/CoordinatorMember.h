#pragma once

namespace AI
{
	namespace Coordinator
	{
		class CoordinatorBase;

		class Member : public basecross::Component
		{
		public:
			Member(const std::shared_ptr<basecross::GameObject>& owner);

			~Member() = default;

			void SetCurrentCoordinator(CoordinatorBase* coordinator);

			CoordinatorBase* GetCurrentCoordinator() const;

			template<class T,
				std::enable_if_t<
					std::is_base_of_v<CoordinatorBase, T>,
				std::nullptr_t> = nullptr
			>
			T* GetCastCoordinator() const {
				return dynamic_cast<T*>(mCurrentCoordinator);
			}

		private:
			CoordinatorBase* mCurrentCoordinator = nullptr;	//Œ»İŠ‘®‚µ‚Ä‚¢‚éCoordinator
		};

	}
}