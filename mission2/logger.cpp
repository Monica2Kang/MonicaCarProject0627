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
        printf("� ���� Ÿ���� �����ұ��?\n");
        printf("1. Sedan\n");
        printf("2. SUV\n");
        printf("3. Truck\n");
    }
    else if (step == Engine_Q)
    {
        printf(CLEAR_SCREEN);
        printf("� ������ ž���ұ��?\n");
        printf("0. �ڷΰ���\n");
        printf("1. GM\n");
        printf("2. TOYOTA\n");
        printf("3. WIA\n");
        printf("4. ���峭 ����\n");
    }
    else if (step == BrakeSystem_Q)
    {
        printf(CLEAR_SCREEN);
        printf("� ������ġ�� �����ұ��?\n");
        printf("0. �ڷΰ���\n");
        printf("1. MANDO\n");
        printf("2. CONTINENTAL\n");
        printf("3. BOSCH\n");
    }
    else if (step == SteeringSystem_Q)
    {
        printf(CLEAR_SCREEN);
        printf("� ������ġ�� �����ұ��?\n");
        printf("0. �ڷΰ���\n");
        printf("1. BOSCH\n");
        printf("2. MOBIS\n");
    }
    else if (step == Run_Test)
    {
        printf(CLEAR_SCREEN);
        printf("���� ������ �ϼ��Ǿ����ϴ�.\n");
        printf("� ������ �ұ��?\n");
        printf("0. ó�� ȭ������ ���ư���\n");
        printf("1. RUN\n");
        printf("2. Test\n");
    }
    printf("===============================\n");
}

bool Logger::IsExitAfterClearEnter(char* buf)
{
    // ���� ���๮�� ����
    char* context = nullptr;
    strtok_s(buf, "\r", &context);
    strtok_s(buf, "\n", &context);

    if (!strcmp(buf, "exit"))
    {
        printf("���̹���\n");
        return true;
    }
    return false;
}

bool Logger::isNotNumber(char* checkNumber)
{
    // �Է¹��� ���ڰ� ���ڰ� �ƴ϶��
    if (*checkNumber != '\0')
    {
        printf("ERROR :: ���ڸ� �Է� ����\n");
        delay(800);
        return true;
    }
    return false;
}

bool Logger::isInvalidNumberByStep(int& step, int number)
{
    if (isInvalidNumberForStepCarType(step, number))
    {
        printf("ERROR :: ���� Ÿ���� 1 ~ 3 ������ ���� ����\n");
        delay(800);
        return true;
    }

    if (isInvalidNumberForStepEngine(step, number))
    {
        printf("ERROR :: ������ 1 ~ 4 ������ ���� ����\n");
        delay(800);
        return true;
    }

    if (isInvalidNumberForStepBrakeSystem(step, number))
    {
        printf("ERROR :: ������ġ�� 1 ~ 3 ������ ���� ����\n");
        delay(800);
        return true;
    }

    if (isInvalidNumberForStepSteeringSystem(step, number))
    {
        printf("ERROR :: ������ġ�� 1 ~ 2 ������ ���� ����\n");
        delay(800);
        return true;
    }

    if (isInvalidNumberForStepRunTest(step, number))
    {
        printf("ERROR :: Run �Ǵ� Test �� �ϳ��� ���� �ʿ�\n");
        delay(800);
        return true;
    }

    // ó������ ���ư���
    if (number == BACK_NUMBER && step == Run_Test)
    {
        step = CarType_Q;
        return true;
    }

    // �������� ���ư���
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
