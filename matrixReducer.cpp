#include <iostream>
#include <vector>
#include "matrix_functions.h"
using namespace std;



int main()
{
    // initializing matrix
    int rows, cols;
    cout << "How many rows does the matrix have" << endl;
    cin >> rows;
    cout << "How many columns does the matrix have" << endl;
    cin >> cols;
    vector<double> initialRow(cols, 0);
    vector<vector<double> > matrix(rows, initialRow);
    double input;
    cout << "Enter the Values for the matrix" << endl;

    for (int row = 0; row < rows; row++)
    {
        cout << "Enter the entries for row " << row << endl;
        for (int col = 0; col < cols; col++)
        {
            cin >> input;
            matrix.at(row).at(col) = input;
        }
    }

    // Prints Matrix
    printMatrix(rows, cols, matrix);


    //moves all zero rows to the bottom of the matrix
    bool allZeroRow;
    for(int i = 0 ;i<rows;i++){
        allZeroRow = true;
        if(matrix.at(i).at(0) == 0){
            for(int j = 1;j<cols;j++){
                if(matrix.at(i).at(j) != 0){
                    allZeroRow = false;
                }
            }
            if(allZeroRow && i < rows-1){

                vector<double> temp = matrix.at(i+1);
                matrix.at(i+1) = matrix.at(i);
                matrix.at(i) = temp;
            }
        }
    }


    // Reduction Algorithm
    matrix = matrixReducer(matrix,&addRows,&multiplyRow,&checkRREF,0,0,&printMatrix);

    printMatrix(rows, cols, matrix);

    return 0;
}


