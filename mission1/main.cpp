#ifdef _DEBUG

#include "gmock/gmock.h"

int main()
{
    testing::InitGoogleMock();
    return RUN_ALL_TESTS();
}

#else

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CLEAR_SCREEN "\033[H\033[2J"

int stack[10];

void printStepGuide(int step);
bool isNotNumber(char* checkNumber);
bool IsExitAfterClearEnter(char* buf);
bool isInvalidNumberByStep(int& step, int answer);
bool isInvalidNumberForStepCarType(int step, int number);
bool isInvalidNumberForStepEngine(int step, int number);
bool isInvalidNumberForStepBrakeSystem(int step, int number);
bool isInvalidNumberForStepSteeringSystem(int step, int number);
bool isInvalidNumberForStepRunTest(int step, int number);

int makeProducedCar(int step, int answer);
void printSelectedCarType(int answer);
void printSelectedEngine(int answer);
void printSelectedBrakeSystem(int answer);
void printSelectedSteeringSystem(int answer);

void doRunTestProducedCar(int answer);
void runProducedCar();
int isValidCheck();
bool isValidCheckForCarSedan();
bool isValidCheckForCarSUV();
bool isValidCheckForCarTruckWithEngine();
bool isValidCheckForCarTruckWithBrakeSystem();
bool isValidCheckForSystemBosch();
void printCurrentStackCarType();
void printCurrentStackEngine();
void printCurrentStackBrakeSystem();
void printCurrentStackSteeringSystem();
void testProducedCar();

void delay(int ms);

enum QuestionType
{
    CarType_Q,
    Engine_Q,
    brakeSystem_Q,
    SteeringSystem_Q,
    Run_Test,
};

enum RunTestStepType
{
    Run = 1,
    Test
};

enum CarType
{
    SEDAN = 1,
    SUV,
    TRUCK
};

enum Engine
{
    GM = 1,
    TOYOTA,
    WIA,
    INVALID_E
};

enum brakeSystem
{
    MANDO = 1,
    CONTINENTAL,
    BOSCH_B
};

enum SteeringSystem
{
    BOSCH_S = 1,
    MOBIS
};

void delay(int ms)
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

const int BACK_NUMBER = 0;

int main()
{
    char inputBuf[100];
    int step = CarType_Q;

    while (1)
    {
        printStepGuide(step);

        printf("INPUT > ");
        fgets(inputBuf, sizeof(inputBuf), stdin);
        if (IsExitAfterClearEnter(inputBuf)) break;

        // 숫자로 된 대답인지 확인
        char* inputNumber;
        int selectNumber = strtol(inputBuf, &inputNumber, 10); // 문자열을 10진수로 변환

        if (isNotNumber(inputNumber)) continue;
        if (isInvalidNumberByStep(step, selectNumber)) continue;
        step = makeProducedCar(step, selectNumber);
    }
}

void printStepGuide(int step)
{
    if (step == CarType_Q)
    {
        printf(CLEAR_SCREEN);

        printf("        ______________\n");
        printf("       /|            | \n");
        printf("  ____/_|_____________|____\n");
        printf(" |                      O  |\n");
        printf(" '-(@)----------------(@)--'\n");
        printf("===============================\n");
        printf("어떤 차량 타입을 선택할까요?\n");
        printf("1. Sedan\n");
        printf("2. SUV\n");
        printf("3. Truck\n");
    }
    else if (step == Engine_Q)
    {
        printf(CLEAR_SCREEN);
        printf("어떤 엔진을 탑재할까요?\n");
        printf("0. 뒤로가기\n");
        printf("1. GM\n");
        printf("2. TOYOTA\n");
        printf("3. WIA\n");
        printf("4. 고장난 엔진\n");
    }
    else if (step == brakeSystem_Q)
    {
        printf(CLEAR_SCREEN);
        printf("어떤 제동장치를 선택할까요?\n");
        printf("0. 뒤로가기\n");
        printf("1. MANDO\n");
        printf("2. CONTINENTAL\n");
        printf("3. BOSCH\n");
    }
    else if (step == SteeringSystem_Q)
    {
        printf(CLEAR_SCREEN);
        printf("어떤 조향장치를 선택할까요?\n");
        printf("0. 뒤로가기\n");
        printf("1. BOSCH\n");
        printf("2. MOBIS\n");
    }
    else if (step == Run_Test)
    {
        printf(CLEAR_SCREEN);
        printf("멋진 차량이 완성되었습니다.\n");
        printf("어떤 동작을 할까요?\n");
        printf("0. 처음 화면으로 돌아가기\n");
        printf("1. RUN\n");
        printf("2. Test\n");
    }
    printf("===============================\n");
}

