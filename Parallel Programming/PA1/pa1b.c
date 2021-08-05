/*
author: Kyle Lugo, kjl56@zips.uakron.edu
purpose: Write a parallel program to multiply a mxn matrix and nx1 vector. 
Your program should read the matrix and the vector from a data file (mv-data.txt) 
and print the results on the screen (assuming you only have 2 core processors).
*/
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main (void) {
  int size;  //num of processes
  int rank;  //current process's rank
  const int root = 0;

  MPI_Init(NULL, NULL);  //initializes mpi stuff for use, creating a communicator called MPI_COMM_WORLD
  MPI_Comm_size(MPI_COMM_WORLD, &size);  //sets size
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);  //sets rank

  int m, n; 
  int k = 1;

  //all file I/O should be kept to master process only
  FILE *fp;
  if (rank == root) {
    //extract m, n
    fp = fopen("mv-data.txt", "r"); //read-only mode
    
    fscanf(fp, "%d", &m);
    fscanf(fp, "%d", &n);
  }

  //share m and n with all processes so each may create their own matrixes and vectors
  //done this way since I failed with  the dynamic allocation method, and it's simpler
  MPI_Bcast(&m, sizeof(int), MPI_INT, root, MPI_COMM_WORLD);
  MPI_Bcast(&n, sizeof(int), MPI_INT, root, MPI_COMM_WORLD);

  int matrix[m*n];
  int vector[n*k];
  int result[m*k];
  int localMatrix[m*n/size];
  int local_result[m*k];

  if (rank == root) {
    //fill matrix
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        fscanf(fp, "%d", &matrix[(i*m+i) + j]);
        //printf("%d\n", matrix[(i*m+i) + j]);
      }
    }

    //fill vector
    for (int i = 0; i < n; i++) {
      fscanf(fp, "%d", &vector[i]);
    }

    fclose(fp);
  }

  /* parallel edition from powerpoint */
  void matVectMult(
      int local_a[], //in
      int local_x[], //in
      int local_y[], //out
      int local_m, //in
      int n, //in
      int local_n, //in
      MPI_Comm comm //in
    ) {
    int* x;
    //int local_ok = 1;

    x = malloc(n*sizeof(int));
    MPI_Allgather(local_x, local_n, MPI_INT, x, local_n, MPI_INT, comm);

    for (int i = 0; i < local_m; i++) {
      local_y[i] = 0;
      for (int j = 0; j < n; j++)
        local_y[i] += local_a[i*n+j] * x[j];
    }
    free(x);
  }

  //scatter rows of matrix to different processes
  //splits 'matrix' into equal parts based on total process count ('size') and sends each part to a process's 'localMatrix'
  MPI_Scatter(&matrix, m*n/size, MPI_INT, &localMatrix, m*n/size, MPI_INT, root, MPI_COMM_WORLD);

  printf("Greetings from process %d of %d:\nlocal matrix of process %d: ", rank, size, rank);
  for (int i = 0; i < m*n/size; i++) {
    printf("%d, ", localMatrix[i]);
  }

  //broadcast 'vector' to all processes
  //done with broadcast since each process will need the entire vector to do its math
  MPI_Bcast(vector, n, MPI_INT, root, MPI_COMM_WORLD);

  //have each process do a part of the calculation
  matVectMult(localMatrix, vector, local_result, m/size, n, n, MPI_COMM_WORLD);

  printf("\nlocal result of process %d: ", rank);
  for (int i = 0; i < m/size; i++) {
    printf("%d, ", local_result[i]);
  }

  //gather the results of each process and combine them for the final answer
  MPI_Gather(local_result, m/size, MPI_INT, result, m/size, MPI_INT, root, MPI_COMM_WORLD);
  if (rank == root) {
    printf("\nfinal result: ");
    for (int i = 0; i < m*k; i++) {
      printf("%d, ", result[i]);
    }
    printf("\n");
  }

  MPI_Finalize();
  return 0;
}