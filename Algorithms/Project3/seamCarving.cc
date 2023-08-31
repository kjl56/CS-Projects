//Assignment 3: Seam Carving
//code written by:  Kyle Lugo
//email:            kjl56@zips.uakron.edu
//student ID:       4148313
//project description: this program removes 'seams' of pixels from images in order to reduce their resolution 
//                     by removing the least visible pixels across the image. Seams are detected first vertically through the image
//                     and removed, then horizontally. Seam carving is done to try to preserve the most visible
//                     portions of an image to preserve detail, instead of simple cropping.

//standard libraries
#include <string>
#include <iostream>
#include <stdlib.h> 
#include <algorithm>
#include <fstream>
#include <vector>
#include <iterator>

//transposes a 2d vector
void transpose(std::vector<std::vector<int>> &vect) {
  if (vect.size() == 0) {
    return;
  }

  std::vector<std::vector<int>> transVec(vect[0].size(), std::vector<int>());
  for (int i = 0; i < vect.size(); i++) {
    for (int j = 0; j < vect[i].size(); j++) {
      transVec[j].push_back(vect[i][j]);
    }
  }
  vect = transVec;
}

//creates an energy matrix from the image's greyscale values
//must pass in the 2d vector of the image's values and a 2d vector to store energy matrix in
void createEnergyMatrix(const std::vector<std::vector<int>> &greyscaleValues, std::vector<std::vector<int>> &energyMatrix) {
  int tempEnergyValue = 0;
    int valueCenter = 0, valueLeft = 0, valueRight = 0, valueUp = 0, valueDown = 0;
    for (int i = 0; i < greyscaleValues.size(); i++) {
      //make row
      std::vector<int> energyRow;
      //std::cout << "\nrow " << i+1 << ": ";
      //calculate energy of each greyscale value in greyscaleValues vector, and add to energy matrix
      //e(x,y) = abs(v(x,y)-v(x-1,y))+abs(v(x,y)-v(x+1,y))+abs(v(x,y)-v(x,y-1))+abs(v(x,y)-v(x,y+1))
      for (int j = 0; j < greyscaleValues[i].size(); j++) {
        valueCenter = greyscaleValues[i][j]; //j is x, i is y
        //check if i is min
        if (i != 0) { valueDown = greyscaleValues[i-1][j]; } else {valueDown = valueCenter;}
        tempEnergyValue += abs(valueCenter - valueDown); 
        //check if i is max
        if (i != greyscaleValues.size()-1) { valueUp = greyscaleValues[i+1][j]; } else {valueUp = valueCenter;}
        tempEnergyValue += abs(valueCenter - valueUp);
        //check if j is min
        if (j != 0) { valueLeft = greyscaleValues[i][j-1]; } else {valueLeft = valueCenter;}
        tempEnergyValue += abs(valueCenter - valueLeft);
        //check if j is max
        if (j != greyscaleValues[i].size()-1) { valueRight = greyscaleValues[i][j+1]; } else {valueRight = valueCenter;}
        tempEnergyValue += abs(valueCenter - valueRight);

        //std::cout << tempEnergyValue << " ";
        energyRow.push_back(tempEnergyValue);
        tempEnergyValue = 0;
      }
      energyMatrix.push_back(energyRow);
    }
}

