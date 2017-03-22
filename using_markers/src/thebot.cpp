#include <thebot.h>
#include <math.h>

thebot::thebot(ourposition* thePOS)
{
	myPOS = *thePOS;
}
	//todo, cache x,y directional vector upon turn ot avoid its calculation everytime

void thebot::docmd(commands cmd)
{
	switch(cmd)
	{
		case GOFWD:
			myPOS.x+= cos(myPOS.w);
			myPOS.y+= sin(myPOS.w);
		break;
		case GOBKWD:
			myPOS.x-= cos(myPOS.w);
			myPOS.y-= sin(myPOS.w);
		break;
		case GOLEFT:
			myPOS.w+=0.02;
                        //if (myPOS.w >3.14) myPOS.w =-3.14;
		break;
		case GORGHT:
			myPOS.w-=0.02;
                        //if (myPOS.w < -3.14) myPOS.w = 3.14;
		break;
	}
}

double thebot::getX() {return myPOS.x;}
double thebot::getY() {return myPOS.y;}
double thebot::getW() {return myPOS.w;}
ourposition* thebot::getPOS() {return &myPOS;}