bool IsExitAfterClearEnter(char* buf)
{
    // 엔터 개행문자 제거
    char* context = nullptr;
    strtok_s(buf, "\r", &context);
    strtok_s(buf, "\n", &context);

    if (!strcmp(buf, "exit"))
    {
        printf("바이바이\n");
        return true;
    }
    return false;
}

bool isNotNumber(char* checkNumber)
{
    // 입력받은 문자가 숫자가 아니라면
    if (*checkNumber != '\0')
    {
        printf("ERROR :: 숫자만 입력 가능\n");
        delay(800);
        return true;
    }
    return false;
}

bool isInvalidNumberByStep(int& step, int number)
{
    if (isInvalidNumberForStepCarType(step, number))
    {
        printf("ERROR :: 차량 타입은 1 ~ 3 범위만 선택 가능\n");
        delay(800);
        return true;
    }

    if (isInvalidNumberForStepEngine(step, number))
    {
        printf("ERROR :: 엔진은 1 ~ 4 범위만 선택 가능\n");
        delay(800);
        return true;
    }

    if (isInvalidNumberForStepBrakeSystem(step, number))
    {
        printf("ERROR :: 제동장치는 1 ~ 3 범위만 선택 가능\n");
        delay(800);
        return true;
    }

    if (isInvalidNumberForStepSteeringSystem(step, number))
    {
        printf("ERROR :: 조향장치는 1 ~ 2 범위만 선택 가능\n");
        delay(800);
        return true;
    }

    if (isInvalidNumberForStepRunTest(step, number))
    {
        printf("ERROR :: Run 또는 Test 중 하나를 선택 필요\n");
        delay(800);
        return true;
    }

    // 처음으로 돌아가기
    if (number == BACK_NUMBER && step == Run_Test)
    {
        step = CarType_Q;
        return true;
    }

    // 이전으로 돌아가기
    if (number == BACK_NUMBER && step >= Engine_Q)
    {
        step -= 1;
        return true;
    }
    return false;
}

bool isInvalidNumberForStepCarType(int step, int number)
{
    return step == CarType_Q && !(number >= SEDAN && number <= TRUCK);
}

bool isInvalidNumberForStepEngine(int step, int number)
{
    return step == Engine_Q && !(number >= BACK_NUMBER && number <= INVALID_E);
}

bool isInvalidNumberForStepBrakeSystem(int step, int number)
{
    return step == brakeSystem_Q && !(number >= BACK_NUMBER && number <= BOSCH_B);
}

bool isInvalidNumberForStepSteeringSystem(int step, int number)
{
    return step == SteeringSystem_Q && !(number >= BACK_NUMBER && number <= MOBIS);
}

bool isInvalidNumberForStepRunTest(int step, int number)
{
    return step == Run_Test && !(number >= BACK_NUMBER && number <= Test);
}

int makeProducedCar(int step, int number)
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
        return brakeSystem_Q;
    }
    else if (step == brakeSystem_Q)
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

    doRunTestProducedCar(number);
    return Run_Test;
}

void printSelectedCarType(int carType)
{
    stack[CarType_Q] = carType;
    if (carType == SEDAN)
        printf("차량 타입으로 Sedan을 선택하셨습니다.\n");
    if (carType == SUV)
        printf("차량 타입으로 SUV을 선택하셨습니다.\n");
    if (carType == TRUCK)
        printf("차량 타입으로 Truck을 선택하셨습니다.\n");
}

void printSelectedEngine(int engine)
{
    stack[Engine_Q] = engine;
    if (engine == GM)
        printf("GM 엔진을 선택하셨습니다.\n");
    if (engine == TOYOTA)
        printf("TOYOTA 엔진을 선택하셨습니다.\n");
    if (engine == WIA)
        printf("WIA 엔진을 선택하셨습니다.\n");
}

void printSelectedBrakeSystem(int brakeSystem)
{
    stack[brakeSystem_Q] = brakeSystem;
    if (brakeSystem == MANDO)
        printf("MANDO 제동장치를 선택하셨습니다.\n");
    if (brakeSystem == CONTINENTAL)
        printf("CONTINENTAL 제동장치를 선택하셨습니다.\n");
    if (brakeSystem == BOSCH_B)
        printf("BOSCH 제동장치를 선택하셨습니다.\n");
}

