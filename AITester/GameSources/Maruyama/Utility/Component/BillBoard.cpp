
/*!
@file BillBoard.cpp
@brief BillBoardクラス実体
担当：丸山裕喜
*/

#include "stdafx.h"
#include "Project.h"
#include "BillBoard.h"

#include "Maruyama/Utility/Utility.h"
#include "Maruyama/Utility/Mathf.h"

namespace basecross {

	void BillBoard::OnUpdate() {
		// カメラを取得する
		auto camera = dynamic_pointer_cast<Camera>(GetStage()->GetView()->GetTargetCamera());

		auto transComp = GetGameObject()->GetComponent<Transform>();
		auto pos = transComp->GetPosition();

		// カメラへの回転を算出する
		auto boardToCamera = camera->GetEye() - pos;
		//boardToCamera.y = 0.0f;
		boardToCamera.normalize();
		float rotY = atan2f(-boardToCamera.z, boardToCamera.x) + maru::Utility::FOWARD_ADJUST;

		auto rotation = transComp->GetRotation();
		boardToCamera.y = 0.0f;
		transComp->SetForward(boardToCamera);

		//回転調整offset
		Quat quat = transComp->GetQuaternion();
		quat *= (Quat)XMQuaternionRotationAxis(transComp->GetRight(), m_rotationOffset.x);
		quat *= (Quat)XMQuaternionRotationAxis(transComp->GetUp(), m_rotationOffset.y);
		quat *= (Quat)XMQuaternionRotationAxis(transComp->GetForward(), m_rotationOffset.z);

		transComp->SetQuaternion(quat);

	}

}

//endbasecross