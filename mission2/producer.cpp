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
        printf("���� Ÿ������ Sedan�� �����ϼ̽��ϴ�.\n");
    if (carType == SUV)
        printf("���� Ÿ������ SUV�� �����ϼ̽��ϴ�.\n");
    if (carType == TRUCK)
        printf("���� Ÿ������ Truck�� �����ϼ̽��ϴ�.\n");
}

void Producer::printSelectedEngine(int engine)
{
    stack[Engine_Q] = engine;
    if (engine == GM)
        printf("GM ������ �����ϼ̽��ϴ�.\n");
    if (engine == TOYOTA)
        printf("TOYOTA ������ �����ϼ̽��ϴ�.\n");
    if (engine == WIA)
        printf("WIA ������ �����ϼ̽��ϴ�.\n");
}

void Producer::printSelectedBrakeSystem(int brakeSystem)
{
    stack[BrakeSystem_Q] = brakeSystem;
    if (brakeSystem == MANDO)
        printf("MANDO ������ġ�� �����ϼ̽��ϴ�.\n");
    if (brakeSystem == CONTINENTAL)
        printf("CONTINENTAL ������ġ�� �����ϼ̽��ϴ�.\n");
    if (brakeSystem == BOSCH_B)
        printf("BOSCH ������ġ�� �����ϼ̽��ϴ�.\n");
}

void Producer::printSelectedSteeringSystem(int steeringSystem)
{
    stack[SteeringSystem_Q] = steeringSystem;
    if (steeringSystem == BOSCH_S)
        printf("BOSCH ������ġ�� �����ϼ̽��ϴ�.\n");
    if (steeringSystem == MOBIS)
        printf("MOBIS ������ġ�� �����ϼ̽��ϴ�.\n");
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
        printf("�ڵ����� ���۵��� �ʽ��ϴ�\n");
        return;
    }

    if (stack[Engine_Q] == INVALID_E)
    {
        printf("������ ���峪�ֽ��ϴ�.\n");
        printf("�ڵ����� �������� �ʽ��ϴ�.\n");
        return;
    }

    Printer print = Printer::GetInstance();
    print.printCurrentStackCarType(stack[CarType_Q]);
    print.printCurrentStackEngine(stack[Engine_Q]);
    print.printCurrentStackBrakeSystem(stack[BrakeSystem_Q]);
    print.printCurrentStackSteeringSystem(stack[SteeringSystem_Q]);
    printf("�ڵ����� ���۵˴ϴ�.\n");
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
    const char* FAIL = "�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n";
    const char* PASS = "�ڵ��� ��ǰ ���� �׽�Ʈ ��� : PASS\n";

    if (isInvalidCheckForCarSedan())
    {
        printf("%s", FAIL);
        printf("Sedan���� Continental������ġ ��� �Ұ�\n");
    }
    else if (isInvalidCheckForCarSUV())
    {
        printf("%s", FAIL);
        printf("SUV���� TOYOTA���� ��� �Ұ�\n");
    }
    else if (isInvalidCheckForCarTruckWithEngine())
    {
        printf("%s", FAIL);
        printf("Truck���� WIA���� ��� �Ұ�\n");
    }
    else if (isInvalidCheckForCarTruckWithBrakeSystem())
    {
        printf("%s", FAIL);
        printf("Truck���� Mando������ġ ��� �Ұ�\n");
    }
    else if (isInvalidCheckForSystemBosch())
    {
        printf("%s", FAIL);
        printf("Bosch������ġ���� Bosch������ġ �̿� ��� �Ұ�\n");
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

