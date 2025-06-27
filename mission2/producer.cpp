#include "utility.hpp"
#include "producer.hpp"
#include "printer.hpp"

int Producer::makeProducedCar(int step, int number)
{
    if (step == CarType_Q)
    {
        printSelectedCarType(number);
        delay(800);
        return Engine_Q;
    }
    else if (step == Engine_Q)
    {
        printSelectedEngine(number);
        delay(800);
        return BrakeSystem_Q;
    }
    else if (step == BrakeSystem_Q)
    {
        printSelectedBrakeSystem(number);
        delay(800);
        return SteeringSystem_Q;
    }
    else if (step == SteeringSystem_Q)
    {
        printSelectedSteeringSystem(number);
        delay(800);
        return Run_Test;
    }
    else if (step == Run_Test) 
    {
        doRunTestProducedCar(number);
        return Run_Test;
    }
}

void Producer::printSelectedCarType(int carType)
{
    stack[CarType_Q] = carType;
    if (carType == SEDAN)
        printf("차량 타입으로 Sedan을 선택하셨습니다.\n");
    if (carType == SUV)
        printf("차량 타입으로 SUV을 선택하셨습니다.\n");
    if (carType == TRUCK)
        printf("차량 타입으로 Truck을 선택하셨습니다.\n");
}

void Producer::printSelectedEngine(int engine)
{
    stack[Engine_Q] = engine;
    if (engine == GM)
        printf("GM 엔진을 선택하셨습니다.\n");
    if (engine == TOYOTA)
        printf("TOYOTA 엔진을 선택하셨습니다.\n");
    if (engine == WIA)
        printf("WIA 엔진을 선택하셨습니다.\n");
}

void Producer::printSelectedBrakeSystem(int brakeSystem)
{
    stack[BrakeSystem_Q] = brakeSystem;
    if (brakeSystem == MANDO)
        printf("MANDO 제동장치를 선택하셨습니다.\n");
    if (brakeSystem == CONTINENTAL)
        printf("CONTINENTAL 제동장치를 선택하셨습니다.\n");
    if (brakeSystem == BOSCH_B)
        printf("BOSCH 제동장치를 선택하셨습니다.\n");
}

void Producer::printSelectedSteeringSystem(int steeringSystem)
{
    stack[SteeringSystem_Q] = steeringSystem;
    if (steeringSystem == BOSCH_S)
        printf("BOSCH 조향장치를 선택하셨습니다.\n");
    if (steeringSystem == MOBIS)
        printf("MOBIS 조향장치를 선택하셨습니다.\n");
}

void Producer::doRunTestProducedCar(int number)
{
    if (number == STEP_RUN)
    {
        runProducedCar();
        delay(2000);
    }
    else if (number == STEP_TEST)
    {
        printf("Test...\n");
        delay(1500);
        testProducedCar();
        delay(2000);
    }
}

void Producer::runProducedCar()
{
    if (isValidCheck() == false)
    {
        printf("자동차가 동작되지 않습니다\n");
        return;
    }

    if (stack[Engine_Q] == INVALID_E)
    {
        printf("엔진이 고장나있습니다.\n");
        printf("자동차가 움직이지 않습니다.\n");
        return;
    }

    Printer print = Printer::GetInstance();
    print.printCurrentStackCarType(stack[CarType_Q]);
    print.printCurrentStackEngine(stack[Engine_Q]);
    print.printCurrentStackBrakeSystem(stack[BrakeSystem_Q]);
    print.printCurrentStackSteeringSystem(stack[SteeringSystem_Q]);
    printf("자동차가 동작됩니다.\n");
}

int Producer::isValidCheck()
{
    if (isInvalidCheckForCarSedan()) return false;
    else if (isInvalidCheckForCarSUV()) return false;
    else if (isInvalidCheckForCarTruckWithEngine()) return false;
    else if (isInvalidCheckForCarTruckWithBrakeSystem()) return false;
    else if (isInvalidCheckForSystemBosch()) return false;
    return true;
}

bool Producer::isInvalidCheckForCarSedan()
{
    return stack[CarType_Q] == SEDAN && stack[BrakeSystem_Q] == CONTINENTAL;
}

bool Producer::isInvalidCheckForCarSUV()
{
    return stack[CarType_Q] == SUV && stack[Engine_Q] == TOYOTA;
}

bool Producer::isInvalidCheckForCarTruckWithEngine()
{
    return stack[CarType_Q] == TRUCK && stack[Engine_Q] == WIA;
}

bool Producer::isInvalidCheckForCarTruckWithBrakeSystem()
{
    return stack[CarType_Q] == TRUCK && stack[BrakeSystem_Q] == MANDO;
}

bool Producer::isInvalidCheckForSystemBosch()
{
    return stack[BrakeSystem_Q] == BOSCH_B && stack[SteeringSystem_Q] != BOSCH_S;
}

void Producer::testProducedCar()
{
    const char* FAIL = "자동차 부품 조합 테스트 결과 : FAIL\n";
    const char* PASS = "자동차 부품 조합 테스트 결과 : PASS\n";

    if (isInvalidCheckForCarSedan())
    {
        printf("%s", FAIL);
        printf("Sedan에는 Continental제동장치 사용 불가\n");
    }
    else if (isInvalidCheckForCarSUV())
    {
        printf("%s", FAIL);
        printf("SUV에는 TOYOTA엔진 사용 불가\n");
    }
    else if (isInvalidCheckForCarTruckWithEngine())
    {
        printf("%s", FAIL);
        printf("Truck에는 WIA엔진 사용 불가\n");
    }
    else if (isInvalidCheckForCarTruckWithBrakeSystem())
    {
        printf("%s", FAIL);
        printf("Truck에는 Mando제동장치 사용 불가\n");
    }
    else if (isInvalidCheckForSystemBosch())
    {
        printf("%s", FAIL);
        printf("Bosch제동장치에는 Bosch조향장치 이외 사용 불가\n");
    }
    else
    {
        printf("%s", PASS);
    }
}

//int Producer::getCarType() {
//    return stack[CarType_Q];
//}
//int Producer::getEngine() {
//    return stack[Engine_Q];
//}
//int Producer::getBrakeSystem() {
//    return stack[BrakeSystem_Q];
//}
//int Producer::getSteeringSystem() {
//    return stack[SteeringSystem_Q];
//}

void Producer::setCarType(int carType) {
    stack[CarType_Q] = carType;
}

void Producer::setEngine(int engine) {
    stack[Engine_Q] = engine;
}

void Producer::setBrakeSystem(int brakeSystem) {
    stack[BrakeSystem_Q] = brakeSystem;
}

void Producer::setSteeringSystem(int steeringSystem) {
    stack[SteeringSystem_Q] = steeringSystem;
}

void Producer::delay(int ms)
{
    volatile int sum = 0;
    for (int i = 0; i < 1000; i++)
    {
        for (int j = 0; j < 1000; j++)
        {
            for (int t = 0; t < ms; t++)
            {
                sum++;
            }
        }
    }
}

