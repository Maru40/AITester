/*!
@file GameStage.cpp
@brief ゲームステージ実体
*/

#include "stdafx.h"
#include "Project.h"

#include "Maruyama/Camera/SeekTPS.h"
#include "Maruyama/Player/Object/PlayerObject.h"
#include "PlayerInputer.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス実体
	//--------------------------------------------------------------------------------------
	void GameStage::CreateViewLight() {
		//const Vec3 eye(0.0f, 5.0f, -5.0f);
		//const Vec3 at(0.0f);
		//auto PtrView = CreateView<SingleView>();
		////ビューのカメラの設定
		//auto PtrCamera = ObjectFactory::Create<Camera>();
		//PtrView->SetCamera(PtrCamera);
		//PtrCamera->SetEye(eye);
		//PtrCamera->SetAt(at);
		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();
	}



	void GameStage::OnCreate() {
		try {

			EventSystem::GetInstance(GetThis<Stage>())->SetBasicInputer(PlayerInputer::GetInstance());
			//ビューとライトの作成
			CreateViewLight();
			CreateMainCamera();

			AddGameObject<PlayerObject>();
		}
		catch (...) {
			throw;
		}
	}

	void GameStage::CreateMainCamera()
	{
		const Vec3 eye(0.0f, 5.0f, -5.0f);
		const Vec3 at(0.0f);

		//メインカメラの実装
		m_mainView = ObjectFactory::Create<SingleView>(GetThis<Stage>());
		//m_mainView = CreateView<SingleView>();
		m_mainCamera = ObjectFactory::Create<Camera>();
		m_mainView->SetCamera(m_mainCamera);
		m_mainCamera->SetEye(eye);
		m_mainCamera->SetAt(at);
		m_mainCamObj = AddGameObject<GameObject>();
		auto mainTrans = m_mainCamObj->GetComponent<Transform>();
		mainTrans->SetPosition(eye);
		m_mainCamObj->SetUpdateActive(false);   //こいつがアクティブになるまで処理を行わない。

		ChangeMainCamera();
		//auto lookTarget = m_player->GetComponent<LookTarget>(false);
		//if (lookTarget) {
		//	lookTarget->SetTarget(m_mainCamObj);
		//}
	}

	std::shared_ptr<Camera> 
	GameStage::ChangeMainCamera()
	{
		auto ptrObjCamera = m_mainView->GetCamera();
		if (ptrObjCamera)
		{
			ptrObjCamera->SetCameraObject(m_mainCamObj);
		}

		SetView(m_mainView);

		m_mainCamObj->SetUpdateActive(true);
		return dynamic_pointer_cast<Camera>(ptrObjCamera);
	}

}
//end basecross
