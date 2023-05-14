#pragma once

namespace AI
{
	/// <summary>
	/// 影響データ
	/// </summary>
	struct InfluenceData
	{
		f32 dengerValue;	//危険度

		InfluenceData();
		InfluenceData(const f32 dengerValue);
	};
}