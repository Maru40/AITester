/*!
@file MainCameraObj.cpp
@brief MainCameraObj�̃N���X����
�S���F�ێR�T��
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

		//�I�u�W�F�N�g�̃O���[�v�𓾂�
		auto group = GetStage()->GetSharedObjectGroup(L"rotate");
		//�O���[�v�Ɏ������g��ǉ�
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

		//�e��t�����܂܂��ƁA�e�̕������Ă��܂����߁B
		//auto parent = targetTrans->GetParent();
		//targetTrans->ClearParent();

		auto pos = targetTrans->GetWorldPosition();
		
		pos += m_lockCenterOffset;  //player��������pivot�ɂȂ��Ă��邽��Center�ʒu��ς���B  

		camera->SetAt(pos);
	}

	void MainCameraObj::RayCtrl() 
	{
		
		auto selfPos = GetComponent<Transform>()->GetPosition();
		auto targetPos = m_target->GetComponent<Transform>()->GetPosition();

		auto objs = GetStage()->GetGameObjectVec();
		for (auto& obj : objs)
		{
			if (obj == m_target) {  //���肪�^�[�Q�b�g�������珈�����΂��B
				continue;
			}

			auto col = obj->GetComponent<CollisionObb>(false);
			if (col) {  //�R���W�����������Ă�����B
				if (HitTest::SEGMENT_OBB(selfPos, targetPos, col->GetObb())) {  //�R���W�����ɓ������Ă�����B
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