#include "TempCheckAndAlert.h"

BreachType checkLowerLimit(double value, double lowerLimit)
{
	if(value < lowerLimit) 
	{
    return TOO_LOW;
	}
	 return NORMAL;
}
BreachType checkUpperLimit(double value, double upperLimit)
{
	if(value > upperLimit)
 	{
    return TOO_HIGH;
    }
	 return NORMAL;
}
