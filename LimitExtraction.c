#include "TempCheckAndAlert.h"


int  passiveCoolingUpperLimit(CoolingType coolingType, int upperLimit)
{
	if (coolingType  == PASSIVE_COOLING)
	{
		return 35;
	}
	return upperLimit;
}

int  passiveCoolingLowerLimit(CoolingType coolingType, int lowerLimit)
{
	if (coolingType  == PASSIVE_COOLING)
	{
		return 0;
	}
	return lowerLimit;
}

int  hiActiveCoolingUpperLimit(CoolingType coolingType, int upperLimit)
{
	if (coolingType  == HI_ACTIVE_COOLING)
	{
		return 45;
	}
	return upperLimit;
}

int  hiActiveCoolingLowerLimit(CoolingType coolingType, int lowerLimit)
{
	if (coolingType  == HI_ACTIVE_COOLING)
	{
		return 0;
	}
	return lowerLimit;
}
int  medActiveCoolingUpperLimit(CoolingType coolingType, int upperLimit)
{
	if (coolingType  == MED_ACTIVE_COOLING)
	{
		return 40;
	}
	return upperLimit;
}

int  medActiveCoolingLowerLimit(CoolingType coolingType, int lowerLimit)
{
	if (coolingType  == MED_ACTIVE_COOLING)
	{
		return 0;
	}
	return lowerLimit;
}

