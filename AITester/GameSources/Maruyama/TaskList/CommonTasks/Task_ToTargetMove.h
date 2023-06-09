/*!
@file Task_ToTargetMove.h
@brief Task_ToTargetMove
担当者：丸山 裕喜
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

#include "Maruyama/TaskList/TaskList.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	///	前方宣言
	//--------------------------------------------------------------------------------------
	class VelocityManager;
	class OnlinePlayerSynchronizer;
	class AIVirtualController;
	class WallAvoid;

	namespace Task {
		//--------------------------------------------------------------------------------------
		///	移動タイプ
		//--------------------------------------------------------------------------------------
		enum class ToTargetMove_MoveType {
			Lerp,					//補間
			OnlineLerp,				//オンラインように仮で作ったLerp処理
			Transform,				//通常トランスフォーム
			SeekVelocity,			//追従速度
			ArriveVelocity,			//到着速度
		};

		//--------------------------------------------------------------------------------------
		///	時間計測タイプ
		//--------------------------------------------------------------------------------------
		enum class ToTargetMove_DeltaType {
			Normal, //通常
			Real,   //リアルタイム
		};

		//--------------------------------------------------------------------------------------
		///	指定箇所まで移動するタスクのパラメータ
		//--------------------------------------------------------------------------------------
		struct ToTargetMove_Parametor
		{
			using MoveType = ToTargetMove_MoveType;	
			using DeltaType = ToTargetMove_DeltaType;

			Vec3 startPosition;			//開始位置
			Vec3 endPosition;			//終了位置
			float speed;				//移動速度
			float targetNearRange;		//目的地にたどり着いたと判断する距離
			MoveType moveType;			//移動タイプ
			DeltaType deltaType;		//時間計測タイプ
			bool isAIVirtualController;	//バーチャルコントローラーを使用する。
			bool isOnlineSynchro;		//オンラインシンクロをするかどうか

			/// <summary>
			/// コンストラクタ
			/// </summary>
			ToTargetMove_Parametor();

			/// <summary>
			/// コンストラクタ
			/// </summary>
			/// <param name="speed">移動速度</param>
			/// <param name="taretNearRange">目的地にたどり着いたと判断する距離</param>
			/// <param name="moveType">移動タイプ</param>
			/// <param name="deltaType">時間計測タイプ</param>
			ToTargetMove_Parametor(const float& speed, const float& taretNearRange,
				const MoveType moveType = MoveType::Lerp, const DeltaType& deltaType = DeltaType::Normal);

			/// <summary>
			/// コンストラクタ
			/// </summary>
			/// <param name="startPosition">開始位置</param>
			/// <param name="endPosition">終了位置</param>
			/// <param name="speed">移動速度</param>
			/// <param name="taretNearRange">目的地にたどり着いたと判断する距離</param>
			/// <param name="moveType">移動タイプ</param>
			/// <param name="deltaType">時間計測タイプ</param>
			ToTargetMove_Parametor(const Vec3& startPosition, const Vec3& endPosition,
				const float& speed, const float& taretNearRange,
				const MoveType moveType = MoveType::Lerp, const DeltaType& deltaType = DeltaType::Normal);
		};

		//--------------------------------------------------------------------------------------
		///	指定箇所まで移動するタスク
		//--------------------------------------------------------------------------------------
		class ToTargetMove : public TaskNodeBase<GameObject>
		{
		public:
			using Parametor = ToTargetMove_Parametor;
			using MoveType = ToTargetMove_MoveType;
			using DeltaType = ToTargetMove_DeltaType;

		private:
			ex_weak_ptr<Parametor> m_paramPtr;	//パラメータ

			std::weak_ptr<VelocityManager> m_velocityManager;
			std::weak_ptr<AIVirtualController> m_virtualController;			//バーチャルコントローラー
			std::weak_ptr<OnlinePlayerSynchronizer> m_onlineSynchronizer;	//オンラインシンクロ
			std::weak_ptr<WallAvoid> m_wallAvoid;

		public:
			/// <summary>
			/// コンストラクタ
			/// </summary>
			/// <param name="owner">このクラスを所有するゲームオブジェクト</param>
			/// <param name="paramPtr">パラメータ</param>
			ToTargetMove(const std::shared_ptr<GameObject>& owner, const std::shared_ptr<Parametor>& paramPtr);

			void OnStart() override;
			bool OnUpdate() override;
			void OnExit() override;

		private:
			/// <summary>
			/// このクラスを所有するゲームオブジェクトの位置設定
			/// </summary>
			/// <param name="position">位置</param>
			void SetOwnerPosition(const Vec3& position);

			/// <summary>
			/// このクラスを所有するゲームオブジェクトの位置の取得
			/// </summary>
			/// <returns>このクラスを所有するゲームオブジェクトの位置</returns>
			Vec3 GetOwnerPosition();

			/// <summary>
			/// 移動更新
			/// </summary>
			void MoveUpdate();

			/// <summary>
			/// 補完移動処理
			/// </summary>
			void LerpMove();

			/// <summary>
			/// 通常移動処理
			/// </summary>
			void TransformMove();

			/// <summary>
			/// 速度移動
			/// </summary>
			void VelocityMove();

			/// <summary>
			/// 仮想コントローラーを使った移動をする。
			/// </summary>
			void AIVirtualControllerMove(const Vec3& force);

			/// <summary>
			/// タイプの合わせた加速力を返す。
			/// </summary>
			/// <returns>タイプに合わせた加速力</returns>
			Vec3 CalculateVelocityForce();

			/// <summary>
			/// 経過時間の取得
			/// </summary>
			/// <returns>経過時間</returns>
			float GetElapsedTime();

			/// <summary>
			/// 終了判断
			/// </summary>
			/// <returns>目的地まで移動が完了したらtrue</returns>
			bool IsEnd();

		public:
			//--------------------------------------------------------------------------------------
			///	アクセッサ
			//--------------------------------------------------------------------------------------

			/// <summary>
			/// パラメータの設定
			/// </summary>
			/// <param name="parametor">パラメータ</param>
			void SetParametor(const std::shared_ptr<ToTargetMove::Parametor>& parametor) noexcept;

			/// <summary>
			/// パラメータの取得
			/// </summary>
			/// <returns>パラメータ</returns>
			std::shared_ptr<ToTargetMove::Parametor> GetParametor() const;

			/// <summary>
			///	バーチャルコントローラーを使うかどうか
			/// </summary>
			/// <param name="isAIVirtualController"></param>
			void SetIsAIVirtualController(const bool isAIVirtualController) { m_paramPtr->isAIVirtualController = isAIVirtualController; }

		};

	}
}

//endbasecross