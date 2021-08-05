#ifndef JARVISMARCH_HPP_INCLUDED
#define JARVISMARCH_HPP_INCLUDED

#include "convexHull435.hpp"

class Jarvis
{
    public:
        //find orientation of ordered triplet
        int orientation(Point p, Point q, Point r);

        //prints convex hull of a set of n points
        void convexHull(std::vector<Point> points, int n, std::ofstream &output);

        //point structure


};

#endif
