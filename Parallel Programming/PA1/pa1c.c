/*
author: Kyle Lugo, kjl56@zips.uakron.edu
purpose: 
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

void fillArray(int lower, int upper, int arrSize, int arr[]) {
  for (int i = 0; i < arrSize; i++) {
    arr[i] = ((rand() % (upper - lower + 1)) + lower);
  }
}

unsigned int factorial(unsigned int n) 
{ 
  if (n == 0) return 1; 
  return n * factorial(n - 1); 
}

int main (int argc, char *argv[]) {
  int size;  //num of processes
  int rank;  //current process's rank
  const int root = 0;

  MPI_Init(NULL, NULL);  //initializes mpi stuff for use, creating a communicator called MPI_COMM_WORLD
  MPI_Comm_size(MPI_COMM_WORLD, &size);  //sets size
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);  //sets rank

  //prompt user for two integers m and n
  int m, n;
  if (rank == root) {
    printf("enter a value for m: ");
    fflush(stdout);
    scanf("%d", &m);
    printf("\nenter a value for n: ");
    fflush(stdout);
    scanf("%d", &n);
  }
  MPI_Bcast(&m, sizeof(int), MPI_INT, root, MPI_COMM_WORLD);
  MPI_Bcast(&n, sizeof(int), MPI_INT, root, MPI_COMM_WORLD);
  
  //create an array of 1000
  //allow user to input array size in command line so I don't have to copy paste the same code later
  int arraySize;
  if (argc > 1) {
    arraySize = atoi(argv[1]);
  } else {
    arraySize = 1000;
  }
  int randNumArr[arraySize];
  if(rank == root) printf("\narray of size %d created\nsize can be changed in command line\n", arraySize);
  int localArraySize = arraySize/size;
  int localRandNumArr[localArraySize];
  
  //fill the array with random numbers between m and n
  if (rank == root) {
    //done only on root so all processes have the same numbers to work with once split
    srand(time(0));
    fillArray(m, n, arraySize, randNumArr);
    printf("array filled with random numbers between %d and %d on root process\n", m, n);
  }
  //split the array 'randNumArr' between all processes
  MPI_Scatter(randNumArr, localArraySize, MPI_INT, localRandNumArr, localArraySize, MPI_INT, root, MPI_COMM_WORLD);
  if (rank == root) printf("array split between %d processes\nnow computing factorials\n", size);

  //compute the factorial  of each number in the array
  //print out the time it takes to do this 
  double local_start, local_finish, local_elapsed, elapsed;
  
  MPI_Barrier(MPI_COMM_WORLD);
  local_start = MPI_Wtime();

  /*code to be timed*/
  for (int i = 0; i < localArraySize; i++) {
    localRandNumArr[i] = factorial(localRandNumArr[i]);
  }

  local_finish = MPI_Wtime();
  local_elapsed = local_finish - local_start;
  MPI_Reduce(&local_elapsed, &elapsed, 1, MPI_DOUBLE, MPI_MAX, root, MPI_COMM_WORLD);
  if (rank == root) {
    printf("factorials computed. elapsed time = %e seconds\n", elapsed);
  }
  
  //repeat for arrays of size 2000, 4000, 8000 and 16000
  //run the program with 1, 2, 4 and 8 processors
  //record the run-times in performance.txt
  //calculate  and add to performance.txt the speedup and efficiency of all the above cases
  //at the top of performance.txt, list the values of m and n used , whether the program is scalable, and if yes, then strongly or weakly

  /*
  double local_start, local_finish, local_elapsed, elapsed;
  
  MPI_Barrier(MPI_COMM_WORLD);
  local_start = MPI_Wtime();
  //code to be timed
  local_finish = MPI_Wtime();
  local_elapsed = local_finish - local_start;
  MPI_Reduce(&local_elapsed, &elapsed, 1, MPI_DOUBLE, MPI_MAX, root, MPI_COMM_WORLD);
  if (rank == root) {
    printf("elapsed time = %e seconds\n", elapsed);
  }
  */
  MPI_Finalize();
  return 0;
}