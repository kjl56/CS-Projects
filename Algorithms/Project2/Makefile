

.PHONY: all
all : convexHull435

convexHull435 : convexHull435.o JarvisMarch.o GrahamScan.o
	g++ JarvisMarch.o convexHull435.o GrahamScan.o -o convexHull435

convexHull435.o : convexHull435.cpp JarvisMarch.hpp GrahamScan.hpp convexHull435.hpp
	g++ -std=c++17 -c convexHull435.cpp

GrahamScan.o : GrahamScan.cpp
	g++ -std=c++11 -c GrahamScan.cpp

JarvisMarch.o : JarvisMarch.cpp
	g++ -std=c++17 -c JarvisMarch.cpp

QuickHull.o : QuickHull.cpp
	g++ -std=c++17 -c QuickHull.cpp


.PHONY: clean
clean :
	@rm -f *.o convexHull435 hull_G* hull_J* hull_Q*
	@rm -f *10*.txt

#generates all hull_J_*.txt files with Jarvis March.
.PHONY: runJ
runJ : convexHull435
	time -o output/test_J_rectangle10.txt -f "Program: %C\nTotal time: %E\n" ./convexHull435 J rectangle10.txt
	time -o output/test_J_rectangle100.txt -f "Program: %C\nTotal time: %E\n" ./convexHull435 J rectangle100.txt
	time -o output/test_J_rectangle1000.txt -f "Program: %C\nTotal time: %E\n" ./convexHull435 J rectangle1000.txt
	time -o output/test_J_rectangle10000.txt -f "Program: %C\nTotal time: %E\n" ./convexHull435 J rectangle10000.txt
	time -o output/test_J_rectangle100000.txt -f "Program: %C\nTotal time: %E\n" ./convexHull435 J rectangle100000.txt
	time -o output/test_J_rectangle1000000.txt -f "Program: %C\nTotal time: %E\n" ./convexHull435 J rectangle1000000.txt
	time -o output/test_J_circle10.txt -f "Program: %C\nTotal time: %E\n" ./convexHull435 J circle10.txt
	time -o output/test_J_circle100.txt -f "Program: %C\nTotal time: %E\n" ./convexHull435 J circle100.txt
	time -o output/test_J_circle1000.txt -f "Program: %C\nTotal time: %E\n" ./convexHull435 J circle1000.txt
	time -o output/test_J_circle10000.txt -f "Program: %C\nTotal time: %E\n" ./convexHull435 J circle10000.txt
	time -o output/test_J_circle100000.txt -f "Program: %C\nTotal time: %E\n" ./convexHull435 J circle100000.txt
	time -o output/test_J_circle1000000.txt -f "Program: %C\nTotal time: %E\n" ./convexHull435 J circle1000000.txt
	time -o output/test_J_onCircle10.txt -f "Program: %C\nTotal time: %E\n" ./convexHull435 J onCircle10.txt
	time -o output/test_J_onCircle100.txt -f "Program: %C\nTotal time: %E\n" ./convexHull435 J onCircle100.txt
	time -o output/test_J_onCircle1000.txt -f "Program: %C\nTotal time: %E\n" ./convexHull435 J onCircle1000.txt
	time -o output/test_J_onCircle10000.txt -f "Program: %C\nTotal time: %E\n" ./convexHull435 J onCircle10000.txt
	time -o output/test_J_onCircle100000.txt -f "Program: %C\nTotal time: %E\n" ./convexHull435 J onCircle100000.txt
	time -o output/test_J_onCircle1000000.txt -f "Program: %C\nTotal time: %E\n" ./convexHull435 J onCircle1000000.txt
	time -o output/test_J_triangle10.txt -f "Program: %C\nTotal time: %E\n" ./convexHull435 J triangle10.txt
	time -o output/test_J_triangle100.txt -f "Program: %C\nTotal time: %E\n" ./convexHull435 J triangle100.txt
	time -o output/test_J_triangle1000.txt -f "Program: %C\nTotal time: %E\n" ./convexHull435 J triangle1000.txt
	time -o output/test_J_triangle10000.txt -f "Program: %C\nTotal time: %E\n" ./convexHull435 J triangle10000.txt
	time -o output/test_J_triangle100000.txt -f "Program: %C\nTotal time: %E\n" ./convexHull435 J triangle100000.txt
	time -o output/test_J_triangle1000000.txt -f "Program: %C\nTotal time: %E\n" ./convexHull435 J triangle1000000.txt

