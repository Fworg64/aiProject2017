
#ifndef THEBALL_H
#define THEBALL_H

#define FRICTION .7

class theball {
	private:
	double x;
	double y;
	double xv;
	double yv;
	public:
	theball(double, double);
	double getX();
	double getY();
	void kick(double, double);
	void eval();
};


#endif
