#include "gmock/gmock.h"
#include "utility.hpp"
#include "logger.hpp"

TEST(printStepGuide, AllStep) {
	Logger log;

	for(int step = CarType_Q; step <= Run_Test; step++)
		log.printStepGuide(step);
}

TEST(IsExitAfterClearEnter, NotExit) {
	Logger log;
	char buf[100] = "1";

	int ret = log.IsExitAfterClearEnter(buf);
	EXPECT_EQ(ret, false);
}

TEST(IsExitAfterClearEnter, Exit) {
	Logger log;
	char buf[100] = "exit";

	int ret = log.IsExitAfterClearEnter(buf);
	EXPECT_EQ(ret, true);
}


TEST(isNotNumber, PossibleNumber) {
	Logger log;
	char inputBuf[100] = "0";
	char* inputNumber;
	int selectNumber = strtol(inputBuf, &inputNumber, 10); 

	int ret = log.isNotNumber(inputNumber);
	EXPECT_EQ(ret, false);
}

TEST(isNotNumber, ImpossibleNumber) {
	Logger log;
	char inputBuf[100] = "dd";
	char* inputNumber;
	int selectNumber = strtol(inputBuf, &inputNumber, 10); 

	int ret = log.isNotNumber(inputNumber);
	EXPECT_EQ(ret, true);
}

TEST(isInvalidNumberByStep, CarTypePass) {
	Logger log;
	int step = CarType_Q;
	int number = TRUCK;
	int ret = log.isInvalidNumberByStep(step, number);
	EXPECT_EQ(ret, false);
}

TEST(isInvalidNumberByStep, CarTypeFail) {
	Logger log;
	int step = CarType_Q;
	int number = TRUCK+1;
	int ret = log.isInvalidNumberByStep(step, number);
	EXPECT_EQ(ret, true);
}

TEST(isInvalidNumberByStep, EnginePass) {
	Logger log;
	int step = Engine_Q;
	int number = INVALID_E;
	int ret = log.isInvalidNumberByStep(step, number);
	EXPECT_EQ(ret, false);
}

TEST(isInvalidNumberByStep, EngineFail) {
	Logger log;
	int step = Engine_Q;
	int number = INVALID_E +1;
	int ret = log.isInvalidNumberByStep(step, number);
	EXPECT_EQ(ret, true);
}

TEST(isInvalidNumberByStep, BrakeSystemPass) {
	Logger log;
	int step = BrakeSystem_Q;
	int number = BOSCH_B;
	int ret = log.isInvalidNumberByStep(step, number);
	EXPECT_EQ(ret, false);
}

TEST(isInvalidNumberByStep, BrakeSystemFail) {
	Logger log;
	int step = BrakeSystem_Q;
	int number = BOSCH_B +1;
	int ret = log.isInvalidNumberByStep(step, number);
	EXPECT_EQ(ret, true);
}

TEST(isInvalidNumberByStep, SteeringSystemPass) {
	Logger log;
	int step = SteeringSystem_Q;
	int number = MOBIS;
	int ret = log.isInvalidNumberByStep(step, number);
	EXPECT_EQ(ret, false);
}

TEST(isInvalidNumberByStep, SteeringSystemFail) {
	Logger log;
	int step = SteeringSystem_Q;
	int number = MOBIS +1;
	int ret = log.isInvalidNumberByStep(step, number);
	EXPECT_EQ(ret, true);
}

TEST(isInvalidNumberByStep, RunTestPass) {
	Logger log;
	int step = Run_Test;
	int number = STEP_TEST;
	int ret = log.isInvalidNumberByStep(step, number);
	EXPECT_EQ(ret, false);
}

TEST(isInvalidNumberByStep, RunTestFail) {
	Logger log;
	int step = Run_Test;
	int number = STEP_TEST +1;
	int ret = log.isInvalidNumberByStep(step, number);
	EXPECT_EQ(ret, true);
}

TEST(isInvalidNumberByStep, GoFirstStep) {
	Logger log;
	int step = Run_Test;
	int number = 0; //BACK_NUMBER
	int ret = log.isInvalidNumberByStep(step, number);
	EXPECT_EQ(ret, true);
}

TEST(isInvalidNumberByStep, GoBackStep) {
	Logger log;
	int step = Engine_Q;
	int number = 0; //BACK_NUMBER
	int ret = log.isInvalidNumberByStep(step, number);
	EXPECT_EQ(ret, true);
}