void printSelectedSteeringSystem(int steeringSystem)
{
    stack[SteeringSystem_Q] = steeringSystem;
    if (steeringSystem == BOSCH_S)
        printf("BOSCH 조향장치를 선택하셨습니다.\n");
    if (steeringSystem == MOBIS)
        printf("MOBIS 조향장치를 선택하셨습니다.\n");
}

void doRunTestProducedCar(int number)
{
    if (number == Run)
    {
        runProducedCar();
        delay(2000);
    }
    else if (number == Test)
    {
        printf("Test...\n");
        delay(1500);
        testProducedCar();
        delay(2000);
    }
}

void runProducedCar()
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

    printCurrentStackCarType();
    printCurrentStackEngine();
    printCurrentStackBrakeSystem();
    printCurrentStackSteeringSystem();
    printf("자동차가 동작됩니다.\n");
}

int isValidCheck()
{
    if (isValidCheckForCarSedan()) return false;
    else if (isValidCheckForCarSUV()) return false;
    else if (isValidCheckForCarTruckWithEngine()) return false;
    else if (isValidCheckForCarTruckWithBrakeSystem()) return false;
    else if (isValidCheckForSystemBosch()) return false;
    return true;
}

bool isValidCheckForCarSedan()
{
    return stack[CarType_Q] == SEDAN && stack[brakeSystem_Q] == CONTINENTAL;
}

bool isValidCheckForCarSUV()
{
    return stack[CarType_Q] == SUV && stack[Engine_Q] == TOYOTA;
}

bool isValidCheckForCarTruckWithEngine()
{
    return stack[CarType_Q] == TRUCK && stack[Engine_Q] == WIA;
}

bool isValidCheckForCarTruckWithBrakeSystem()
{
    return stack[CarType_Q] == TRUCK && stack[brakeSystem_Q] == MANDO;
}

bool isValidCheckForSystemBosch()
{
    return stack[brakeSystem_Q] == BOSCH_B && stack[SteeringSystem_Q] != BOSCH_S;
}

void printCurrentStackCarType()
{
    if (stack[CarType_Q] == SEDAN)
        printf("Car Type : Sedan\n");
    if (stack[CarType_Q] == SUV)
        printf("Car Type : SUV\n");
    if (stack[CarType_Q] == TRUCK)
        printf("Car Type : Truck\n");
}

void printCurrentStackEngine()
{
    if (stack[Engine_Q] == GM)
        printf("Engine : GM\n");
    if (stack[Engine_Q] == TOYOTA)
        printf("Engine : TOYOTA\n");
    if (stack[Engine_Q] == WIA)
        printf("Engine : WIA\n");
}

void printCurrentStackBrakeSystem()
{

    if (stack[brakeSystem_Q] == MANDO)
        printf("Brake System : Mando");
    if (stack[brakeSystem_Q] == CONTINENTAL)
        printf("Brake System : Continental\n");
    if (stack[brakeSystem_Q] == BOSCH_B)
        printf("Brake System : Bosch\n");
}

void printCurrentStackSteeringSystem()
{
    if (stack[SteeringSystem_Q] == BOSCH_S)
        printf("SteeringSystem : Bosch\n");
    if (stack[SteeringSystem_Q] == MOBIS)
        printf("SteeringSystem : Mobis\n");
}

void testProducedCar()
{
    const char* FAIL = "자동차 부품 조합 테스트 결과 : FAIL\n";
    const char* PASS = "자동차 부품 조합 테스트 결과 : PASS\n";

    if (isValidCheckForCarSedan())
    {
        printf("%s", FAIL);
        printf("Sedan에는 Continental제동장치 사용 불가\n");
    }
    else if (isValidCheckForCarSUV())
    {
        printf("%s", FAIL);
        printf("SUV에는 TOYOTA엔진 사용 불가\n");
    }
    else if (isValidCheckForCarTruckWithEngine())
    {
        printf("%s", FAIL);
        printf("Truck에는 WIA엔진 사용 불가\n");
    }
    else if (isValidCheckForCarTruckWithBrakeSystem())
    {
        printf("%s", FAIL);
        printf("Truck에는 Mando제동장치 사용 불가\n");
    }
    else if (isValidCheckForSystemBosch())
    {
        printf("%s", FAIL);
        printf("Bosch제동장치에는 Bosch조향장치 이외 사용 불가\n");
    }
    else
    {
        printf("%s", PASS);
    }
}

#endif
