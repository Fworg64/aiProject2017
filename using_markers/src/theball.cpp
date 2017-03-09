#include <theball.h>

theball::theball(double x1, double y1)
{
    x = x1;
    y = y1;
}

double theball::getX() {return x;}
double theball::getY() {return y;}

void theball::kick(double xin, double yin)
{
    yv += yin;
    xv +=xin;
}

void theball::eval()
{
	x +=xv;
	y +=yv;
	yv*=FRICTION;
	xv*=FRICTION;
	if (yv<.1) yv=0;
	if (xv<.1) xv=0;
}
