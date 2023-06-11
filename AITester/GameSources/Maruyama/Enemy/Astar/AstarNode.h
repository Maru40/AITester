
/*!
@file AstarNode.h
@brief AstarNodeなど
担当：丸山裕喜
*/

#pragma once
#include "stdafx.h"

#include "Maruyama/StateMachine/NodeBase.h"

#include "Maruyama/New/AI/AIDirector/InfluenceMap/InfluenceData.h"

namespace basecross {

	namespace maru {

		//--------------------------------------------------------------------------------------
		///	前方宣言
		//--------------------------------------------------------------------------------------
		class AstarNode;
		class Debug_DrawController;

		//--------------------------------------------------------------------------------------
		///	Astar用のノード
		//--------------------------------------------------------------------------------------
		class AstarNode : public NodeBase
		{
		public:
			AstarNode();

			AstarNode(const int index);

			AstarNode(const int index, const Vec3& position);

			AstarNode(const int index, const Vec3& position, const std::shared_ptr<AstarNode>& parent);

			virtual ~AstarNode() = default;

			//--------------------------------------------------------------------------------------
			///	アクセッサ
			//--------------------------------------------------------------------------------------

			void SetPosition(const Vec3& position) noexcept { m_position = position; }

			_NODISCARD Vec3 GetPosition() const noexcept { return m_position; }

			void SetParent(const std::shared_ptr<AstarNode>& parent) noexcept;

			std::shared_ptr<AstarNode> GetParent() const noexcept;

			bool HasParent() const noexcept;

			void SetInfluenceData(const AI::InfluenceData& data) { mInfluenceData = data; }

			AI::InfluenceData GetInfluenceData() const { return mInfluenceData; }

			void SetDengerValue(const f32 dengerValue) { mInfluenceData.dengerValue = dengerValue; }

			f32 GetDengerValue() const { return mInfluenceData.dengerValue; }

		private:
			Vec3 m_position;					//位置情報

			std::weak_ptr<AstarNode> m_parent;	//親ノード

			AI::InfluenceData mInfluenceData;	//影響データ

		public:

			//--------------------------------------------------------------------------------------
			///	デバッグ系
			//--------------------------------------------------------------------------------------

			std::shared_ptr<Debug_DrawController> m_debugDrawController; //デバッグ表示用コントローラー

			void SetDebugDrawActive(const bool isActive);

			void OnDebugDraw();
		};

	}
}