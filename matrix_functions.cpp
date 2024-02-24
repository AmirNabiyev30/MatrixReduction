//
// Created by Amir Nabiyev on 2/24/24.
//
#include "matrix_functions.h"
#include <vector>
#include <iostream>
using namespace std;

void printMatrix(int rows, int cols, vector<vector<double> > matrix)
{

    cout << endl
         << "Matrix:" << endl
         << endl;
    cout << "     ";
    for (int i = 0; i < cols; i++)
    {
        cout << i + 1 << "  ";
    }
    cout << endl
         << endl;
    for (int i = 0; i < rows; i++)
    {
        cout << i + 1 << "    ";
        for (int j = 0; j < cols; j++)
        {
            cout << matrix.at(i).at(j) << "  ";
        }
        cout << endl;
    }
    cout << endl;
}

void matrixReducer(vector<vector<double> > matrix) { cout << "this thing works"; }

// row operations
vector<double> multiplyRow(double scalar, vector<double> row)
{
    cout << "Multiply row  by " << scalar << endl;

    for (double & i : row)
    {
        i *= scalar;
    }

    return row;
}

vector<double> addRows(vector<double> row1, vector<double> row2)
{
    vector<double> sumRow(row1.size());
    for (int i = 0; i < row1.size(); i++)
    {
        sumRow.push_back(row1.at(i) + row2.at(i));
    }
    return sumRow;
}

bool checkRREF(vector<vector<double> > matrix)
{
    /*
    RULES FOR A MATRICE TO BE IN RREF
        1.The first non-zero entry has to be all 1's
        2. The leading 1 in the second row or beyond is to the right of the leading 1 just above
        3.Any rows containing only 0's at the bottom
    */

    // track leading 1's column of current row
    int leading1Pos = -1;
    // track leading 1's column of previous iteration of row
    int prevLeading1Pos = -1;
    vector<double> currRow;
    for (int i = 0; i < matrix.size(); i++) {

        currRow = matrix.at(i);
        // find leading 1 of that row
        for (int j = 0; j < currRow.size(); j++) {
            if (currRow.at(j) == 1) {
                leading1Pos = j;
                if (leading1Pos < prevLeading1Pos) {
                    cout << "Found leading 1 before previous leading 1" << endl;
                    return false;
                }
                break;
            } else if (currRow.at(j) != 0) {
                return false;
            }
        }



        //the position of leading 1 can't be the same position as the previous leading 1 and
        // can't be negative(1 not found)
        if (leading1Pos != prevLeading1Pos && leading1Pos != -1) {
            // checks if the column above is zero
            for (int z = i + 1; z < matrix.size(); z++) {
                if (matrix.at(z).at(leading1Pos) != 0) {
                    cout << "The values above the leading 1 at position: " << leading1Pos << " are not zero" << endl;
                    return false;
                }
            }

            //checks if column above is zero

            for (int j = i - 1; j >= 0; j--) {

                if (matrix.at(j).at(leading1Pos) != 0) {
                    cout << "The values below the leading 1 at position: " << leading1Pos << " are not zero" << endl;
                    return false;
                }
            }
        }
            //if no leading 1 is found make sure row is all zero's
        else {
            for (double z : currRow) {
                if (z != 0) {
                    cout << "The entire row is not zero's" << endl;
                    return false;
                }
            }
        }
        //setting previous leading 1 pos as the current one
        prevLeading1Pos = leading1Pos;

    }
    return true;
}
