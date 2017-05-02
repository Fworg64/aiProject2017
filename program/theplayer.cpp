#include <theplayer.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

# define PI           3.14159265358979323846
#define OBSTGAIN .05

double theplayer::getangleofline(double dx, double dy)
{
            double lAngle = atan2(dx, dy);

            //if ((dx >= 0) && (dy >= 0)) { lAngle = 360 - lAngle; }
            //if ((dx < 0) && (dy >= 0)) { lAngle = 270 - (lAngle - 90); }
            lAngle = lAngle * 180 / PI;
    
            return lAngle;
} 

std::vector<double> theplayer::getpathvector(std::vector<std::vector<double> > obstacles, std::vector<double> goal)
{
    std::vector<double> tempgoal(2);
    tempgoal.at(0) = goal.at(0) -myPOS.x ;
    tempgoal.at(1) = goal.at(1) - myPOS.y;

    printf("goal x: %f.4    goal y: %f.4\n", tempgoal.at(0), tempgoal.at(1));

    std::vector<std::vector<double> > tempobstacles(obstacles.size());

    double theta1 =0;
    double theta2=0;
    int unsigned index =0;
    for (index = 0; index<obstacles.size();index++)
    {
      theta1 =getangleofline(tempgoal.at(0), tempgoal.at(1));
      theta2 = getangleofline(obstacles.at(index).at(0) -myPOS.x,obstacles.at(index).at(1)-myPOS.y);
      
      tempobstacles.at(index).at(0) = obstacles.at(index).at(1) -myPOS.y;
      tempobstacles.at(index).at(1) = obstacles.at(index).at(0) - myPOS.x;
      double tempthing = tempobstacles.at(index).at(0)*tempobstacles.at(index).at(0) + tempobstacles.at(index).at(1)*tempobstacles.at(index).at(1);
      tempobstacles.at(index).at(0) = tempthing/tempobstacles.at(index).at(0);
      tempobstacles.at(index).at(1) = tempthing/tempobstacles.at(index).at(1);


      if(theta1 > theta2)
      {
           tempobstacles.at(index).at(0) = -tempobstacles.at(index).at(0);
      } 
      else
      {
           tempobstacles.at(index).at(1) = -tempobstacles.at(index).at(1);
      }

      printf("Obstacle%d x: %f.4, y: %f.4\n", index, tempobstacles.at(index).at(0), tempobstacles.at(index).at(1));

         
    }
    std::vector<double> garbage(2);
    return garbage;

}

commands theplayer::go2waypoint(double x, double y)
{

    double theta1 = getangleofline(x-myPOS.x, y-myPOS.y);

    if (myPOS.w > theta1 + 20) return GORGHT;
    else if (myPOS.w < theta1 -20) return GOLEFT;
    else return GOFWD;     
        

    //go towards ball
}

commands theplayer::eval(ourposition* position1, std::vector<std::vector<double> > obstacles, double ballx, double bally)
{
	myPOS = *position1;
    	return go2waypoint(ballx, bally);

}

theplayer::theplayer(ourposition* thePOS)
{
    myPOS = *thePOS;
}
