#pragma once

class I_Inputer
{
public:
	virtual ~I_Inputer() = default;

	virtual Vector GetMoveInput() = 0;
};