//creates a cumulative energy matrix from the energy matrix
//createEnergyMatrix needs to be done first
//must pass in the 2d vector of the energy matrix and a 2d vector to store the cumulative energy matrix in
void createCumEnergyMatrix(const std::vector<std::vector<int>> &energyMatrix, std::vector<std::vector<int>> &cumEnergyMatrix) {
  int tempCumEnergyValue = 0;
  int energyValueCenter = 0, energyValueDiagLeft = 0, energyValueDown = 0, energyValueDiagRight = 0;
  for (int i = 0; i < energyMatrix.size(); i++) {
    //make row
    std::vector<int> cumEnergyRow;
    //std::cout << "\nrow " << i+1 << ": ";
    //calculate cumulative energy using values from the energyMatrix vector and add to cumEnergyMatrix vector
    //for vertical seam: m(x,y) = e(x.y) + min( m(x-1,y-1), m(x,y-1), m(x+1,y-1) )
    for (int j = 0; j < energyMatrix[i].size(); j++) { //j is x, i is y
      energyValueCenter = energyMatrix[i][j]; //e(x,y)
      //check if i is min
      if (i == 0) { 
        tempCumEnergyValue = energyValueCenter;
      } else {
        //check if j is min
        if (j != 0) { energyValueDiagLeft = cumEnergyMatrix[i-1][j-1]; } else { energyValueDiagLeft = 5000000; }
        energyValueDown = cumEnergyMatrix[i-1][j];
        //check if j is max
        if (j != energyMatrix[i].size()-1) { energyValueDiagRight = cumEnergyMatrix[i-1][j+1]; } else { energyValueDiagRight = 5000000; }
        tempCumEnergyValue = energyValueCenter + std::min(std::min(energyValueDiagLeft, energyValueDown), energyValueDiagRight);
      }

      //std::cout << tempCumEnergyValue << " ";
      cumEnergyRow.push_back(tempCumEnergyValue);
      tempCumEnergyValue = 0;
    }
    cumEnergyMatrix.push_back(cumEnergyRow);
  }
}

//uses the cumulative energy matrix to form a vertical seam in the image and removes it
//can be used for horizontal seams if the image's 2d vector is transposed first before creating the cumulative energy matrix
//must pass in the cumulative energy matrix and the image's 2d vector 
void seamRemoval(const std::vector<std::vector<int>> &cumEnergyMatrix, std::vector<std::vector<int>> &greyscaleValues) {
  //std::cout << "points to remove: \n";
  int tempXIndex;
  for (int i = 0; i < greyscaleValues.size(); i++) {//traverse each row
    //find point in each row to remove
    //first point is min element
    //subsequent points are minimum between the 3 points diagnol to previous point
    //std::cout << "index row " << i+1 << ": ";
    if (i == 0) {
      auto minElement = std::min_element(cumEnergyMatrix[i].begin(), cumEnergyMatrix[i].end());
      tempXIndex = std::distance( cumEnergyMatrix[i].begin(), minElement );
      greyscaleValues[i].erase(greyscaleValues[i].begin()+tempXIndex);
      //std::cout << tempXIndex << "\n";
    } else {
      //if previous point was all the way to the left
      if (tempXIndex == 0) {
        if (cumEnergyMatrix[i][tempXIndex] < cumEnergyMatrix[i][tempXIndex+1]) {
          //std::cout << cumEnergyMatrix[i][tempXIndex] <<"\n";
          greyscaleValues[i].erase(greyscaleValues[i].begin()+tempXIndex);
        } else {
          //std::cout << cumEnergyMatrix[i][tempXIndex+1] << "\n";
          greyscaleValues[i].erase(greyscaleValues[i].begin()+tempXIndex+1);
          tempXIndex++;
        }
        //std::cout << std::min(cumEnergyMatrix[i][tempXIndex], cumEnergyMatrix[i][tempXIndex+1]) << "\n";
      }
      //if previous point was all the way to the right
      else if (tempXIndex == greyscaleValues[i].size()-1) {
        if (cumEnergyMatrix[i][tempXIndex] < cumEnergyMatrix[i][tempXIndex-1]) {
          //std::cout << cumEnergyMatrix[i][tempXIndex] << "\n";
          greyscaleValues[i].erase(greyscaleValues[i].begin()+tempXIndex);
        }
        else {
          //std::cout << cumEnergyMatrix[i][tempXIndex-1] << "\n";
          greyscaleValues[i].erase(greyscaleValues[i].begin()+tempXIndex-1);
          tempXIndex--;
        }
        //std::cout << std::min(cumEnergyMatrix[i][tempXIndex], cumEnergyMatrix[i][tempXIndex-1]) << "\n";
      } else {
        //if tempxindex+1 is the lowest
        if (cumEnergyMatrix[i][tempXIndex+1] < cumEnergyMatrix[i][tempXIndex] && cumEnergyMatrix[i][tempXIndex+1] < cumEnergyMatrix[i][tempXIndex-1]) {
          //std::cout << cumEnergyMatrix[i][tempXIndex+1] << "\n";
          greyscaleValues[i].erase(greyscaleValues[i].begin()+tempXIndex+1);
          tempXIndex++;
        } //if tempxindex-1 is the lowest
        else if (cumEnergyMatrix[i][tempXIndex-1] < cumEnergyMatrix[i][tempXIndex] && cumEnergyMatrix[i][tempXIndex-1] < cumEnergyMatrix[i][tempXIndex+1]) {
          //std::cout << cumEnergyMatrix[i][tempXIndex-1] << "\n";
          greyscaleValues[i].erase(greyscaleValues[i].begin()+tempXIndex-1);
          tempXIndex--;
        } else { //if tempxindex is the lowest or there is a tie for the lowest
          //std::cout << cumEnergyMatrix[i][tempXIndex] << "\n";
          greyscaleValues[i].erase(greyscaleValues[i].begin()+tempXIndex);
        }
        //std::cout << std::min(std::min(cumEnergyMatrix[i][tempXIndex-1], cumEnergyMatrix[i][tempXIndex]), cumEnergyMatrix[i][tempXIndex+1]) << "\n";
      }
    }
  }
}



