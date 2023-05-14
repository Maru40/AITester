#include "InfluenceData.h"

namespace AI
{
	InfluenceData::InfluenceData() :
		InfluenceData(0.5f)
	{}

	InfluenceData::InfluenceData(const f32 dengerValue):
		dengerValue(dengerValue)
	{}
}