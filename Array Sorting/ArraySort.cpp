#include <stdio.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

void quickSort(double array[], int left, int right);
int partition(double array[], int left, int right);
void swap(double array[], int a, int b);
void insertionSort(double array[], int numElements);
void bubleSort(double array[], int numElements);
void gnomeSort(double array[], int numElements);

int main(int argc, char **argv) {

    // CHECK THAT THERE IS ONLY ONE COMMAND LINE ARGUMENT
    if (argc < 2) {
        cout << "\n*** Please give a single file name in the command line. ***\n\n<<< Exiting Program >>>\n" << endl;
        exit(-1);
    }

    string fileName = argv[1];

    ifstream inputFile;
    inputFile.open(fileName.c_str());

    if (!inputFile.is_open()) {
        cout << "\n*** Error loading file: File does not exist in current directory. ***\n\n<<< Exiting Program >>>\n" << endl;
        exit(-1);
    }

    clock_t timeStart;
    clock_t timeEnd;

    int numElements;
    string line;
    double value;

    double *quickSortArr = new double[numElements];
    double *insertSortArr = new double[numElements];
    double *bubleSortArr = new double[numElements];
    double *gnomeSortArr = new double[numElements];

    getline(inputFile, line);
    numElements = stoi(line);

    // POPULATE ARRAYS
    for (int i = 0; i < numElements; ++i) {

        getline(inputFile, line);

        // CONVERT LINE FROM FILE TO A DOUBLE
        value = stod(line);

        quickSortArr[i] = value;
        insertSortArr[i] = value;
        bubleSortArr[i] = value;
        gnomeSortArr[i] = value;
    }

    inputFile.close();

    cout << "\n     - SORTING -\n* ----------------- *\n";

    // - QUICK SORT - //
    timeStart = clock();
    quickSort(quickSortArr, 0, numElements - 1);
    timeEnd = clock();
    printf("\nQuickSort took %.2fms to sort %d numbers.\n", (float (timeEnd - timeStart) / CLOCKS_PER_SEC) *1000, numElements);

    // - INSERTION SORT - //
    timeStart = clock();
    insertionSort(insertSortArr, numElements);
    timeEnd = clock();

    printf("\nInsertionSort took %.2fms to sort %d numbers.\n",
            (float (timeEnd - timeStart) / CLOCKS_PER_SEC) *1000, numElements);

    // - BUBBLE SORT - //
    timeStart = clock();
    bubleSort(bubleSortArr, numElements);
    timeEnd = clock();

    printf("\nBubbleSort took %.2fms to sort %d numbers.\n",
            (float (timeEnd - timeStart) / CLOCKS_PER_SEC) *1000, numElements);

    // - GNOME SORT - //
    timeStart = clock();
    gnomeSort(gnomeSortArr, numElements);
    timeEnd = clock();

    printf("\nGnomeSort took %.2fms to sort %d numbers.\n\n",
            (float (timeEnd - timeStart) / CLOCKS_PER_SEC) *1000, numElements);


    delete[] quickSortArr;
    delete[] insertSortArr;
    delete[] bubleSortArr;
    delete[] gnomeSortArr;

}

void quickSort(double array[], int left, int right) {
    int index = partition(array, left, right);

    // SORT LEFT HALF
    if (left < index - 1) {
        quickSort(array, left, index - 1);
    }

    // SORT RIGHT HALF
    if (index < right) {
        quickSort(array, index, right);
    }
}

int partition(double array[], int left, int right) {
    // CHOOSE MIDDLE VALUE AS PIVOT
    int pivot = array[(left + right) / 2];

    while (left <= right) {
        // FIND ELEMENTS ON LEFT THAT BELONG ON RIGHT
        while (array[left] < pivot) {
            left++;
        }

        // FIND ELEMENT ON RIGHT THAT BELONGS ON LEFT
        while (array[right] > pivot) {
            right--;
        }

        // SWAP ELEMENTS AND MOVE LEFT & RIGHT INDICES
        if (left <= right) {
            swap(array, left, right);

            left++;
            right--;
        }
    }

    return left;
}

void swap(double array[], int a, int b) {
    double temp = array[a];
    array[a] = array[b];
    array[b] = temp;
}

void insertionSort(double array[], int numElements) {
    for (int j = 1; j < numElements; ++j) // MARKER
    {
        double temp = array[j]; // STORE MARKED ITEM
        int k = j; // WHERE TO START SHIFTING
        while (k > 0 && array[k - 1] >= temp) // WHILE ELEMENT TO LEFT IS LARGER, SHIFT
        {
            array[k] = array[k - 1];
            --k;
        }
        array[k] = temp; // PLACE MARKED ITEM IN CORRECT SPOT
    }
}

void bubleSort(double array[], int numElements) {

    //declare some more variables and modify the code to make it work
    int i, j, t;
    for (i = 0; i < numElements - 1; i++)
        // Last i elements are already in place
        for (j = 0; j < numElements - i - 1; j++)
            if (array[j] > array[j + 1]) {
                t = array[j];
                array[j] = array[j + 1];
                array[j + 1] = t;
            }
};

// A function to sort the algorithm using gnome sort

void gnomeSort(double array[], int numElements) {
    int index = 0;

    while (index < numElements) {
        if (index == 0)
            index++;
        if (array[index] >= array[index - 1])
            index++;
        else {
            int temp = 0;
            temp = array[index];
            array[index] = array[index - 1];
            array[index - 1] = temp;
            index--;
        }
    }
    return;
}
