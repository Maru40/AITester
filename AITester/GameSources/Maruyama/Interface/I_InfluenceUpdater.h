#pragma once

namespace basecross
{
	class EyeSearchRange;
}

namespace AI
{

	/// <summary>
	/// �e���x�X�V��
	/// </summary>
	class I_InfluenceUpdater
	{
	public:
		virtual ~I_InfluenceUpdater() = default;

		void GetEye() const;
	};
}