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
		/// �n�`�������Ƀ��[�g���\�z
		/// </summary>
		/// <param name="selfPosition">�J�n�ʒu</param>
		/// <param name="targetPosition">�ړI�ʒu</param>
		void SearchRoute(const Vector selfPosition, const Vector targetPosition);

		/// <summary>
		/// �n�`�������ƂɃ��[�g���\�z
		/// </summary>
		/// <param name="selfNode">�J�n�m�[�h</param>
		/// <param name="targetNode">�ړI�m�[�h</param>
		void SearchRoute(const std::shared_ptr<AstarNode>& startNode, const std::shared_ptr<AstarNode>& targetNode);

	private:

	};
}