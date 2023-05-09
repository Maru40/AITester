/*!
@file MainCamera.h
@brief メインカメラヘッダ　
担当：丸山裕喜
*/

#pragma once
#include "stdafx.h"
#include "MainCameraObj.h"

namespace basecross {

	class MainCamera : public Camera
	{
		const CONTROLER_STATE GetPad() const
		{
			auto& app = App::GetApp();
			auto device = app->GetInputDevice();
			auto pad = device.GetControlerVec()[0];
			return pad;
		}

		std::weak_ptr<GameObject> m_target;

		float m_armLange;
		Vec3 m_armVec;

		float m_speedY;
		float m_speedXZ;
		float m_radY;
		float m_radXZ;
		float m_maxY;
		float m_minY;

		Vec3 m_lockCenterOffset;
		Vec3 m_returnLookCenterOffset;

	public:
		MainCamera(const std::weak_ptr<GameObject>& target):
			MainCamera(
				target,
				5.0f,
				Vec3(0.0f, 0.5f, 1.0f),
				1.0f,
				2.0f,
				XMConvertToRadians(+30.0f),
				XMConvertToRadians(-90.0f),
				XMConvertToRadians(+45.0f),
				XMConvertToRadians(+10.0f),
				Vec3(0.0f,1.0f,0.0f))
				
		{}

		MainCamera(const std::weak_ptr<GameObject>& target,
			const float armLange,
			const Vec3& armVec,
			const float speedY,
			const float speedXZ,
			const float radY,
			const float radXZ,
			const float maxY,
			const float minY,
			const Vec3& lockCenterOffset
		) :
			Camera(),
			m_target(target),
			m_armLange(armLange),
			m_armVec(armVec),
			m_speedY(speedY),
			m_speedXZ(speedXZ),
			m_radY(radY),
			m_radXZ(radXZ),
			m_maxY(maxY),
			m_minY(minY),
			m_lockCenterOffset(lockCenterOffset),
			m_returnLookCenterOffset(lockCenterOffset)
		{}

		~MainCamera() {}

		void OnCreate() override;
		void OnUpdate() override;

		void TPSMove();
		void InputYVec();
		void InputXZVec();
		void LockAtTarget();
		void CheckRimitY();


		//アクセッサ
		void SetTarget(const std::shared_ptr<GameObject>& target)
		{
			m_target = target;

			//カメラオブジェクトが存在したら。
			auto camObj = GetCameraObject();
			if (camObj)
			{
				auto mainCamObj = dynamic_pointer_cast<MainCameraObj>(camObj);
				if (mainCamObj)
				{
					mainCamObj->SetTarget(target);
				}
			}
		}

		Vec3 GetArmOffset() const
		{
			return m_armVec * m_armLange;
		}

		void SetLookCenterOffset(const Vec3& offset) {
			m_lockCenterOffset = offset;
		}

		void ReturnLookCenterOffset() {
			m_lockCenterOffset = m_returnLookCenterOffset;
		}
	};

}