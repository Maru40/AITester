/*!
@file MainCameraObj.h
@brief MainCameraObjヘッダ　
担当：丸山裕喜
*/

#pragma once
#include "stdafx.h"
#include "SeekTPS.h"

namespace basecross {

	class MainCameraObj : public GameObject
	{

		std::shared_ptr<GameObject> m_target;

		Vec3 m_lockCenterOffset;
		Vec3 m_returnLookCenterOffset;

	public:

		MainCameraObj(const std::shared_ptr<Stage>& stage,
			const std::shared_ptr<GameObject>& target
		):
			GameObject(stage),
			m_target(target),
			m_lockCenterOffset(Vec3(0.0f,0.5f,0.0f)),
			m_returnLookCenterOffset(m_lockCenterOffset)
		{

		}

		void OnCreate() override;
		void OnUpdate() override;

		void LockAtTarget();

		void RayCtrl();
		//void RotationCameraStart(const float rotAngle, const Vec3& rotDirect);


		//アクセッサ
		void SetTarget(const std::shared_ptr<GameObject>& target)
		{
			m_target = target;

			auto seek = GetComponent<SeekTPS>();
			seek->SetTarget(target);

		}

		void SetArmVec(const Vec3& armVec)
		{
			GetComponent<SeekTPS>()->SetArmVec(armVec);
		}

		Vec3 GetArmOffset() const
		{
			return GetComponent<SeekTPS>()->GetArmOffset();
		}

		void SetLookCenterOffset(const Vec3& offset) {
			m_lockCenterOffset = offset;
		}

		void ReturnLookCenterOffset() {
			m_lockCenterOffset = m_returnLookCenterOffset;
		}

		void StartClearMove();
	};

}

//endbasecross