/*!
@file StateEdgeBase.h
@brief StateEdgeBase
担当者：丸山 裕喜
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

#include "Maruyama/Enemy/Astar/GraphEdgeBase.h"

namespace basecross {

	/// <summary>
	/// エッジの基底クラス
	/// </summary>
	/// <typeparam name="EnumType">使用する列挙体</typeparam>
	/// <typeparam name="TransitionStructMember">遷移条件用の構造体メンバー</typeparam>
	template<class EnumType, class TransitionStructMember>
	class StateEdgeBase : public GraphEdgeBase
	{
	public:
		using IsTransitionFunction = std::function<bool(const TransitionStructMember& member)>;

	private:
		IsTransitionFunction m_isTransitionFunc = nullptr; //遷移する条件

		int m_priority = 0;             //優先度
		bool m_isEndTransition = false; //終了時に遷移するかどうか

	public:
		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="from">手前のインデックス</param>
		/// <param name="to">先のインデックス</param>
		StateEdgeBase(const EnumType from, const EnumType to)
			:StateEdgeBase(from, to, nullptr)
		{}

		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="from">手前のインデックス</param>
		/// <param name="to">先のインデックス</param>
		/// <param name="isTransitionFunc">遷移条件関数</param>
		StateEdgeBase(
			const EnumType from, 
			const EnumType to,
			const IsTransitionFunction& isTransitionFunc
		) :
			StateEdgeBase(from, to, isTransitionFunc, static_cast<int>(to))
		{}

		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="from">手前のインデックス</param>
		/// <param name="to">先のインデックス</param>
		/// <param name="isTransitionFunc">遷移条件関数</param>
		/// <param name="priority">優先度</param>
		StateEdgeBase(
			const EnumType from, 
			const EnumType to,
			const IsTransitionFunction& isTransitionFunc,
			const int priority
		) :
			StateEdgeBase(from, to, isTransitionFunc, static_cast<int>(to), false)
		{}

		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="from">手前のインデックス</param>
		/// <param name="to">先のインデックス</param>
		/// <param name="isTransitionFunc">遷移条件関数</param>
		/// <param name="priority">優先度</param>
		/// <param name="isEndTransition">更新処理終了時に判断するかどうか</param>
		StateEdgeBase(
			const EnumType from, 
			const EnumType to,
			const IsTransitionFunction& isTransitionFunc,
			const int priority,
			const bool isEndTransition
		) :
			GraphEdgeBase((int)from, (int)to), 
			m_isTransitionFunc(isTransitionFunc), 
			m_priority(priority), 
			m_isEndTransition(isEndTransition)
		{}

		//--------------------------------------------------------------------------------------
		///	アクセッサ
		//--------------------------------------------------------------------------------------

		/// <summary>
		/// Toに遷移する条件を設定する。
		/// </summary>
		/// <param name="func">設定する条件</param>
		void SetIsToTransition(const std::function<bool(const TransitionStructMember& member)>& func) {
			m_isTransitionFunc = func;
		}

		/// <summary>
		/// 遷移できるかどうか
		/// </summary>
		/// <param name="member">遷移条件用メンバー</param>
		/// <param name="isEndNodeUpdate">更新終了時に判断するかどうか</param>
		/// <returns></returns>
		bool IsTransition(const TransitionStructMember& member, const bool isEndNodeUpdate = false) {
			//終了時遷移なら
			if (m_isEndTransition) {
				//ノードが終了しているなら監視、そうでないならfalse
				return isEndNodeUpdate ? m_isTransitionFunc(member) : false;
			}
			
			//終了時遷移でないなら常に監視
			return m_isTransitionFunc(member);
		}

		/// <summary>
		/// 手前のノードタイプを取得
		/// </summary>
		/// <returns>手前のノードタイプ</returns>
		EnumType GetFromType() const {
			return static_cast<EnumType>(GetFrom());
		}

		/// <summary>
		/// 先のノードタイプを取得
		/// </summary>
		/// <returns>先のノードタイプ</returns>
		EnumType GetToType() const {
			return static_cast<EnumType>(GetTo());
		}

		/// <summary>
		/// 優先度の設定
		/// </summary>
		/// <param name="priority">優先度</param>
		void SetPriority(const int priority) noexcept {
			m_priority = priority;
		}

		/// <summary>
		/// 優先度の取得
		/// </summary>
		/// <returns>優先度</returns>
		int GetPriority() const noexcept {
			return m_priority;
		}

		/// <summary>
		/// 更新終了時に遷移判断するかどうかを設定
		/// </summary>
		/// <param name="isEndTransition">更新終了時に遷移判断するかどうか</param>
		void SetIsEndTransition(const bool isEndTransition) noexcept {
			m_isEndTransition = true;
		}

		/// <summary>
		/// 更新終了時に遷移判断するかどうかを取得
		/// </summary>
		/// <returns>更新終了時に遷移判断するならtrue</returns>
		bool IsEndTransition() const noexcept {
			return m_isEndTransition;
		}
	};

}

//endbasecross