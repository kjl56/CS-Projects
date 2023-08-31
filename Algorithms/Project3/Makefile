

.PHONY: all
all : seamCarving

seamCarving : seamCarving.o
	g++ seamCarving.o -o seamCarving

seamCarving.o : seamCarving.cc
	g++ -std=c++17 -c seamCarving.cc

.PHONY: clean
clean :
	@rm -f *.o seamCarving