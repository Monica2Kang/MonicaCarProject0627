class Producer {
public:
	int makeProducedCar(int step, int number);
	void printSelectedCarType(int carType);
	void printSelectedEngine(int engine);
	void printSelectedBrakeSystem(int brakeSystem);
	void printSelectedSteeringSystem(int steeringSystem);
	void doRunTestProducedCar(int number);
	void runProducedCar();
	int isValidCheck();
	bool isInvalidCheckForCarSedan();
	bool isInvalidCheckForCarSUV();
	bool isInvalidCheckForCarTruckWithEngine();
	bool isInvalidCheckForCarTruckWithBrakeSystem();
	bool isInvalidCheckForSystemBosch();
	void testProducedCar();

	//int getCarType();
	//int getEngine();
	//int getBrakeSystem();
	//int getSteeringSystem();
	void setCarType(int carType);
	void setEngine(int engine);
	void setBrakeSystem(int brakeSystem);
	void setSteeringSystem(int steeringSystem);

private:
	void delay(int ms);
	//void selectProducedCar(int step, int number);
	
	int stack[10];
};