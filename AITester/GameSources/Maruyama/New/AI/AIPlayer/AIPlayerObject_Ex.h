#pragma once

#include "stdafx.h"

#include "Watanabe/Shader/BoneModelDraw.h"
#include "Watanabe/UI/DirectionWithHasBallUI.h"

#include "Maruyama/New/Object/PlayerObjectBase.h"

namespace AI
{
	namespace AIPlayer
	{

		class Object : public PlayerObjectBase
		{
		public:
			using DrawComp = basecross::BoneModelDraw;

		public:
			Object(const std::shared_ptr<basecross::Stage>& stage);

			virtual ~Object() = default;

			void OnCreate() override;
			void OnUpdate() override;

		private:
		};

	}
}