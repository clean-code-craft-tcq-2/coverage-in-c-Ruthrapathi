#include <stdio.h>

typedef enum {
  PASSIVE_COOLING,
  HI_ACTIVE_COOLING,
  MED_ACTIVE_COOLING
} CoolingType;

typedef enum {
  NORMAL,
  TOO_LOW,
  TOO_HIGH,
  BREACH_TYPE_LENGTH
} BreachType;

typedef enum {
  TO_CONTROLLER,
  TO_EMAIL,
  ALERT_TARGET_LENGTH
} AlertTarget;

typedef struct {
  CoolingType coolingType;
  char brand[48];
} BatteryCharacter;

const char Breachinfo[BREACH_TYPE_LENGTH][10] = {"Normal","Too Low","Too High"};

typedef AlertTarget (*actionList) (BreachType breachType);

int  passiveCoolingUpperLimit(CoolingType coolingType, int upperLimit);
int  passiveCoolingLowerLimit(CoolingType coolingType, int lowerLimit);
int  hiActiveCoolingUpperLimit(CoolingType coolingType, int upperLimit);
int  hiActiveCoolingLowerLimit(CoolingType coolingType, int lowerLimit);
int  medActiveCoolingUpperLimit(CoolingType coolingType, int upperLimit);
int  medActiveCoolingLowerLimit(CoolingType coolingType, int lowerLimit);
BreachType checkLowerLimit(double value, double lowerLimit);
BreachType checkUpperLimit(double value, double upperLimit);
BreachType inferBreach(double value, double lowerLimit, double upperLimit);
BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC);
AlertTarget checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC, actionList *alertAction ); 
AlertTarget sendToController(BreachType breachType);
AlertTarget sendToEmail(BreachType breachType);
AlertTarget  printAlert(char* alertInfo, AlertTarget target);


