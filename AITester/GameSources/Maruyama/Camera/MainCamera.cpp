/*!
@file MainCamera.cpp
@brief MainCamera�̃N���X����
�S���F�ێR�T��
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void MainCamera::OnCreate()
	{
		float x = cosf(m_radXZ);
		float y = sinf(m_radY);
		float z = sinf(m_radXZ);

		m_armVec = Vec3(x, y, z);

		Camera::OnCreate();
	}

	void MainCamera::OnUpdate()
	{
		//Camera::OnUpdate();
		//LockAtTarget();
		//TPSMove();
	}

	
	void MainCamera::TPSMove()
	{
		InputYVec();
		InputXZVec();

		auto target = m_target.lock();

		if (target)
		{
			auto targetTrans = target->GetComponent<Transform>();
			auto targetPos = targetTrans->GetPosition();

			auto pos = targetPos + (m_armVec.normalize() * m_armLange);
			SetEye(pos);
		}

	}

	void MainCamera::InputYVec()
	{
		auto pad = GetPad();
		auto delta = App::GetApp()->GetElapsedTime();

		if (!pad.bConnected)
		{
			return;
		}

		float vertical = pad.fThumbRY;

		if (vertical != 0.0f)
		{
			m_radY += vertical * delta * m_speedY;

			CheckRimitY();  //�p�x����

			m_armVec.y = sinf(m_radY);
		}
	}

	void MainCamera::InputXZVec()
	{
		auto pad = GetPad();
		auto delta = App::GetApp()->GetElapsedTime();

		if (!pad.bConnected)
		{
			return;
		}

		float horizontal = pad.fThumbRX;

		if (horizontal != 0)
		{
			m_radXZ += -horizontal * delta * m_speedXZ;

			m_armVec.x = cosf(m_radXZ);
			m_armVec.z = sinf(m_radXZ);
		}

		if (abs(m_radXZ) >= XM_2PI) {
			//���]������0�ɖ߂�
			m_radXZ = 0.0f;
		}
	}

	void MainCamera::LockAtTarget()
	{
		auto target = m_target.lock();

		if (target)
		{
			auto targetTrans = target->GetComponent<Transform>();
			auto pos = targetTrans->GetPosition();
			pos += m_lockCenterOffset;  //player��������pivot�ɂȂ��Ă��邽��Center�ʒu��ς���B  

			SetAt(pos);
		}
		
	}

	void MainCamera::CheckRimitY()
	{
		if (m_radY >= m_maxY)  //����𒴂�����
		{
			m_radY = m_maxY;
		}

		if (m_radY <= m_minY)  //�����𒴂�����
		{
			m_radY = m_minY;
		}
	}

}

//endbasecross