#generates all hull_J_*.txt files with Jarvis March.
.PHONY: runG
runG : convexHull435
	time -o output/test_G_rectangle10.txt -f "Program: %C\nTotal time: %E\n" ./convexHull435 G rectangle10.txt
	time -o output/test_G_rectangle100.txt -f "Program: %C\nTotal time: %E\n" ./convexHull435 G rectangle100.txt
	time -o output/test_G_rectangle1000.txt -f "Program: %C\nTotal time: %E\n" ./convexHull435 G rectangle1000.txt
	time -o output/test_G_rectangle10000.txt -f "Program: %C\nTotal time: %E\n" ./convexHull435 G rectangle10000.txt
	time -o output/test_G_rectangle100000.txt -f "Program: %C\nTotal time: %E\n" ./convexHull435 G rectangle100000.txt
	time -o output/test_G_rectangle1000000.txt -f "Program: %C\nTotal time: %E\n" ./convexHull435 G rectangle1000000.txt
	time -o output/test_G_circle10.txt -f "Program: %C\nTotal time: %E\n" ./convexHull435 G circle10.txt
	time -o output/test_G_circle100.txt -f "Program: %C\nTotal time: %E\n" ./convexHull435 G circle100.txt
	time -o output/test_G_circle1000.txt -f "Program: %C\nTotal time: %E\n" ./convexHull435 G circle1000.txt
	time -o output/test_G_circle10000.txt -f "Program: %C\nTotal time: %E\n" ./convexHull435 G circle10000.txt
	time -o output/test_G_circle100000.txt -f "Program: %C\nTotal time: %E\n" ./convexHull435 G circle100000.txt
	time -o output/test_G_circle1000000.txt -f "Program: %C\nTotal time: %E\n" ./convexHull435 G circle1000000.txt
	time -o output/test_G_onCircle10.txt -f "Program: %C\nTotal time: %E\n" ./convexHull435 G onCircle10.txt
	time -o output/test_G_onCircle100.txt -f "Program: %C\nTotal time: %E\n" ./convexHull435 G onCircle100.txt
	time -o output/test_G_onCircle1000.txt -f "Program: %C\nTotal time: %E\n" ./convexHull435 G onCircle1000.txt
	time -o output/test_G_onCircle10000.txt -f "Program: %C\nTotal time: %E\n" ./convexHull435 G onCircle10000.txt
	time -o output/test_G_onCircle100000.txt -f "Program: %C\nTotal time: %E\n" ./convexHull435 G onCircle100000.txt
	time -o output/test_G_onCircle1000000.txt -f "Program: %C\nTotal time: %E\n" ./convexHull435 G onCircle1000000.txt
	time -o output/test_G_triangle10.txt -f "Program: %C\nTotal time: %E\n" ./convexHull435 G triangle10.txt
	time -o output/test_G_triangle100.txt -f "Program: %C\nTotal time: %E\n" ./convexHull435 G triangle100.txt
	time -o output/test_G_triangle1000.txt -f "Program: %C\nTotal time: %E\n" ./convexHull435 G triangle1000.txt
	time -o output/test_G_triangle10000.txt -f "Program: %C\nTotal time: %E\n" ./convexHull435 G triangle10000.txt
	time -o output/test_G_triangle100000.txt -f "Program: %C\nTotal time: %E\n" ./convexHull435 G triangle100000.txt
	time -o output/test_G_triangle1000000.txt -f "Program: %C\nTotal time: %E\n" ./convexHull435 G triangle1000000.txt

#.PHONY: all
#all : convexHull435

#convexHull435 : convexHull435.o Graham.o Jarvis.o ConvexHull.o
#g++ convexHull435.o Graham.o Jarvis.o ConvexHull.o -o convexHull435

#convexHull435.o : convexHull435.cc Graham.hpp Jarvis.hpp ConvexHull.hpp
#g++ -std=c++11 -c convexHull435.cc

#Graham.o : Graham.cpp
#g++ -std=c++11 -c Graham.cpp

#Jarvis.o : Jarvis.cpp
#g++ -std=c++11 -c Jarvis.cpp

#ConvexHull.o : ConvexHull.cpp
#g++ -std=c++11 -c ConvexHull.cpp

#.PHONY: clean
#clean :
#@rm -f *.o convexHull435 hull_G.txt hull_J.txt hull_Q.txt