int main(int argc, char *argv[]) {
  if (argc != 4)
    std::cout << "wrong format! should be \"a.exe imageFile numOfVerticalSeams numOfHorizontalSeams\"";
  else {
    std::string imageFileName = argv[1];
    int vertSeams = std::atoi(argv[2]);
    int horizSeams = std::atoi(argv[3]);

    //open file
    std::ifstream imageFile;
    imageFile.open(imageFileName);
    if (!imageFile.is_open()) {
      std::cout << "error opening image, program terminated\n";
      return 0;
    }
    std::cout << imageFileName << " opened successfully\n";

    std::vector<std::vector<int>> greyscaleValues;
    std::vector<std::vector<int>> energyMatrix;
    std::vector<std::vector<int>> cumEnergyMatrix;
    int imageWidth;
    int imageHeight;
    int maxGreyscaleValue;

    //extract "P2" line from pgm
    char comment[128];
    imageFile.getline(comment, 128);
    if (comment[0] != 'P' && comment[1] != '2') {
      std::cout << "file is not a pgm image, program terminated\n";
      return 0;
    }

    //extract comment
    imageFile.getline(comment, 128);

    //extract image width
    imageFile >> imageWidth;

    //extract image height
    imageFile >> imageHeight;

    //extract max greyscale value
    imageFile >> maxGreyscaleValue;

    std::cout << "image width: " << imageWidth << "\nimage height: " << imageHeight
              << "\nmax greyscale value: " << maxGreyscaleValue << "\nvertical seams to be removed: " << vertSeams 
              << "\nhorizontal seams to be removed: " << horizSeams << "\n";
    if (imageWidth-vertSeams < 2) {
      std::cout << "error: number of vertical seams to remove is to large for this image\n";
      return 0;
    } else if (imageHeight-horizSeams < 2) {
      std::cout << "error: number of horizontal seams to remove is to large for this image\n";
      return 0;
    }
    std::cout << "\nextracting greyscale values from image.....\n";

    //extract all greyscale values of image row by row
    int tempGreyscaleValue;
    for (int i = 0; i < imageHeight; i++) {
      //make row
      std::vector<int> greyscaleRow;
      //std::cout << "\nrow " << i+1 << ": ";
      //stuff values into row
      for (int j = 0; j < imageWidth; j++) {
        imageFile >> tempGreyscaleValue;
        //std::cout << tempGreyscaleValue << " ";
        greyscaleRow.push_back(tempGreyscaleValue);
      }
      //stuff row into 2d vector
      greyscaleValues.push_back(greyscaleRow);
    }
    std::cout << "greyscale values extracted\n";

    //remove all vertical seams first
    std::cout << "\nnow forming vertical seams.....\n";
    for (int i = 0; i < vertSeams; i++) {
      std::cout << "creating energy matrix.....\n";
      //create 2d vector for energy matrix
      createEnergyMatrix(greyscaleValues, energyMatrix);
      std::cout << "energy matrix created\n";

      std::cout << "creating cumulative energy matrix for vertical seam.....\n";
      //create 2d vector for cumulative energy matrix for a vertical seam
      createCumEnergyMatrix(energyMatrix, cumEnergyMatrix);
      std::cout << "cumulative energy matrix created\n";

      std::cout << "now removing vertical seam.....\n";
      //run through seam carving function to remove vertical seams
      seamRemoval(cumEnergyMatrix, greyscaleValues);
      std::cout << "seam removed\n";

      energyMatrix.clear();
      cumEnergyMatrix.clear();
      imageWidth--;
    }
    std::cout << "requested vertical seams removed\n";

    /*std::cout << "\nnew greyscale table\n";
    for (int i = 0; i < imageHeight; i++) {
      std::cout << "\nrow " << i+1 << ": ";
      for (int j = 0; j < imageWidth-1; j++) {
        std::cout << greyscaleValues[i][j] << " ";
      }
    }*/

    //rotate the image clockwise 90 degrees (aka transpose the matrix)
    transpose(greyscaleValues);
    /*std::cout << "\ntransposed greyscale table\n";
    for (int i = 0; i < greyscaleValues.size(); i++) {
      std::cout << "\nrow " << i+1 << ": ";
      for (int j = 0; j < greyscaleValues[0].size(); j++) {
        std::cout << greyscaleValues[i][j] << " ";
      }
    }*/

    //remove all horizontal seams
    std::cout << "\nnow forming horizontal seams.....\n";
    for (int i = 0; i < horizSeams; i++) {
      std::cout << "creating energy matrix.....\n";
      //create 2d vector for energy matrix
      createEnergyMatrix(greyscaleValues, energyMatrix);
      std::cout << "energy matrix created\n";

      std::cout << "creating cumulative energy matrix for vertical seam.....\n";
      //create 2d vector for cumulative energy matrix for a vertical seam
      createCumEnergyMatrix(energyMatrix, cumEnergyMatrix);
      std::cout << "cumulative energy matrix created\n";

      std::cout << "now removing horizontal seam.....\n";
      //run through seam carving function to remove vertical seams
      seamRemoval(cumEnergyMatrix, greyscaleValues);
      std::cout << "seam removed\n";

      energyMatrix.clear();
      cumEnergyMatrix.clear();
      imageHeight--;
    }
    std::cout << "requested horizontal seams removed\n";
    
    /*std::cout << "\nnew greyscale table\n";
    for (int i = 0; i < greyscaleValues.size(); i++) {
      std::cout << "\nrow " << i+1 << ": ";
      for (int j = 0; j < greyscaleValues[0].size(); j++) {
        std::cout << greyscaleValues[i][j] << " ";
      }
    }*/

    //rotate the image counterclockwise 90 degrees back to its original orientation (transpose again)
    transpose(greyscaleValues);
    /*std::cout << "\ntransposed greyscale table\n";
    for (int i = 0; i < greyscaleValues.size(); i++) {
      std::cout << "\nrow " << i+1 << ": ";
      for (int j = 0; j < greyscaleValues[0].size(); j++) {
        std::cout << greyscaleValues[i][j] << " ";
      }
    }*/

    std::cout << "\nall seams removed\n";
    //output new image as image_processed.pgm
    std::ofstream processedImage;
    std::string processedFilename = imageFileName.substr(0, imageFileName.size()-4);
    processedFilename += "_processed.pgm";
    processedImage.open(processedFilename, std::ios::trunc);
    processedImage << "P2\n" << comment << "\n" << imageWidth << " " << imageHeight << "\n" << maxGreyscaleValue << "\n";
    for (int i = 0; i < greyscaleValues.size(); i++) {
      for (int j = 0; j < greyscaleValues[0].size(); j++) {
        processedImage << greyscaleValues[i][j] << " ";
      }
      processedImage << "\n";
    }
    processedImage.close();
    std::cout << "new image has been saved as " << processedFilename << "\n";
  }

  return 0;
}
