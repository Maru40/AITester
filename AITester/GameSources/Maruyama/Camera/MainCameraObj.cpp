/*!
@file MainCameraObj.cpp
@brief MainCameraObjのクラス実体
担当：丸山裕喜
*/

#include "stdafx.h"
#include "Project.h"

#include "MainCameraObj.h"

namespace basecross {

	void MainCameraObj::OnCreate()
	{

		AddComponent<SeekTPS>(m_target);
		AddComponent<UpCamera>();
		AddComponent<ToTargetMove>();
		//AddComponent<Rotation>();

		//オブジェクトのグループを得る
		auto group = GetStage()->GetSharedObjectGroup(L"rotate");
		//グループに自分自身を追加
		group->IntoGroup(GetThis<GameObject>());

		//auto drawComp = AddComponent<BcPNTStaticDraw>();
		//drawComp->SetMeshResource(L"DEFAULT_CUBE");
		//auto trans = GetComponent<Transform>();
		//trans->SetScale(Vec3(2.0f,2.0f,2.0f));
	}

	void MainCameraObj::OnUpdate()
	{
		LockAtTarget();

		RayCtrl();
	}

	void MainCameraObj::LockAtTarget()
	{
		auto camera = OnGetDrawCamera();

		auto targetTrans = m_target->GetComponent<Transform>();

		//親を付けたままだと、親の方を見てしまうため。
		//auto parent = targetTrans->GetParent();
		//targetTrans->ClearParent();

		auto pos = targetTrans->GetWorldPosition();
		
		pos += m_lockCenterOffset;  //playerが足元がpivotになっているためCenter位置を変える。  

		camera->SetAt(pos);
	}

	void MainCameraObj::RayCtrl() 
	{
		
		auto selfPos = GetComponent<Transform>()->GetPosition();
		auto targetPos = m_target->GetComponent<Transform>()->GetPosition();

		auto objs = GetStage()->GetGameObjectVec();
		for (auto& obj : objs)
		{
			if (obj == m_target) {  //相手がターゲットだったら処理を飛ばす。
				continue;
			}

			auto col = obj->GetComponent<CollisionObb>(false);
			if (col) {  //コリジョンを持っていたら。
				if (HitTest::SEGMENT_OBB(selfPos, targetPos, col->GetObb())) {  //コリジョンに当たっていたら。
					obj->SetDrawActive(false);
				}
				else {
					obj->SetDrawActive(true);
				}
			}
			
		}
	}

	void MainCameraObj::StartClearMove() {
		auto stage = GetGameStage();
		if (!stage) {
			return;
		}

		float armLength = 1.75f;
		Vec3 offsetPos(-0.0f,0.75f,0.0f);
		GetComponent<SeekTPS>()->SetUpdateActive(false);

		auto player = stage->GetPlayer();
		auto targetTrans = player->GetComponent<Transform>();
		auto targetPos = targetTrans->GetPosition();
		auto targetForward = targetTrans->GetForward();
		
		targetPos += targetForward * armLength;
		targetPos += offsetPos;
		//auto toTargetVec = ToTargetVec(player);

		auto targetMove = GetComponent<ToTargetMove>();
		targetMove->MoveStart(targetPos);
	}

	//void MainCameraObj::RotationCameraStart()
	//{

	//}

}

//endbasecross