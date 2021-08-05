/*
author: Kyle Lugo, kjl56@zips.uakron.edu
purpose:  learning how mpi processes interact through an exercise
          where the master process distributes data to all the 
          other processes and have them print the data
*/
#include <stdio.h>
#include <mpi.h>

int main (void) {
  int size;  //num of processes
  int rank;  //current process's rank
  char file[4096];  //will store hello.html
  const int root = 0;

  MPI_Init(NULL, NULL);  //initializes mpi stuff for use, creating a communicator called MPI_COMM_WORLD
  MPI_Comm_size(MPI_COMM_WORLD, &size);  //sets size
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);  //sets rank

  if (rank == root) { //master process
    //load hello.html
    FILE *fp;
    fp = fopen("hello.html", "r"); //open file for reading only
    fread(file, sizeof(char), sizeof(file), fp);  //stick file content into array named 'file'
    fclose(fp);  //close file

  }
  //connect all processes that are a part of the MPI_COMM_WORLD communicator
  //to a broadcast and have all processes copy 'file' data from 'root' (aka, the master process)
  MPI_Bcast(file, sizeof(file), MPI_CHAR, root, MPI_COMM_WORLD);

  //display process number and 'file' content
  printf("Greetings from process %d of %d:\n%s\n", rank, size, file);
  //in c, %d substitutes in an int, %s substitutes in a string
  //from the arguments in the order they appear 

  MPI_Finalize();  //deallocates mpi stuff, important to do before ending
  return 0;
}