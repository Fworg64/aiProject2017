#include <theplayer.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

# define PI           3.14159265358979323846

commands theplayer::go2waypoint(double x, double y)
{

     //orient robot towards ball

    //float alpha = acos((myPOS.x-x)/pow (pow(myPOS.x-x,2)+pow(myPOS.y-y,2),0.5));
   /* 
	double alpha;
	double dx = x - myPOS.x;
	double dy = y - myPOS.y;

	 float d_e = sqrt(dx * dx + dy * dy);
	 if (dx == 0 && dy == 0)
	 alpha = 90;
	 else
	 alpha = (int)(180. / PI *
	 atan2((double)(dy), (double)(dx)));
	 //theta_e = alpha - (int)myPOS.w;

 	// = atan2((y - myPOS.y), (x - myPOS.x));
	printf("player x = %f ball x = %f alpha :%f omega = %f\n", myPOS.x, x, alpha, myPOS.w);
	if (d_e > 1)
{
        if (abs(alpha - myPOS.w) > 10) 
	{
		if (alpha > myPOS.w) return GOLEFT;	
		else return GORGHT;
	}
	else return GOFWD;
}

 */
            double dx = x - myPOS.x;
            double dy = y - myPOS.y;

            double lAngle = atan2(dy, dx);

            lAngle = abs(lAngle * 180 / PI);

            if ((dx >= 0) && (dy >= 0)) { lAngle = 360 - lAngle; }
            if ((dx < 0) && (dy >= 0)) { lAngle = 270 - (lAngle - 90); }
	
                      
           // return abs(lAngle);     

		return GOFWD;     
        

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
