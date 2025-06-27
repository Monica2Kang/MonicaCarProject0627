class Printer {
public:
	static Printer& GetInstance() {
		static Printer Instance;
		return Instance;
	}
	void printCurrentStackCarType(int carType);
	void printCurrentStackEngine(int engine);
	void printCurrentStackBrakeSystem(int brakeSystem);
	void printCurrentStackSteeringSystem(int steeringSystem);

private:
	Printer() = default;
};
