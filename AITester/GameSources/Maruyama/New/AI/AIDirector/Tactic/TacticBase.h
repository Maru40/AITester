#pragma once

#include "stdafx.h"

class Targeted;

namespace AI
{

	class TacticMember;

	struct TacticInfo
	{
		Targeted* targeted = nullptr;			//��p�̃^�[�Q�b�g
		u32 index = 0;							//��p�ԍ��C���f�b�N�X
		u32 numAssigne = 0;						//�A�T�C�����鐔
		std::vector<TacticMember*> members;	//�A�T�C�����Ă��郁���o�[

		TacticInfo();
		TacticInfo(Targeted* const targeted, const u32 index, const u32 numAssigne);
	};

	class TacticBase
	{
	public:
		using Info = TacticInfo;

	public:
		TacticBase();

		virtual ~TacticBase() = default;

		void AssignMember(TacticMember* const member);
		void UnAssignMember(TacticMember* const member);

	private:
		Info mInfo;
	};

}