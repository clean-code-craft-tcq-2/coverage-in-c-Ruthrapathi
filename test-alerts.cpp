#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "TempCheckAndAlert.h"

actionList fpArrayOfActions[ALERT_TARGET_LENGTH] = {sendToController,sendToEmail};



TEST_CASE("Extracts Passive cooling Upper limit") {
  REQUIRE(passiveCoolingUpperLimit(PASSIVE_COOLING, 12) == 35);
  REQUIRE(passiveCoolingUpperLimit(HI_ACTIVE_COOLING, 12) == 12);
  REQUIRE(passiveCoolingUpperLimit(MED_ACTIVE_COOLING, 0) == 0);
  
}


TEST_CASE("Extracts Passive cooling Lowet limit") {
  REQUIRE(passiveCoolingLowerLimit(PASSIVE_COOLING, 12) == 0);
  REQUIRE(passiveCoolingLowerLimit(HI_ACTIVE_COOLING, 12) == 12);
  REQUIRE(passiveCoolingLowerLimit(MED_ACTIVE_COOLING, 14) == 14);
  
}

TEST_CASE("Extracts High Active cooling Upper limit") {
  REQUIRE(hiActiveCoolingUpperLimit(PASSIVE_COOLING, 12) == 12);
  REQUIRE(hiActiveCoolingUpperLimit(HI_ACTIVE_COOLING, 12) == 45);
  REQUIRE(hiActiveCoolingUpperLimit(MED_ACTIVE_COOLING, 0) == 0);
  
}


TEST_CASE("Extracts High Active cooling Lowet limit") {
  REQUIRE(hiActiveCoolingLowerLimit(PASSIVE_COOLING, 12) == 12);
  REQUIRE(hiActiveCoolingLowerLimit(HI_ACTIVE_COOLING, 44) == 0);
  REQUIRE(hiActiveCoolingLowerLimit(MED_ACTIVE_COOLING, 4) == 4);
  
}

TEST_CASE("Extracts Medium Active cooling Upper limit") {
  REQUIRE(medActiveCoolingUpperLimit(PASSIVE_COOLING, 12) == 12);
  REQUIRE(medActiveCoolingUpperLimit(HI_ACTIVE_COOLING, 12) == 12);
  REQUIRE(medActiveCoolingUpperLimit(MED_ACTIVE_COOLING, 10) == 40);
  
}


TEST_CASE("Extracts Medium Active cooling Lowet limit") {
  REQUIRE(medActiveCoolingLowerLimit(PASSIVE_COOLING, 40) == 40);
  REQUIRE(medActiveCoolingLowerLimit(HI_ACTIVE_COOLING, 12) == 12);
  REQUIRE(medActiveCoolingLowerLimit(MED_ACTIVE_COOLING, 14) == 0);
  
}


TEST_CASE("Check the lower limit breach for a value") {
  REQUIRE(checkLowerLimit(10, 0) == NORMAL);
  REQUIRE(checkLowerLimit(-1, 0) == TOO_LOW);
    
}

TEST_CASE("Check the Higher limit breach for a value") {
  REQUIRE(checkUpperLimit(10, 35) == NORMAL);
  REQUIRE(checkUpperLimit(50, 45) == TOO_HIGH);
    
}
TEST_CASE("infers the breach according to limits") {
  REQUIRE(inferBreach(12, 20, 30) == TOO_LOW);
  REQUIRE(inferBreach(22, 20, 30) == NORMAL);
  REQUIRE(inferBreach(32, 20, 30) == TOO_HIGH);
  
}

TEST_CASE("Given Temperature is classified based on the Breach limits")

{
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 41) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, 12) == NORMAL);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, -1) == TOO_LOW);
  
}

TEST_CASE("Checks for temperature Breach and alert")

{
	
 BatteryCharacter batteryChar1 = {PASSIVE_COOLING,"Nothing"};
 REQUIRE(checkAndAlert(TO_CONTROLLER,batteryChar1, 41,fpArrayOfActions) == TO_CONTROLLER);
 BatteryCharacter batteryChar2 = {HI_ACTIVE_COOLING,"Nothing"};
 REQUIRE(checkAndAlert(TO_EMAIL,batteryChar2, 15,fpArrayOfActions) == TO_EMAIL);
 BatteryCharacter batteryChar3 = {MED_ACTIVE_COOLING,"Nothing"};
 REQUIRE(checkAndAlert(TO_CONTROLLER,batteryChar3, 41,fpArrayOfActions) == TO_CONTROLLER);
 BatteryCharacter batteryChar4 = {HI_ACTIVE_COOLING,"Nothing"};
 REQUIRE(checkAndAlert(TO_EMAIL,batteryChar4, -1,fpArrayOfActions) == TO_EMAIL);
	
}

TEST_CASE("Prints the given string and returns the function caller ID")
{
const char* str = "To: @kiruthi \n The temperature is Too Low";
  REQUIRE(printAlert("To: @kiruthi \n The temperature is Too Low",TO_CONTROLLER) == TO_CONTROLLER);
  
}

TEST_CASE("Sending the Breach information to Controller")
{
  REQUIRE(sendToController(TOO_HIGH) == TO_CONTROLLER);
    REQUIRE(sendToController(NORMAL) == TO_CONTROLLER);
 }

TEST_CASE("Sending the Breach information to EMAIL")
{
  
  REQUIRE(sendToEmail(TOO_LOW) == TO_EMAIL);
  REQUIRE(sendToEmail(NORMAL) == TO_EMAIL);
}
