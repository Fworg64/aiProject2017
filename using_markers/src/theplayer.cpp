#include <theplayer.h>
#include <math.h>

commands theplayer::go2waypoint(double x, double y)
{

     //orient robot towards ball

    //float alpha = acos((myPOS.x-x)/pow (pow(myPOS.x-x,2)+pow(myPOS.y-y,2),0.5));
    
    if (myPOS.x < x +.1 ) //waypoint is to the right
    {
        float alpha = atan((myPOS.x -x)/(myPOS.y -y));
        if (alpha > myPOS.w+.1) return GOLEFT; 
        else if (alpha < myPOS.w-.1) return GORGHT;
        else return GOFWD;
    }
    else if (myPOS.x > x -.1) //waypoint is to the left
    {
        float alpha = -atan((myPOS.x -x)/(myPOS.y -y));
        if (alpha > myPOS.w +.1) return GORGHT;
        else if (alpha < myPOS.w +.1) return GOLEFT;
        else return GOFWD;
    }
    else return GOFWD;

    //if (alpha> myPOS.w + .1) return GOLEFT;
   // else if (alpha < myPOS.w -.1) return GORGHT;
    ///else return GOFWD;

    //go towards ball
}

commands theplayer::eval(ourposition*, double ballx, double bally)
{
    return go2waypoint(ballx, bally);
}

theplayer::theplayer(ourposition* thePOS)
{
    myPOS = *thePOS;
}
