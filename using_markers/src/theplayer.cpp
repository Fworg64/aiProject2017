#include <theplayer.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

commands theplayer::go2waypoint(double x, double y)
{

     //orient robot towards ball

    //float alpha = acos((myPOS.x-x)/pow (pow(myPOS.x-x,2)+pow(myPOS.y-y,2),0.5));
    
 double alpha = atan2((y - myPOS.y), (x - myPOS.x));
	printf("player x = %f ball x = %f alpha :%f omega = %f\n", myPOS.x, x, alpha, myPOS.w);
        if (abs(alpha - myPOS.w) > .5) 
	{
		if (alpha > myPOS.w) return GOLEFT;
		else return GORGHT;
	}
	else return GOFWD;

   // if (myPOS.x < x +.4 ) //waypoint is to the right
   /*{
        double alpha = atan2((myPOS.y -y), (myPOS.x -x));
	printf("player x = %f ball x = %f alpha :%f omega = %f\n", myPOS.x, x, alpha, myPOS.w);
        if (alpha > myPOS.w+.4) return GORGHT; 
        else if (alpha < myPOS.w-.4) return GOLEFT;
        else return GOFWD;
     }
   else if (myPOS.x > x -.4) //waypoint is to the left
    {
        double alpha = -atan((myPOS.x -x)/(myPOS.y -y));
	printf("player x = %f ball x = %f alpha :%f omega = %f\n", myPOS.x, x, alpha, myPOS.w);
        if (alpha > myPOS.w +.4) return GOLEFT;
        else if (alpha < myPOS.w -.4) return GORGHT;
        else return GOFWD;
    }*/
    //else return GOFWD;

    //if (alpha> myPOS.w + .1) return GOLEFT;
   // else if (alpha < myPOS.w -.1) return GORGHT;
    ///else return GOFWD;

    //go towards ball
}

commands theplayer::eval(ourposition* position1, double ballx, double bally)
{
	myPOS = *position1;
    	return go2waypoint(ballx, bally);

}

theplayer::theplayer(ourposition* thePOS)
{
    myPOS = *thePOS;
}
