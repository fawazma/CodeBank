#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <cstring>
#include <math.h>
#include <fstream>
#include <iomanip>

#include "Life.h"

using namespace std;

int main(int argc, char** argv) {

    Life w;

    char userChoice, simulationMode = 'C', pause = 'Y';
    string mapFile, outputFile;
    int height = 0, width = 0;
    double density;
    ifstream ifs;

    cout << "  ---------------- THE GAME OF LIFE ----------------\n" << endl;

    cout << "Do you wish to start with a random configuration (R/r), or specify a flat file configuration (F/f)  ?? Type R or F : ";
    userChoice = getchar();
    if (userChoice == 'F' || userChoice == 'f') {
        cout << "\nPlease do enter the name of map file ..(example : map.txt) : ";
        cin>>mapFile;
        ifs.open(mapFile.c_str(), ios_base::in);

        if (ifs.fail()) {
            cout << "Failed to open map file ,  The program will end." << "\n";
            exit(1);
        }
        cout << endl << "Populating the world from the map file ....... " << endl;

        w.populateFromFile(mapFile);


    } else if (userChoice == 'R' || userChoice == 'r') {
        cout << "Please do enter the dimensions (height x width) of the game" << endl;
        cout << "height :";
        cin>>height;
        cout << "width :";
        cin>>width;

        cout << "\nPlease enter the desired population density in the form of a decimal(between 0 and 1): ";
        cin>>density;
        if (density <= 0 && density > 1) {
            cout << "Invalid density value , it must be  >0 and <=1" << "\n";
            exit(1);
        }


        cout << endl << "Populating the world with random values  ....... " << endl;
        w.randomizeCells(height, width, density);
    } else {
        cout << "Invalid choice ,  The program will end." << "\n";
        exit(1);
    }

    w.printToConsole();

    cout << "\nWhich mode would you like: Classic, Doughnut, or Mirror? type C, D, or M: ";
    cin>>simulationMode;

    cout << "\nWant a brief pause between generations ?? Type Y or N :  ";
    cin>>pause;

    if (pause == 'y' || pause == 'Y') {

        cout << "You need to press “Enter” to display the next generation !" << endl;

    } else {
        cout << endl << "Please provide the file name to store the generations : ";
        cin>>outputFile;
    }



    do {

        if (w.isEmpty() ) {
            cout << "The simulation should halt because it is EMPTY , please press “enter” to exit the program";
           cin.ignore();
           cin.get();
            exit(1);
        }
        else if (w.isStabilized())
        {
            cout << "The simulation should halt because it is STABILIZED, please press “enter” to exit the program";
             cin.ignore();
            cin.get();
            exit(1);
        }

        w.computeNextGeneration(simulationMode);

        if (pause == 'y' || pause == 'Y') {

            w.printToConsole();
            cout << "Press “Enter” to display the next generation !" << endl;
              cin.ignore();
            cin.get();
        } else {
            w.printToFile(outputFile);
        }

    } while (true);

    return 0;
}
