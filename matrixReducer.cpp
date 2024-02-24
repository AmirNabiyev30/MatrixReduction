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

    if (checkRREF(matrix))
    {
        cout << "This matrix is in Reduced Row-Echelon Form" << endl;
    }
    else
    {
        cout << "This matrix is not in Reduced Row-Echelon Form" << endl;
    }
    // Reduction Algorithm

    return 0;
}


