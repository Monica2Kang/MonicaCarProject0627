class Logger {
public:
	void printStepGuide(int step);
	bool IsExitAfterClearEnter(char* buf);
	bool isNotNumber(char* checkNumber);
	bool isInvalidNumberByStep(int& step, int answer);
	bool isInvalidNumberForStepCarType(int step, int number);
	bool isInvalidNumberForStepEngine(int step, int number);
	bool isInvalidNumberForStepBrakeSystem(int step, int number);
	bool isInvalidNumberForStepSteeringSystem(int step, int number);
	bool isInvalidNumberForStepRunTest(int step, int number);

private:
	void delay(int ms);
	const int BACK_NUMBER = 0;
};