#pragma once

namespace BitFlagFunc
{
	template<typename BitFlagType>
	void SetBitByBool(bool value, BitFlagType& flag, const BitFlagType& mask)
	{
		(value) ? flag |= mask : flag &= ~mask;
	}
}
