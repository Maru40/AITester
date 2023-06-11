#pragma once

#include "stdafx.h"

#include "Maruyama/Utility/SingletonComponent/SingletonComponent.h"

namespace basecross {
	namespace maru {
		class AstarNode;
		class AstarEdge;
	}
}

namespace AI
{
	class AIDirector : public basecross::maru::SingletonComponent<AIDirector>
	{
	public:
		using AstarNode = basecross::maru::AstarNode;
		using AstarEdge = basecross::maru::AstarEdge;

	public:
		AIDirector(const std::shared_ptr<basecross::GameObject>& owner);

		~AIDirector();

		void OnCreate() override;
		void OnLateStart() override;

		void OnUpdate() override;
	public:

	private:
		/// <summary>
		/// 地形情報を元にルートを構築
		/// </summary>
		/// <param name="selfPosition">開始位置</param>
		/// <param name="targetPosition">目的位置</param>
		void SearchRoute(const Vector selfPosition, const Vector targetPosition);

		/// <summary>
		/// 地形情報をもとにルートを構築
		/// </summary>
		/// <param name="selfNode">開始ノード</param>
		/// <param name="targetNode">目的ノード</param>
		void SearchRoute(const std::shared_ptr<AstarNode>& startNode, const std::shared_ptr<AstarNode>& targetNode);

	private:

	};
}