// You need to complete this program for a part of your first project.

// Standard libraries
#include <string>
#include <iostream>
#include <stdlib.h> 
#include <fstream>
#include <time.h>

// 'BigIntegerLibrary.hh' includes all of the library headers.
#include "BigIntegerLibrary.hh"

//faster way to mod for testing FLT
//doesn't work for some reason :(
BigUnsigned quickExp(const BigUnsigned &base, const BigUnsigned &exponent, const BigUnsigned &modulus){
  //if (exponent == 1) return (base % modulus);
  if (exponent == 0) return 1;
  if (exponent % 2 == 0) return ((quickExp(base, exponent / 2, modulus) ^ 2) % modulus); //if exponent is even
  else return ((base * (quickExp(base, exponent / 2, modulus) ^ 2)) % modulus); //if exponent is odd 
}

//returns true if n is prime, false if else
bool flt(const BigUnsigned &n){
  //fermat's little theorem
  //if n is prime, then for all a, s.t. 1 <= a < n, a^(n-1) % n = 1
  //however, we're only testing 2 random a's
  for ( int i = 0; i < 2; i++){
    BigUnsigned a = BigUnsigned(rand()) % (n - 1) + 1;
    if ( modexp(a, (n - 1), n) != 1 ){
      //if ANY mod is not 1
      return false;
    }
  }
  //if ALL mods return 1
  return true;
}

int main(){
	/* The library throws 'const char *' error messages when things go
	 * wrong.  It's a good idea to catch them using a 'try' block like this
	 * one.  Your C++ compiler might need a command-line option to compile
	 * code that uses exceptions. */
	try {      
      std::cout << "a couple of test cases for 3460:435/535 Algorithms!!!\n";
      srand(time(NULL)); //seeding for rand()
      
      //generate p
      BigUnsigned big1 = BigUnsigned(1);
      bool prime = true;
      do {
        //generate random number
        big1 = 1;
        for (int i=0;i<200;i++) {
          big1 = big1*10 +rand();
        }
        //check for primality using fermat's little theorem
        prime = flt(big1);
      } while (!prime);

      std::cout << "my big1 !!!\n";
      std::cout << big1 << "\n";

      //generate q
      BigUnsigned big2 = BigUnsigned(1);
      prime = true;
      do {
        //generate random number
        big2 = 1;
        for (int i=0;i<200;i++) {
          big2 = big2*10 +rand();
        }
        //check for primality using fermat's little theorem
        prime = flt(big2);
      } while (!prime);
      /*
      std::cout << "my big2 !!!\n";
      std::cout << big2 << "\n";

      std::cout << "my big3 = big1*big2 !!!\n";
      BigUnsigned big3 = big1*big2;
      std::cout <<big3 << "\n";

      std::cout << "my big3/big2 !!!\n";
      std::cout <<big3/big2 << "\n";
      */
      //output p and q to a file called p_q.txt, one int per line, no whitespace
      std::ofstream pqfile;
      pqfile.open("p_q.txt", std::ios::trunc);
      pqfile << big1 << "\n" << big2;
      pqfile.close(); 
      std::cout << "p and q now in file p_q.txt\n";

      //use extended euclidean algo to generate two pairs of keys: (e,n) and (d,n) where n = q*p
      //compute n
      BigUnsigned n = big1 * big2;
      std::cout << "n: " << n << "\n";

      //compute phi for use with e and d
      BigUnsigned phi = (big1 - 1) * (big2 - 1);
      std::cout << "phi: " << phi << "\n";

      //generate e for public key
      BigUnsigned e = 1;
      prime = true;
      BigUnsigned temp;
      do {
        e = BigUnsigned(rand()) % (phi - 1) + 1;
        prime = flt(e);
        temp = gcd(phi, e);
      } while (!prime && temp != 1);
      std::cout << "e: " << e << "\n";

      //generate d for private key
      BigUnsigned d = modinv(e, phi);
      std::cout << "d: " << d << "\n";

      //Save the two pairs of keys in two separate files: e_n.txt and d_n.txt, one integer per line and no white space
      //e_n.txt
      std::ofstream enfile;
      enfile.open("e_n.txt", std::ios::trunc);
      enfile << e << "\n" << n;
      enfile.close();
      std::cout << "public key now in file e_n.txt\n";

      //d_n.txt
      std::ofstream dnfile;
      dnfile.open("d_n.txt", std::ios::trunc);
      dnfile << d << "\n" << n;
      dnfile.close();
      std::cout << "private key now in file d_n.txt\n";

	} catch(char const* err) {
		std::cout << "The library threw an exception:\n"
			<< err << std::endl;
	}

	return 0;
}