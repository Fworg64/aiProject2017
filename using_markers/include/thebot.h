
#ifndef THEBOT_H
#define THEBOT_H

#define GOFWD 1
#define GOBKWD 2
#define GOLEFT 3
#define GORGHT 4

class thebot {
	private:
	double x;
	double y;
	double w;
	public:
	thebot (double, double, double);
	void docmd(int);
	double getX();
	double getY();
	double getW();
};


#endif
