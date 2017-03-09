#include <thebot.h>
#include <math.h>

thebot::thebot(double x1, double y1, double w1)
{
	x =x1;
	y =y1;
	w =w1;
}
	//todo, cache x,y directional vector upon turn ot avoid its calculation everytime

void thebot::docmd(int cmd)
{
	switch(cmd)
	{
		case GOFWD:
			x+= cos(w);
			y+= sin(w);
		break;
		case GOBKWD:
			x-= cos(w);
			y-= sin(w);
		break;
		case GOLEFT:
			w+=.1;
		break;
		case GORGHT:
			w-=.1;
		break;
	}
}

double thebot::getX() {return x;}
double thebot::getY() {return y;}
double thebot::getW() {return w;}
