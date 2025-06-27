#include "gmock/gmock.h"
#include "utility.hpp"
#include "producer.hpp"

TEST(makeProducedCar, AllStep) {
	Producer pro;
	for (int step = CarType_Q; step <= Run_Test; step++) {
		int ret = pro.makeProducedCar(step, 0);
		int expected = (step + 1 > Run_Test) ? Run_Test : step + 1;
		EXPECT_EQ(ret, expected);
	}
}

TEST(makeProducedCar, nextEngine) {
	Producer pro;
	for (int carType = SEDAN; carType <= TRUCK; carType++)
	{
		int ret = pro.makeProducedCar(CarType_Q, carType);
		EXPECT_EQ(ret, Engine_Q);
	}
}

TEST(makeProducedCar, nextBrakeSystem) {
	Producer pro;
	for (int engine = GM; engine <= WIA; engine++)
	{
		int ret = pro.makeProducedCar(Engine_Q, engine);
		EXPECT_EQ(ret, BrakeSystem_Q);
	}
}

TEST(makeProducedCar, nextSteeringSystem) {
	Producer pro;
	for (int brakeSystem = MANDO; brakeSystem <= BOSCH_B; brakeSystem++)
	{
		int ret = pro.makeProducedCar(BrakeSystem_Q, brakeSystem);
		EXPECT_EQ(ret, SteeringSystem_Q);
	}
}

TEST(makeProducedCar, nextRunTest) {
	Producer pro;
	for (int steeringSystem = BOSCH_S; steeringSystem <= MOBIS; steeringSystem++)
	{
		int ret = pro.makeProducedCar(SteeringSystem_Q, steeringSystem);
		EXPECT_EQ(ret, Run_Test);
	}
}

TEST(makeProducedCar, nextRunValiCheckFalse) {
	Producer pro;
	pro.setCarType(SEDAN);
	pro.setBrakeSystem(CONTINENTAL);
	int ret = pro.makeProducedCar(Run_Test, STEP_RUN);
	EXPECT_EQ(ret, Run_Test);
}

TEST(makeProducedCar, nextRunWithInvalidEngine) {
	Producer pro;
	pro.setEngine(INVALID_E);
	int ret = pro.makeProducedCar(Run_Test, STEP_RUN);
	EXPECT_EQ(ret, Run_Test);
}

TEST(makeProducedCar, nextRunWithAllCarType) {
	Producer pro;
	int ret;
	for (int carType = SEDAN; carType <= TRUCK; carType++)
	{
		pro.setCarType(carType);
		ret = pro.makeProducedCar(Run_Test, STEP_RUN);
		EXPECT_EQ(ret, Run_Test);
	}
}

TEST(makeProducedCar, nextRunWithAllEngine) {
	Producer pro;
	int ret;
	for (int engine = GM; engine <= WIA; engine++)
	{
		pro.setEngine(engine);
		ret = pro.makeProducedCar(Run_Test, STEP_RUN);
		EXPECT_EQ(ret, Run_Test);
	}
}

TEST(makeProducedCar, nextRunWithAllBrakeSystem) {
	Producer pro;
	int ret;
	for (int brakeSystem = MANDO; brakeSystem <= BOSCH_B; brakeSystem++)
	{
		pro.setBrakeSystem(brakeSystem);
		pro.setSteeringSystem(BOSCH_S);
		ret = pro.makeProducedCar(Run_Test, STEP_RUN);
		EXPECT_EQ(ret, Run_Test);
	}
}

TEST(makeProducedCar, nextRunWithAllSteeringSystem) {
	Producer pro;
	int ret;
	for (int steeringSystem = BOSCH_S; steeringSystem <= MOBIS; steeringSystem++)
	{
		pro.setSteeringSystem(steeringSystem);
		ret = pro.makeProducedCar(Run_Test, STEP_RUN);
		EXPECT_EQ(ret, Run_Test);
	}
}

TEST(makeProducedCar, nextTestInvalidCaseCarSedan) {
	Producer pro;
	pro.setCarType(SEDAN);
	pro.setBrakeSystem(CONTINENTAL);
	int ret = pro.makeProducedCar(Run_Test, STEP_TEST);
	EXPECT_EQ(ret, Run_Test);
}

TEST(makeProducedCar, nextTestInvalidCaseCarSUV) {
	Producer pro;
	pro.setCarType(SUV);
	pro.setEngine(TOYOTA);
	int ret = pro.makeProducedCar(Run_Test, STEP_TEST);
	EXPECT_EQ(ret, Run_Test);
}

TEST(makeProducedCar, nextTestInvalidCaseCarTruckWithEngine) {
	Producer pro;
	pro.setCarType(TRUCK);
	pro.setEngine(WIA);
	int ret = pro.makeProducedCar(Run_Test, STEP_TEST);
	EXPECT_EQ(ret, Run_Test);
}

TEST(makeProducedCar, nextTestInvalidCaseCarTruckWithBrakeSystem) {
	Producer pro;
	pro.setCarType(TRUCK);
	pro.setBrakeSystem(MANDO);
	int ret = pro.makeProducedCar(Run_Test, STEP_TEST);
	EXPECT_EQ(ret, Run_Test);
}

TEST(makeProducedCar, nextTestInvalidCaseSystemBosch) {
	Producer pro;
	pro.setBrakeSystem(BOSCH_B);
	pro.setSteeringSystem(MOBIS);
	int ret = pro.makeProducedCar(Run_Test, STEP_TEST);
	EXPECT_EQ(ret, Run_Test);
}

TEST(makeProducedCar, nextTestValidCase) {
	Producer pro;
	int ret = pro.makeProducedCar(Run_Test, STEP_TEST);
	EXPECT_EQ(ret, Run_Test);
}

TEST(isValidCheck, CaseCarSedan) {
	Producer pro;
	pro.setCarType(SEDAN);
	pro.setBrakeSystem(CONTINENTAL);
	bool ret = pro.isValidCheck();
	EXPECT_EQ(ret, false);
}

TEST(isValidCheck, CaseCarSUV) {
	Producer pro;
	pro.setCarType(SUV);
	pro.setEngine(TOYOTA);
	bool ret = pro.isValidCheck();
	EXPECT_EQ(ret, false);
}

TEST(isValidCheck, CaseCarTruckWithEngine) {
	Producer pro;
	pro.setCarType(TRUCK);
	pro.setEngine(WIA);
	bool ret = pro.isValidCheck();
	EXPECT_EQ(ret, false);
}

TEST(isValidCheck, CaseCarTruckWithBrakeSystem) {
	Producer pro;
	pro.setCarType(TRUCK);
	pro.setBrakeSystem(MANDO);
	bool ret = pro.isValidCheck();
	EXPECT_EQ(ret, false);
}

TEST(isValidCheck, CaseSystemBosch) {
	Producer pro;
	pro.setBrakeSystem(BOSCH_B);
	pro.setSteeringSystem(MOBIS);
	bool ret = pro.isValidCheck();
	EXPECT_EQ(ret, false);
}

TEST(isValidCheck, Pass) {
	Producer pro;
	pro.setCarType(SEDAN);
	pro.setBrakeSystem(MANDO);
	bool ret = pro.isValidCheck();
	EXPECT_EQ(ret, true);
}

