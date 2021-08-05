/*
author: Kyle Lugo, kjl56@zips.uakron.edu
Purpose: read in a csv file of stats from League of Legends games and
         compute whatever averages or statistics the user wants
*/
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main (int argc, char *argv[]) {
  int size;  //num of processes
  int rank;  //current process's rank
  const int root = 0;

  MPI_Init(NULL, NULL);  //initializes mpi stuff for use, creating a communicator called MPI_COMM_WORLD
  MPI_Comm_size(MPI_COMM_WORLD, &size);  //sets size
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);  //sets rank

  //check to make sure user entered a filename, exit program if didn't
  char *filename;
  int numOfLines; //used to specify the number of rows to use in the csv until I get dynamic allocation working (if I do)
  if (argc > 2) { //change to 1 once full file can dynamically be read in
    filename = argv[1];
    if (rank == root) printf("file: %s will be opened\n", filename);
    if (argc > 2) {
      numOfLines = atoi(argv[2]);
      if (rank == root) printf("the first %d lines will be used\n", numOfLines);
    }
  } else {
    if (rank == root) printf("please pass in a file to begin\n");
    
    MPI_Finalize();
    return 0;
  }

  //have root open file and parse it into a 2d array
  //all file I/O should be kept to master process only
  FILE *fp;
  const int numOfColumns = 50; //the number of columns in the csv
  double csvData[numOfLines*numOfColumns]; //only filled on root
  double localcsvData[numOfLines/size*numOfColumns];
  int localcsvSize = numOfLines/size*numOfColumns;

  if (rank == root) {
    fp = fopen(filename, "r"); //read-only mode

    //since the first row of the csv's are just the column names, they can be iterated over and ignored
    //for (int i = 0; i < numOfColumns; i++){
      //char temp;
      fscanf(fp, "%*s");
    //}

    //fill up the 2d array
    for (int i = 0; i < numOfLines; i++){
      for (int j = 0; j < numOfColumns; j++){
        fscanf(fp, "%lf,", &csvData[(i*numOfColumns) + j]);
        //printf("%.1f, ", csvData[(i*numOfLines+i) + numOfColumns]);
      }
    }
  }

  //loop program to allow user to perform various computations between data fields until user exits
  int tasks = 1; //1 = true, 0 = false
  while (tasks) {
    int userSelect;
    
    if (rank == root) {
      printf("please select one of the following options: \n");
      printf("  1. compute an average\n");
      printf("  2. compute a %% of operation\n");
      printf("  0. exit program\n");

      scanf("%d", &userSelect);
      //printf("you selected option %d\n", userSelect);
    }

    //have all threads wait until user makes a decision
    MPI_Bcast(&userSelect, sizeof(int), MPI_INT, root, MPI_COMM_WORLD);
    //MPI_Barrier(MPI_COMM_WORLD);

    if (userSelect == 0) {
      tasks = 0;
      //MPI_Finalize();
      //return 0; 
    } else if (userSelect == 1) { //compute an average
      
      //print menu of all column options for user
      if (rank == root) {
        //print column options
        printf("which stat would you like to compute an average for?: \n");
        printf("1. gameId  2. gameDuraton  3. blueWins\n4. blueFirstBlood  5. blueFirstTower  6. blueFirstBaron\n7. blueFirstDragon  8. blueFirstInhibitor  9. blueDragonKills\n10. blueBaronKills\n");
        printf("11. blueTowerKills  12. blueInhibitorKills  13. blueWardPlaced\n14. blueWardkills  15. blueKills  16. blueDeath\n17. blueAssist  18. blueChampionDamageDealt  19. blueTotalGold\n20. blueTotalMinionKills\n");
        printf("21. blueTotalLevel  22. blueAvgLevel  23. blueJungleMinionKills\n24. blueKillingSpree  25. blueTotalHeal  26. blueObjectDamageDealt\n27. redWins  28. redFirstBlood  29. redFirstTower\n30. redFirstBaron\n");
        printf("31. redFirstDragon  32. redFirstInhibitor  33. redDragonKills\n34. redBaronKills  35. redTowerKills  36. redInhibitorKills\n37. redWardPlaced  38. redWardkills  39. redKills\n40. redDeath\n");
        printf("41. redAssist  42. redChampionDamageDealt  43. redTotalGold\n44. redTotalMinionKills  45. redTotalLevel  46. redAvgLevel\n47. redJungleMinionKills  48. redKillingSpree  49. redTotalHeal\n50. redObjectDamageDealt\n");
        //get user option
        scanf("%d", &userSelect);
      }
      MPI_Bcast(&userSelect, sizeof(int), MPI_INT, root, MPI_COMM_WORLD);
      //MPI_Barrier(MPI_COMM_WORLD);
      
      if (userSelect > 0 && userSelect < 51) {
        //split csv data rows among threads 
        MPI_Scatter(&csvData, localcsvSize, MPI_DOUBLE, 
                    &localcsvData, localcsvSize, MPI_DOUBLE, 
                    root, MPI_COMM_WORLD);
        //compute average of selected column
        if(rank == root) printf("now computing average...\n");

        double localAvg = 0, local_start, local_finish, local_elapsed, elapsed;

        MPI_Barrier(MPI_COMM_WORLD);
        local_start = MPI_Wtime();

        /*code to be timed*/
        for (int i = 0; i < numOfLines/size; i++) {
          localAvg += localcsvData[(i*numOfColumns) + (userSelect-1)];
        }
        localAvg /= numOfLines/size;
        
        //combine results of each thread into root
        double *local_avgs = NULL;
        if (rank == root) {
          local_avgs = malloc(sizeof(double) * size);
        }
        MPI_Gather(&localAvg, 1, MPI_DOUBLE, local_avgs, 1, MPI_DOUBLE, root, MPI_COMM_WORLD);

        //have root compute total average from all the local averages
        if (rank == root) {
          double avg = 0;
          for (int i = 0; i < size; i++) {
            //printf("local_avgs row %d: %f\n", i, local_avgs[i]);
            avg += local_avgs[i];
          }
          avg /= size;

          printf("average computed. result: %f\n", avg);
        }

        //final average computed by root process. end timer
        local_finish = MPI_Wtime();
        local_elapsed = local_finish - local_start;
        MPI_Reduce(&local_elapsed, &elapsed, 1, MPI_DOUBLE, MPI_MAX, root, MPI_COMM_WORLD);
        if(rank == root) {
          printf("time taken: %e seconds\n", elapsed);
        }
      }

    } else if (userSelect == 2) { //compute a % of operation
      int localstat1 = 0;
      int localstat2 = 0;
      //have user choose first stat
      int select1;
      if (rank == root) {
        //print column options
        printf("please choose the first stat: \n");
        printf("1. gameId  2. gameDuraton  3. blueWins\n4. blueFirstBlood  5. blueFirstTower  6. blueFirstBaron\n7. blueFirstDragon  8. blueFirstInhibitor  9. blueDragonKills\n10. blueBaronKills\n");
        printf("11. blueTowerKills  12. blueInhibitorKills  13. blueWardPlaced\n14. blueWardkills  15. blueKills  16. blueDeath\n17. blueAssist  18. blueChampionDamageDealt  19. blueTotalGold\n20. blueTotalMinionKills\n");
        printf("21. blueTotalLevel  22. blueAvgLevel  23. blueJungleMinionKills\n24. blueKillingSpree  25. blueTotalHeal  26. blueObjectDamageDealt\n27. redWins  28. redFirstBlood  29. redFirstTower\n30. redFirstBaron\n");
        printf("31. redFirstDragon  32. redFirstInhibitor  33. redDragonKills\n34. redBaronKills  35. redTowerKills  36. redInhibitorKills\n37. redWardPlaced  38. redWardkills  39. redKills\n40. redDeath\n");
        printf("41. redAssist  42. redChampionDamageDealt  43. redTotalGold\n44. redTotalMinionKills  45. redTotalLevel  46. redAvgLevel\n47. redJungleMinionKills  48. redKillingSpree  49. redTotalHeal\n50. redObjectDamageDealt\n");
        //get user option
        scanf("%d", &select1);
      }
      MPI_Bcast(&select1, sizeof(int), MPI_INT, root, MPI_COMM_WORLD);

      //have user choose second stat
      int select2;
      if (rank == root) {
        //print column options
        printf("please choose the second stat: \n");
        printf("1. gameId  2. gameDuraton  3. blueWins\n4. blueFirstBlood  5. blueFirstTower  6. blueFirstBaron\n7. blueFirstDragon  8. blueFirstInhibitor  9. blueDragonKills\n10. blueBaronKills\n");
        printf("11. blueTowerKills  12. blueInhibitorKills  13. blueWardPlaced\n14. blueWardkills  15. blueKills  16. blueDeath\n17. blueAssist  18. blueChampionDamageDealt  19. blueTotalGold\n20. blueTotalMinionKills\n");
        printf("21. blueTotalLevel  22. blueAvgLevel  23. blueJungleMinionKills\n24. blueKillingSpree  25. blueTotalHeal  26. blueObjectDamageDealt\n27. redWins  28. redFirstBlood  29. redFirstTower\n30. redFirstBaron\n");
        printf("31. redFirstDragon  32. redFirstInhibitor  33. redDragonKills\n34. redBaronKills  35. redTowerKills  36. redInhibitorKills\n37. redWardPlaced  38. redWardkills  39. redKills\n40. redDeath\n");
        printf("41. redAssist  42. redChampionDamageDealt  43. redTotalGold\n44. redTotalMinionKills  45. redTotalLevel  46. redAvgLevel\n47. redJungleMinionKills  48. redKillingSpree  49. redTotalHeal\n50. redObjectDamageDealt\n");
        //get user option
        scanf("%d", &select2);
      }
      MPI_Bcast(&select2, sizeof(int), MPI_INT, root, MPI_COMM_WORLD);

      //split data rows among threads
      MPI_Scatter(&csvData, localcsvSize, MPI_DOUBLE, 
                    &localcsvData, localcsvSize, MPI_DOUBLE, 
                    root, MPI_COMM_WORLD);

      if(rank == root) printf("now computing...\n");

      double local_start, local_finish, local_elapsed, elapsed;

      MPI_Barrier(MPI_COMM_WORLD);
      local_start = MPI_Wtime();

      /**code to be timed*/
      //have threads count num of times each stat occurs
      for (int i = 0; i < numOfLines/size; i++) {
        if (localcsvData[(i*numOfColumns) + (select1-1)] == 1) {
          localstat1++;
          if (localcsvData[(i*numOfColumns) + (select2-1)] == 1) {
            localstat2++;
          }
        }
      }

      //combine results of each thread into root
      int *local_stat1 = NULL;
      int *local_stat2 = NULL;
      if (rank == root) {
        local_stat1 = malloc(sizeof(int) * size);
        local_stat2 = malloc(sizeof(int) * size);
      }
      MPI_Gather(&localstat1, 1, MPI_INT, local_stat1, 1, MPI_INT, root, MPI_COMM_WORLD);
      MPI_Gather(&localstat2, 1, MPI_INT, local_stat2, 1, MPI_INT, root, MPI_COMM_WORLD);

      //have root compute the total %
      if (rank == root) {
        int stat1total = 0;
        int stat2total = 0;
        for (int i = 0; i < size; i++) {
          stat1total += local_stat1[i];
          stat2total += local_stat2[i];
        }
        int percentage;
        if (stat1total == 0 || stat2total == 0) {
          percentage = 0;
        } else {
          percentage = stat2total*100/stat1total;
        }

        printf("option 2 occurs in %d out of %d occurances of option 1, or %d%% of occurances\n",stat2total, stat1total, percentage);
      }

      //final percentage calculated by root process. end timer
      local_finish = MPI_Wtime();
      local_elapsed = local_finish - local_start;
      MPI_Reduce(&local_elapsed, &elapsed, 1, MPI_DOUBLE, MPI_MAX, root, MPI_COMM_WORLD);
      if (rank == root) {
        printf("time elapsed: %e seconds\n", elapsed);
      }
    }
    
  }

  MPI_Finalize();
  return 0;
}