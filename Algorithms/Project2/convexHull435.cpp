// You need to complete this program for your second project.

// Standard libraries
#include <string>
#include "convexHull435.hpp"
#include "JarvisMarch.hpp"
#include "GrahamScan.hpp"

int main(int argc, char *argv[])
{
    if (argc < 3)
        std::cout << "wrong format! should be \"a.exe algType dataFile\"";
    else
    {
        std::string algType = argv[1];
        std::string dataFilename = argv[2];
        std::string outputFile = "";
        std::ifstream dataFile;
        dataFile.open(dataFilename);
        //read your data points from dataFile (see class example for the format)

        switch(algType[0])
        {
            case 'G':
            {
                //call your Graham Scan algorithm to solve the problem

                Graham grahamHull;
                Point tmp;
                std::vector<Point> points;
                int n=0, x=0, y=0;

                while(dataFile >> tmp.x >> tmp.y)
                {
                    points.push_back(tmp);
                    ++n;
                }

                outputFile = "hull_G_" + dataFilename;
                std::ofstream hullFile(outputFile);
                grahamHull.convexHull(points, n, hullFile);
                hullFile.close();
                break;
            }

            case 'J':
                {
                    //call your Javis March algorithm to solve the problem
                    Jarvis jarvisHull;
                    Point tmp;
                    std::vector<Point> points;
                    int n=0, x=0, y=0;

                    while(dataFile >> tmp.x >> tmp.y)
                    {
                        points.push_back(tmp);
                        ++n;
                    }

                    outputFile = "hull_J_" + dataFilename;
                    std::ofstream hullFile(outputFile);
                    jarvisHull.convexHull(points, n, hullFile);
                    hullFile.close();
                    break;
                }
            case 'Q':
                //call your Quickhull algorithm to solve the problem

                outputFile = "hull_Q.txt";
                break;
            default:
                //any other parameter is called
                std::cout << "You done messed up AA Ron!" << std::endl;
                break;
        }

        //write your convex hull to the outputFile (see class example for the format)
        //you should be able to visulize your convex hull using the "ConvexHull_GUI" program.
        dataFile.close();
    }

    return 0;
}
