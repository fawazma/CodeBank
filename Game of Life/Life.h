#ifndef Life_H
#define Life_H

#include <string>

class Life {

public  :
     Life();
     Life(int, int);
       // copy constructor
     Life(const Life& other) ;

    // overloaded assignment operator
   // We can copy into differently-sized square list, as long as it is large
   // enough to hold all of the actual stored data.
    const Life& operator=(const Life& rhs) ;


     ~Life();
     void randomizeCells(int h , int w , double density );
     void populateFromFile(std::string filename) ;
     void printToConsole() ;
     void printToFile(std::string filename) ;
     void computeNextGeneration(char) ;
     int getAliveNeighborCount(int row , int col , char simulationMode) ;

     bool isEmpty() ;
     bool isStabilized() ;

private :
    int height , width , generationCount ;
    char ** currentGrid ;

    bool stabilizes , empty ;


};



#endif
