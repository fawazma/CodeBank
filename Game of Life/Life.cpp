#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <cstring>
#include <math.h>
#include <fstream>
#include <iomanip>

#include "Life.h"



using namespace std;

Life::Life() {
    height = 0;
    width = 0;
    generationCount = 0;
    empty = false;
    stabilizes = false;

}

Life::Life(int h, int w) {
    height = h;
    width = w;

    currentGrid = new char*[height];
    for (int i = 0; i < height; ++i)
        currentGrid[i] = new char[width];

}

Life::Life(const Life& other) {

    height = other.height;
    width = other.width;

    currentGrid = new char*[height];
    for (int i = 0; i < height; ++i) {
        currentGrid[i] = new char[width];
        memcpy(&currentGrid[i], &other.currentGrid[i], width * sizeof (int));
    }

}

Life::~Life() {

}

const Life& Life::operator=(const Life& rhs) {

    if (this != &rhs) {

        height = rhs.height;
        width = rhs.width;

        for (int i = 0; i < height; ++i) {
            memcpy(&currentGrid[i], &rhs.currentGrid[i], width * sizeof (int));
        }
    }
    return *this;
}

void Life::randomizeCells(int h, int w, double density) {

    height = h;
    width = w;

    // initializing the grid
    currentGrid = new char*[height];
    for (int i = 0; i < h; ++i)
        currentGrid[i] = new char[width];


    int row = 0;
    int column = 0;
    int xPopulation = (height * width)*(density); // gets the number of x's to put in grid

    for (int s = 0; s < height; ++s) // fills grid with dashes first
    {
        for (int col = 0; col < width; ++col) {
            currentGrid[s][col] = '-';
        }
    }

 //populating the Life with random values
    while (xPopulation > 0) {
        row = rand() % height ;
        column = rand() % width ;
        if (currentGrid[row][column] != 'X') {
            currentGrid[row][column] = 'X';
            --xPopulation;
        }

    }
}

void Life::populateFromFile(string filename) {

    ifstream ifs;

    //open the file in input mode i.e for read purpose
    ifs.open(filename.c_str(), ios_base::in);


    ifs.clear();
    ifs.seekg(0, ios::beg); // set file back to the beginning for next iteration


    // read the width & height of the Life from map file .
    ifs >> height; //read the first  line into rows
    ifs >> width; //read the second line into rows

    // based on above dimension, initialize the Life
    currentGrid = new char*[height];
    for (int i = 0; i < height; ++i)
        currentGrid[i] = new char[width];


    // populate the Life based on file content
    string line;
    int rowNum = 0;
    while (!ifs.eof()) {
        ifs >> line;
        for (int i = 0; i < line[i] != '\0'; ++i) {
            currentGrid[rowNum][i] = line[i];
        }
        rowNum++;
    }
    ifs.close();
}

void Life::printToConsole() {

    cout << endl << generationCount++ << endl;
    for (int r = 0; r < height; r++) {
        for (int col = 0; col < width; col++) {
            cout << currentGrid[r][col] << setw(1);
        }
        cout << endl;
    }
}

void Life::printToFile(string filename) {

    ofstream ofs;
    ofs.open(filename.c_str(), ofstream::out | ofstream::app); // open .. create, and append
    ofs << generationCount++ << endl;

    for (int r = 0; r < height; r++) {
        for (int col = 0; col < width; col++) {
            ofs << currentGrid[r][col] << setw(1);
        }
        ofs << endl;
    }
    ofs << "\n";

    ofs.close();
}

bool Life::isEmpty() {

    return empty;
}

bool Life::isStabilized() {

    return stabilizes;
}

