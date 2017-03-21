#ifndef THEPLAYER_H
#define THEPLAYER_H

#include <ourposition.h>
#include <commands.h>

class theplayer {
    private:
        ourposition myPOS;
        commands go2waypoint(double,double);
    public:
         theplayer(ourposition*);
         commands eval(ourposition*, double, double);
         //wants playerx, y, w, ballx, bally
         //returns motor command
};

#endif
