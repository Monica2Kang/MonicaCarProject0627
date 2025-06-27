#ifdef _DEBUG

#include "gmock/gmock.h"

int main()
{
    testing::InitGoogleMock();
    return RUN_ALL_TESTS();
}

#else

#include "logger.hpp"
#include "printer.hpp"
#include "producer.hpp"
#include "utility.hpp"

int main()
{
    char inputBuf[100];
    int step = CarType_Q;
    Logger log;
    Producer proCar;

    while (1)
    {
        log.printStepGuide(step);

        printf("INPUT > ");
        fgets(inputBuf, sizeof(inputBuf), stdin);
        if (log.IsExitAfterClearEnter(inputBuf)) break;

        // ���ڷ� �� ������� Ȯ��
        char* inputNumber;
        int selectNumber = strtol(inputBuf, &inputNumber, 10); // ���ڿ��� 10������ ��ȯ

        if (log.isNotNumber(inputNumber)) continue;
        if (log.isInvalidNumberByStep(step, selectNumber)) continue;
        step = proCar.makeProducedCar(step, selectNumber);
    }
}
#endif