int Life:: getAliveNeighborCount(int row , int col , char simulationMode)
{
    int aliveLiveCnt = 0;

                // this section calculate neighbors for cells on the grid boundaries
            if (row == 0 || row == height - 1 || col == 0 || col == width - 1) {

                if (simulationMode == 'C' || simulationMode == 'c') {

                    //  Classic mode: All locations off the grid are considered to be empty.
                    //  so fill the border cells with '-'
                    //  since by default , all cells have '-' value , so simply dont process .
                    return 0 ;
                      // this will continue with next row/column

                } else {  // simulationMode == 'D' || simulationMode == 'd')
                    if ((row == 0) && (col == 0)) //top left corner
                    {
                        if (simulationMode == 'D' || simulationMode == 'd') {

                            // adjacent  cells
                            if (currentGrid[row][col+1] == 'X') // same row , next column
                                 aliveLiveCnt++;
                            if (currentGrid[row+1][col+1] == 'X') // diagonal
                                aliveLiveCnt++;
                            if (currentGrid[row+1][col] == 'X') // next row , same column
                                aliveLiveCnt++;

                            // horizontally wrapped
                             if (currentGrid[height -1][col] == 'X')
                                 aliveLiveCnt++;
                            if (currentGrid[height -1][col+1] == 'X')
                                aliveLiveCnt++;

                             // vertically wrapped

                            if (currentGrid[row][width-1] == 'X')
                                 aliveLiveCnt++;
                            if (currentGrid[row+1][width-1] == 'X')
                                aliveLiveCnt++;

                            // diagonally wrapped

                             if (currentGrid[height -1][width-1] == 'X')
                                aliveLiveCnt++;
                        }

                        if (simulationMode == 'M' || simulationMode == 'm') {

                             if (currentGrid[row][col] == 'X')
                                 aliveLiveCnt= aliveLiveCnt+3 ;




                        }

                    }
                    if ((row == 0) && ((col > 0) && (col < width - 1)))// top middle section
                    {

                        if (simulationMode == 'D' || simulationMode == 'd') {


                            // same row
                            if (currentGrid[row][col-1] == 'X')
                                 aliveLiveCnt++;
                            if (currentGrid[row][col+1] == 'X')
                                 aliveLiveCnt++;

                            //next row
                            if (currentGrid[row+1][col-1] == 'X')
                                aliveLiveCnt++;
                            if (currentGrid[row+1][col] == 'X')
                                aliveLiveCnt++;
                             if (currentGrid[row+1][col+1] == 'X')
                                aliveLiveCnt++;

                              // horizontally wrapped
                             if (currentGrid[height -1][col-1] == 'X')
                                 aliveLiveCnt++;
                             if (currentGrid[height -1][col] == 'X')
                                 aliveLiveCnt++;
                             if (currentGrid[height -1][col+1] == 'X')
                                 aliveLiveCnt++;

                        }

                        if (simulationMode == 'M' || simulationMode == 'm') {

                        }

                    }

                    if ((row == 0) && (col == width - 1)) // top right corner
                    {

                        if (simulationMode == 'D' || simulationMode == 'd') {

                              // adjucent  cells
                            if (currentGrid[row][col-1] == 'X') // same row , previous column
                                 aliveLiveCnt++;
                            if (currentGrid[row+1][col-1] == 'X') // diagonal
                                aliveLiveCnt++;
                            if (currentGrid[row+1][col] == 'X') // next row , same column
                                aliveLiveCnt++;

                            // horizontally wrapped
                             if (currentGrid[height -1][col] == 'X')
                                 aliveLiveCnt++;
                            if (currentGrid[height -1][col-1] == 'X')
                                aliveLiveCnt++;

                             // vertically wrapped

                            if (currentGrid[row][0] == 'X')
                                 aliveLiveCnt++;
                            if (currentGrid[row+1][0] == 'X')
                                aliveLiveCnt++;

                            // diagonal wrapped

                             if (currentGrid[0][width-1] == 'X')
                                aliveLiveCnt++;

                        }

                        if (simulationMode == 'M' || simulationMode == 'm') {

                              if (currentGrid[row][col] == 'X')
                                 aliveLiveCnt= aliveLiveCnt+3 ;



                        }

                    }

                    if (((row > 0) && (row < height - 1)) && (col == width - 1)) // right side middle
                    {

                        if (simulationMode == 'D' || simulationMode == 'd') {

                             // same column
                            if (currentGrid[row-1][width - 1] == 'X')
                                 aliveLiveCnt++;
                            if (currentGrid[row+1][width - 1] == 'X')
                                 aliveLiveCnt++;

                            //previuos column
                            if (currentGrid[row-1][width - 2] == 'X')
                                aliveLiveCnt++;
                            if (currentGrid[row][width - 2] == 'X')
                                aliveLiveCnt++;
                             if (currentGrid[row+1][width - 2] == 'X')
                                aliveLiveCnt++;

                              // vertical wrapped
                             if (currentGrid[row-1][0] == 'X')
                                 aliveLiveCnt++;
                             if (currentGrid[row][0] == 'X')
                                 aliveLiveCnt++;
                             if (currentGrid[row +1][0] == 'X')
                                 aliveLiveCnt++;



                        }

                        if (simulationMode == 'M' || simulationMode == 'm') {

                        }

                    }

                    if ((row == height - 1) && (col == width - 1)) // bottom right corner
                    {
                        if (simulationMode == 'D' || simulationMode == 'd') {

                             // adjucent  cells
                            if (currentGrid[row][col-1] == 'X') // same row , previous column
                                 aliveLiveCnt++;
                            if (currentGrid[row-1][col-1] == 'X') // diagonal
                                aliveLiveCnt++;
                            if (currentGrid[row-1][col] == 'X') // previous row , same column
                                aliveLiveCnt++;

                            // horizontally wrapped  -- 0 row
                             if (currentGrid[0][col] == 'X')
                                 aliveLiveCnt++;
                            if (currentGrid[0][col-1] == 'X')
                                aliveLiveCnt++;

                             // vertically wrapped -- last i.e height-1 row

                            if (currentGrid[row][col] == 'X')
                                 aliveLiveCnt++;
                            if (currentGrid[row][col-1] == 'X')
                                aliveLiveCnt++;

                            // diagonal wrapped

                             if (currentGrid[0][0] == 'X')
                                aliveLiveCnt++;

                        }

                        if (simulationMode == 'M' || simulationMode == 'm') {

                             if (currentGrid[row][col] == 'X')
                                 aliveLiveCnt= aliveLiveCnt+3 ;



                        }

                    }

                    if ((row == height - 1) && ((col < width - 1) && (col > 0))) // bottom portion
                    {
                        if (simulationMode == 'D' || simulationMode == 'd') {

                              // same row
                            if (currentGrid[row][col-1] == 'X')
                                 aliveLiveCnt++;
                            if (currentGrid[row][col+1] == 'X')
                                 aliveLiveCnt++;

                            //previous row
                            if (currentGrid[row-1][col-1] == 'X')
                                aliveLiveCnt++;
                            if (currentGrid[row-1][col] == 'X')
                                aliveLiveCnt++;
                             if (currentGrid[row-1][col+1] == 'X')
                                aliveLiveCnt++;

                              // horizontally wrapped --first i.e 0 row
                             if (currentGrid[0][col-1] == 'X')
                                 aliveLiveCnt++;
                             if (currentGrid[0][col] == 'X')
                                 aliveLiveCnt++;
                             if (currentGrid[0][col+1] == 'X')
                                 aliveLiveCnt++;

                        }

                        if (simulationMode == 'M' || simulationMode == 'm') {

                        }


                    }
                    if ((row == height - 1) && (col == 0)) // bottom left corner
                    {
                        if (simulationMode == 'D' || simulationMode == 'd') {

                             // adjacent  cells
                            if (currentGrid[row][col+1] == 'X') // same row , next column
                                 aliveLiveCnt++;
                            if (currentGrid[row-1][col-1] == 'X') // diagonal
                                aliveLiveCnt++;
                            if (currentGrid[row-1][col+1] == 'X') // previous row , same column
                                aliveLiveCnt++;

                            // horizontally wrapped
                             if (currentGrid[0][col] == 'X')
                                 aliveLiveCnt++;
                            if (currentGrid[0][col+1] == 'X')
                                aliveLiveCnt++;

                             // vertically wrapped

                            if (currentGrid[row][width-1] == 'X')
                                 aliveLiveCnt++;
                            if (currentGrid[row-1][width-1] == 'X')
                                aliveLiveCnt++;

                            // diagonally wrapped

                             if (currentGrid[0][width-1] == 'X')
                                aliveLiveCnt++;

                        }

                        if (simulationMode == 'M' || simulationMode == 'm') {

                          if (currentGrid[row][col] == 'X')
                                 aliveLiveCnt= aliveLiveCnt+3 ;
                        }

                    }

                    if (((row < height - 1) && (row > 0)) && (col == 0)) // left side middle
                    {

                        if (simulationMode == 'D' || simulationMode == 'd') {

                              // same column
                            if (currentGrid[row-1][col] == 'X')
                                 aliveLiveCnt++;
                            if (currentGrid[row+1][col] == 'X')
                                 aliveLiveCnt++;

                            //next column
                            if (currentGrid[row-1][col+1] == 'X')
                                aliveLiveCnt++;
                            if (currentGrid[row][col+1] == 'X')
                                aliveLiveCnt++;
                             if (currentGrid[row+1][col+1] == 'X')
                                aliveLiveCnt++;

                              // vertical wrapped -- last column
                             if (currentGrid[row-1][width-1] == 'X')
                                 aliveLiveCnt++;
                             if (currentGrid[row][width-1] == 'X')
                                 aliveLiveCnt++;
                             if (currentGrid[row +1][width-1] == 'X')
                                 aliveLiveCnt++;
                        }

                        if (simulationMode == 'M' || simulationMode == 'm') {

                        }

                    }

                }

            }  // boundary cells section end here
              // this section calculate neighbors for cells inside the grid boundaries
            else if ((row > 0 && row < height - 1) && (col > 0 || col < height - 1)) {


                if (currentGrid[row - 1][col - 1] == 'X') {
                    aliveLiveCnt++;
                }

                if (currentGrid[row - 1][col] == 'X') {
                    aliveLiveCnt++;
                }
                if (currentGrid[row - 1][col + 1] == 'X') {
                    aliveLiveCnt++;
                }

                if (currentGrid[row][col - 1] == 'X') {
                    aliveLiveCnt++;
                }

                if (currentGrid[row][col + 1] == 'X') {
                    aliveLiveCnt++;
                }

                if (currentGrid[row + 1][col - 1] == 'X') {
                    aliveLiveCnt++;
                }

                if (currentGrid[row + 1][col + 1] == 'X') {
                    aliveLiveCnt++;
                }
            }  // non boundary section end here


    return aliveLiveCnt ;
}
void Life::computeNextGeneration(char simulationMode) {

    /*/
        Rules:
        1.	A location that has one or fewer neighbors will be empty in the next generation.
        2.	A location with two neighbors remains stable.
        3.	A location with three neighbors will contain r cell in the next generation.
        4.	A location with four or more neighbors will be empty in the next generation .
/*/

    //declare and initialize future grid

    char** futureGrid = new char*[height];
    for (int i = 0; i < height; ++i)
        futureGrid[i] = new char[width];


    // Loop through every cell
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            int aliveLiveCnt = 0;

              aliveLiveCnt = getAliveNeighborCount(row,col,simulationMode) ;
            // the below section populates new Life as per rules .

            futureGrid[row][col] = '-'; // initially fill it with dash

            if (currentGrid[row][col] == 'X' && aliveLiveCnt < 1) //rule 1
            {
                futureGrid[row][col] = '-';
            } else if (currentGrid[row][col] == 'X' && (aliveLiveCnt == 2))//rule 2
            {
                futureGrid[row][col] = 'X';
            } else if ((currentGrid[row][col] == 'X' || currentGrid[row][col] == '-') && (aliveLiveCnt == 3)) //rule 3
            {
                futureGrid[row][col] = 'X';

            } else if (currentGrid[row][col] == 'X' && aliveLiveCnt >= 4) //rule 4
            {
                futureGrid[row][col] = '-';
            } else {
                futureGrid[row][col] = currentGrid[row][col];
            }

        } // for loop cols

    }  // for loop rows


    // test whether grid has stabilized , so you can exit  later
    stabilizes = true;
    empty = true;
    for (int s = 0; s < height; ++s) {

        for (int col = 0; col < width; ++col) {

            if (futureGrid[s][col] == 'X') {
                empty = false;
            }

            if (currentGrid[s][col] != futureGrid[s][col]) {
                stabilizes = false;

            }

        }
    }

    // this section will delete existing current grid and make future grid as currentGrid
    delete[] currentGrid;
    currentGrid = futureGrid;
}




/*
 *
 */
