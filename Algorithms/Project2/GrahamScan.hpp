#ifndef GRAHAMSCAN_HPP_INCLUDED
#define GRAHAMSCAN_HPP_INCLUDED

#include "convexHull435.hpp"

class Graham
{
    public:
        //find orientation of ordered triplet
        int orientation(Point p, Point q, Point r);

        void swap(Point &p1, Point &p2);

        int distSq(Point p1, Point p2);

        void convexHull(std::vector<Point> points, int n);

        //prints convex hull of a set of n points
        void convexHull(std::vector<Point> points, int n, std::ofstream &output);

        Point getP0() {return p0;};
    private:
        Point p0;
        Point nextToTop(std::stack<Point> &S)
        {
            Point p = S.top();
            S.pop();
            Point res = S.top();
            S.push(p);
            return res;
        }

};

#endif
