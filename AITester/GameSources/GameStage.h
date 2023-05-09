/*!
@file GameStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {
		//ビューの作成
		void CreateViewLight();
	public:
		//構築と破棄
		GameStage() :Stage() {}
		virtual ~GameStage() {}
		//初期化
		virtual void OnCreate()override;

		std::shared_ptr<Camera> ChangeMainCamera();

	private:
		std::shared_ptr<SingleView> m_mainView;
		std::shared_ptr<Camera> m_mainCamera;
		std::shared_ptr<GameObject> m_mainCamObj;

		void CreateMainCamera();
	};


}
//end basecross

