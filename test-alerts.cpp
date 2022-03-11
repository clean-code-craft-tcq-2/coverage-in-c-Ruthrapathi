#include "TempCheckAndAlert.h"


BreachType inferBreach(double value, double lowerLimit, double upperLimit) 
{
  BreachType lowerBreachResult = checkLowerLimit( value,  lowerLimit);
  BreachType upperBreachResult = checkUpperLimit( value,  upperLimit);
  
  return (BreachType)((int)lowerBreachResult + (int)upperBreachResult);
 
}

BreachType classifyTemperatureBreach(
  CoolingType coolingType, double temperatureInC) {
 
  int lowerLimit = 0;
  int upperLimit = 0;

 upperLimit = passiveCoolingUpperLimit( coolingType,  upperLimit);
 lowerLimit = passiveCoolingLowerLimit( coolingType,  lowerLimit);
 upperLimit = hiActiveCoolingUpperLimit( coolingType,  upperLimit);
 lowerLimit = hiActiveCoolingLowerLimit( coolingType,  lowerLimit);
 upperLimit = medActiveCoolingUpperLimit( coolingType,  upperLimit);
 lowerLimit = medActiveCoolingLowerLimit( coolingType,  lowerLimit);
  
  return inferBreach(temperatureInC, lowerLimit, upperLimit);
}

AlertTarget checkAndAlert(
    AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC, actionList *alertAction ) 
{
  
	 BreachType breachType = classifyTemperatureBreach(
		batteryChar.coolingType, temperatureInC
	  );

	 return  (*alertAction[alertTarget])(breachType);
	  
 }
 
AlertTarget  printAlert(char* alertInfo, AlertTarget target)
 {
     puts(alertInfo);
     return target;
 }


AlertTarget sendToController(BreachType breachType) 
{    	 const unsigned short header = 0xfeed;
	 char alertInfo[100];
	 sprintf(alertInfo ,"%x : %x\n", header, breachType);
	 AlertTarget result =  printAlert(alertInfo, TO_CONTROLLER );
	 return result;
}

AlertTarget sendToEmail(BreachType breachType) {
	AlertTarget target = TO_EMAIL;
if(breachType != NORMAL)
{
  const char* recepient = "a.b@c.com";
  char alertInfo[100];
  sprintf(alertInfo, "To: %s\n Hi,The Temperature is %s \n", recepient ,Breachinfo[breachType] );
  return printAlert(alertInfo, TO_EMAIL );
}
	return target;
}


