/***
  prepared for CS435 Project 1 part 2
**/

#include <string.h>
#include <iostream>
#include <fstream>
#include "sha256.h"
#include "BigIntegerLibrary.hh"

 
int main(int argc, char *argv[])
{
  //demonstrating how sha256 works
  std::string input = "testing";
  std::string output1 = sha256(input);
  std::cout << "sha256('"<< input << "'):" << output1 << "\n";
  
  //demo bigInt works here
  BigUnsigned a = stringToBigUnsigned("124338907642982722929222542626327282");
  BigUnsigned b = stringToBigUnsigned("124338907642977775546469426263278643");
  std::cout << "big a = " <<a<<"\n";
  std::cout << "big b = " <<b<<"\n";
  std::cout << "big a*b = " <<a*b<<"\n";

  //Second part of your project starts here
  if (!((argc == 3 && argv[1][0]=='s') || (argc == 4 && argv[1][0]=='v'))) 
    std::cout << "wrong format! should be \"a.exe s filename\" or \"a.exe v filename sigfile\"";
  else {
    std::string filename = argv[2];
          
    //read the file
    std::streampos begin,end;
    std::ifstream myfile (filename.c_str(), std::ios::binary);
    begin = myfile.tellg();
    myfile.seekg (0, std::ios::end);
    end = myfile.tellg();
    std::streampos size = end-begin;
    std::cout << "size of the file: " << size << " bytes.\n"; //size of the file
    
    myfile.seekg (0, std::ios::beg);
    char * memblock = new char[size];
    myfile.read (memblock, size); //read file; it's saved in the char array memblock
    myfile.close();
    
    std::string copyOFfile = filename+".Copy"; 
    std::ofstream myfile2 (copyOFfile.c_str(), std::ios::binary);
    myfile2.write (memblock, size); //write to a file
    myfile2.close();
    
    std::cout<<memblock;
      
    if (argv[1][0]=='s') {
      std::cout << "\n"<<"Need to sign the doc.\n";
      
      //generate sha256 hash of file to be signed
      std::string fileHash = sha256(memblock); //base 16
      std::cout << "sha256('"<< memblock << "'): " << fileHash << "\n";

      //get private key from d_n.txt
      std::ifstream dnfile;
      dnfile.open("d_n.txt");
      std::string numString;
      std::getline(dnfile, numString);
      BigUnsigned d = stringToBigUnsigned(numString);
      std::getline(dnfile, numString);
      BigUnsigned n = stringToBigUnsigned(numString);
      dnfile.close();
      std::cout << "d: " << d << "\nn: " << n << "\n";

      //sign hash with private key
      BigUnsignedInABase q = BigUnsignedInABase(fileHash, 16); //convert from base 16 to base 10
      BigUnsigned hashNum = q;
      std::cout << "hashNum: " << hashNum << "\n";
      BigUnsigned signature = modexp(hashNum, d, n);
      std::cout << "signature: " << signature << "\n";

      //save signature to file.txt.signature
      std::ofstream sigFile;
      sigFile.open("file.txt.signature", std::ios::trunc);
      sigFile << signature;
      sigFile.close();
      std::cout << "signature now in file file.txt.signature\n";

    }
    else {
      std::cout << "\n"<<"Need to verify the doc.\n";
      
      //generate sha256 hash of file to be signed
      std::string fileHash = sha256(memblock); //base 16
      std::cout << "sha256('"<< memblock << "'): " << fileHash << "\n";

      //get signature from file.txt.signature
      std::string sigArg = argv[3];
      std::cout << "sigArg: " << sigArg << "\n";
      std::ifstream sigFile;
      sigFile.open(sigArg);
      std::string sigString;
      std::getline(sigFile, sigString);
      BigUnsigned signature = stringToBigUnsigned(sigString); //base 10
      sigFile.close();
      std::cout << "signature: " << signature << "\n";

      //get public key from e_n.txt
      std::ifstream enfile;
      enfile.open("e_n.txt");
      std::string numString;
      std::getline(enfile, numString);
      BigUnsigned e = stringToBigUnsigned(numString);
      std::getline(enfile, numString);
      BigUnsigned n = stringToBigUnsigned(numString);
      enfile.close();
      std::cout << "e: " << e << "\nn: " << n << "\n";

      //sign signature with public key
      BigUnsigned modSig = modexp(signature, e, n);
      std::cout << "modded signature: " << modSig << "\n";

      //compare sha256 hash and signed signature
      //report whether document is authentic or modified
      BigUnsignedInABase q = BigUnsignedInABase(fileHash, 16); //convert from base 16 to base 10
      BigUnsigned hashNum = q;
      std::cout << "base 10 hash: " << hashNum << "\n";
      if (hashNum == modSig) std::cout << "signature and hash match, document authentic\n";
      else std::cout << "signature and hash do not match, document has been modified\n";
        
    }
    delete[] memblock;
  }
  return 0;
}