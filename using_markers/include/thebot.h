
#ifndef THEBOT_H
#define THEBOT_H

#include <ourposition.h>
#include <commands.h>

class thebot {
	private:
	ourposition myPOS;
	public:
	thebot (ourposition*);
	void docmd(commands);
        ourposition* getPOS();
        double getX();
        double getY();
        double getW();
};


#endif
