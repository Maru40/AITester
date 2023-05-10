#pragma once

#include "stdafx.h"

namespace AI
{
	namespace AIPlayer
	{
		class Object : public basecross::GameObject
		{
		public:
			Object(const std::shared_ptr<basecross::Stage>& stage);

			virtual ~Object() = default;

			void OnCreate() override;
		};
	}
}