
/*!
@file AstarNode.cpp
@brief AstarNodeのクラス実体
担当：丸山裕喜
*/

#include "stdafx.h"
#include "Project.h"

#include "AstarNode.h"

#include "Maruyama/DebugClass/Debug_DrawController.h"

namespace basecross {

	namespace maru {

		AstarNode::AstarNode():
			AstarNode(0)
		{}

		AstarNode::AstarNode(const int index) :
			AstarNode(index, Vec3(0.0f))
		{}

		AstarNode::AstarNode(const int index, const Vec3& position) :
			AstarNode(index, position, nullptr)
		{}

		AstarNode::AstarNode(const int index, const Vec3& position, const std::shared_ptr<AstarNode>& parent):
			NodeBase(index), 
			m_position(position), 
			m_parent(parent),
			m_debugDrawController(nullptr)
		{}

		//--------------------------------------------------------------------------------------
		///	アクセッサ
		//--------------------------------------------------------------------------------------

		void AstarNode::SetParent(const std::shared_ptr<AstarNode>& parent) noexcept {
			m_parent = parent;
		}

		std::shared_ptr<AstarNode> AstarNode::GetParent() const noexcept {
			return m_parent.lock();
		}

		bool AstarNode::HasParent() const noexcept {
			return !m_parent.expired();
		}

		//--------------------------------------------------------------------------------------
		///	デバッグ系
		//--------------------------------------------------------------------------------------

		void AstarNode::SetDebugDrawActive(const bool isActive)
		{
			if (m_debugDrawController) {
				m_debugDrawController->SetDebugDrawActive(isActive);
			}
		}

		void AstarNode::OnDebugDraw() {
			//デバッグコンポーネントが存在するかどうかの確認
			if (m_debugDrawController == nullptr) {
				constexpr float Width = 0.8f;
				constexpr float Depth = 0.8f;
				auto data = Debug_DrawData(maru::Rect(Vec3(0.0f), Width, Depth));
				m_debugDrawController = std::make_shared<Debug_DrawController>(data);
			}

			//カラー設定
			auto dengerValue = GetDengerValue();
			auto color = Col4(1.0f, dengerValue, dengerValue, 1.0f);
			m_debugDrawController->SetColor(color);

			m_debugDrawController->OnDraw(GetPosition());
		}
	}

}