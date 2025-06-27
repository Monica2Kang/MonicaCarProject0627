#include "utility.hpp"
#include "printer.hpp"

void Printer::printCurrentStackCarType(int carType)
{
    //stack[CarType_Q]
    if (carType == SEDAN)
        printf("Car Type : Sedan\n");
    if (carType == SUV)
        printf("Car Type : SUV\n");
    if (carType == TRUCK)
        printf("Car Type : Truck\n");
}

void Printer::printCurrentStackEngine(int engine)
{
    //stack[Engine_Q]
    if (engine == GM)
        printf("Engine : GM\n");
    if (engine == TOYOTA)
        printf("Engine : TOYOTA\n");
    if (engine == WIA)
        printf("Engine : WIA\n");
}

void Printer::printCurrentStackBrakeSystem(int brakeSystem)
{
    //stack[brakeSystem_Q]
    if (brakeSystem == MANDO)
        printf("Brake System : Mando");
    if (brakeSystem == CONTINENTAL)
        printf("Brake System : Continental\n");
    if (brakeSystem == BOSCH_B)
        printf("Brake System : Bosch\n");
}

void Printer::printCurrentStackSteeringSystem(int steeringSystem)
{
    //stack[SteeringSystem_Q]
    if (steeringSystem == BOSCH_S)
        printf("SteeringSystem : Bosch\n");
    if (steeringSystem == MOBIS)
        printf("SteeringSystem : Mobis\n");
}
