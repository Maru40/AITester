/*!
@file NoneHidePlace.h
@brief NoneHidePlaceなど
担当者：丸山 裕喜
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

#include "../Interface/I_Decorator.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	/// 前方宣言
	//--------------------------------------------------------------------------------------

	class TargetManager;

	namespace Enemy {
		class EnemyBase;
	}

	namespace maru {

		namespace Behavior {

			namespace Decorator {

				//--------------------------------------------------------------------------------------
				/// 隠し場所が全て空いていて、探す場所がないなら
				//--------------------------------------------------------------------------------------
				class NoneHidePlace : public DecoratorBase<Enemy::EnemyBase>
				{
				public:

				};

			}
		}
	}
}