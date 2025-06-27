#include "utility.hpp"
#include "logger.hpp"

void Logger::printStepGuide(int step)
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
    else if (step == BrakeSystem_Q)
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

bool Logger::IsExitAfterClearEnter(char* buf)
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

bool Logger::isNotNumber(char* checkNumber)
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

bool Logger::isInvalidNumberByStep(int& step, int number)
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

bool Logger::isInvalidNumberForStepCarType(int step, int number)
{
    return step == CarType_Q && !(number >= SEDAN && number <= TRUCK);
}

bool Logger::isInvalidNumberForStepEngine(int step, int number)
{
    return step == Engine_Q && !(number >= BACK_NUMBER && number <= INVALID_E);
}

bool Logger::isInvalidNumberForStepBrakeSystem(int step, int number)
{
    return step == BrakeSystem_Q && !(number >= BACK_NUMBER && number <= BOSCH_B);
}

bool Logger::isInvalidNumberForStepSteeringSystem(int step, int number)
{
    return step == SteeringSystem_Q && !(number >= BACK_NUMBER && number <= MOBIS);
}

bool Logger::isInvalidNumberForStepRunTest(int step, int number)
{
    return step == Run_Test && !(number >= BACK_NUMBER && number <= STEP_TEST);
}

void Logger::delay(int ms)
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
