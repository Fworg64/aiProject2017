#ifndef THEPLAYER_H
#define THEPLAYER_H

#include <ourposition.h>
#include <commands.h>
#include <vector>

class theplayer {
    public:
        ourposition myPOS;
        commands go2waypoint(double,double);
        double getangleofline(double, double);
        std::vector<double> getpathvector(std::vector<std::vector<double> >, std::vector<double>); //obstacles, goal
    public:
         theplayer(ourposition*);
         commands eval(ourposition*,double*, double, double);
         //wants playerx, y, w, ballx, bally
         //returns motor command
};

#endif
