/*!
@file   Animator.cpp
@brief  アニメーション管理クラス実体
*/

#include "stdafx.h"
#include "Animator.h"
#include "../Utility/CSVLoad.h"
#include "../Utility/DataExtracter.h"

namespace basecross {

	TimeEventData::TimeEventData():
		TimeEventData(0, nullptr)
	{}

	TimeEventData::TimeEventData(const f32 time, const std::function<void()>& timeEvent):
		time(time),
		timeEvent(timeEvent),
		isActive(true)
	{}


	void AnimationClip::ResetTimeEvent()
	{
		for (auto& data : timeEventDatas)
		{
			//アクティブ状態なら、タイムイベントを呼ぶ。
			if (data.isActive) {
				data.timeEvent();
			}

			data.isActive = true;
		}
	}


	Animator::Animator(const shared_ptr<GameObject>& owner)
		:Component(owner)
	{}

	vector<AnimationClip> Animator::LoadAnimationData(const wstring& csvKey) {
		if (!CSVLoad::GetInstance()->CheckData(csvKey)) {
			throw BaseException(
				L"指定したキーがありません。",
				L"csvKey : " + csvKey,
				L"Animator::LoadMotionData()"
			);
		}

		vector<AnimationClip> outputData;
		m_animationClipMap.clear();

		auto fileData = CSVLoad::GetInstance()->GetData(csvKey);
		for (int i = 0; i < fileData.size(); i++) {
			// 1行目は見出しなので無視
			if (i == 0) {
				continue;
			}
			// ","で区切る
			auto delimiterData = DataExtracter::DelimitData(fileData[i]);
			AnimationClip clip(
				delimiterData[0],
				(int)_wtof(delimiterData[1].c_str()),
				(int)_wtof(delimiterData[2].c_str()),
				Utility::WStrToBool(delimiterData[3]),
				(float)_wtof(delimiterData[4].c_str())
			);
			outputData.push_back(clip);
			m_animationClipMap[delimiterData[0]] = clip;
		}

		return outputData;
	}

	void Animator::RegisterAnimationClip(AnimationClip clip) {
		auto drawer = GetGameObject()->GetComponent<ModelDrawComp>();
		drawer->AddAnimation(clip.name,
			clip.start, clip.end - clip.start,
			clip.isLoop, 30);
	}

	void Animator::ChangeAnimation(wstring key) {
		GetCurrentAnimationClip().ResetTimeEvent();

		auto drawer = GetGameObject()->GetComponent<ModelDrawComp>();
		drawer->ChangeCurrentAnimation(key);
	}

	AnimationClip Animator::GetAnimationClip(const wstring& key) const
	{
		return m_animationClipMap.at(key);
	}

	AnimationClip Animator::GetCurrentAnimationClip() const
	{
		auto draw = GetGameObject()->GetComponent<ModelDrawComp>();
		auto currentAnimation = draw->GetCurrentAnimation();
		return m_animationClipMap.at(currentAnimation);
	}

	void Animator::OnUpdate() {
		auto drawer = GetGameObject()->GetComponent<ModelDrawComp>();
		drawer->UpdateAnimation(App::GetApp()->GetElapsedTime() * GetPlaySpeed());

		CallTimeEvent();		//タイムイベントの実装
		CallLoopEndEvent();		//終了イベントの実装
	}

	bool Animator::IsTargetAnimationEnd() {
		auto drawer = GetGameObject()->GetComponent<ModelDrawComp>();
		return drawer->IsTargetAnimeEnd();
	}

	float Animator::GetPlaySpeed() {
		auto drawer = GetGameObject()->GetComponent<ModelDrawComp>();
		auto keyName = drawer->GetCurrentAnimation();

		return m_animationClipMap[keyName].playSpeed;
	}

	void Animator::CallTimeEvent()
	{
		auto draw = GetGameObject()->GetComponent<ModelDrawComp>();
		f32 currentTime = draw->GetCurrentAnimationTime();

		auto currentClip = GetCurrentAnimationClip();
		auto datas = currentClip.timeEventDatas;

		for (auto& data : datas) {
			if (!data.isActive) {	//アクティブでないなら処理をとばす
				continue;
			}

			if (data.time < currentTime) {	//時間を超えていたら。
				if (data.timeEvent) {
					data.timeEvent();
					data.isActive = false;
				}
			}
		}
	}

	void Animator::CallLoopEndEvent()
	{
		auto draw = GetGameObject()->GetComponent<ModelDrawComp>();
		f32 currentTime = draw->GetCurrentAnimationTime();
		auto currentClip = GetCurrentAnimationClip();

		if (currentTime < mBeforeTime) {
			currentClip.CallLoopEndEvent();
			currentClip.ResetTimeEvent();
		}

		mBeforeTime = currentTime;	//前のフレームの時間を設定
	}

}