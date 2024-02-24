//
// Created by Amir Nabiyev on 2/24/24.
//

#ifndef MATRIXREDUCTION_MATRIX_FUNCTIONS_H
#define MATRIXREDUCTION_MATRIX_FUNCTIONS_H

#include <vector>
using namespace std;

void printMatrix(int rows, int cols, vector<vector<double> > matrix);

void matrixReducer(vector<vector<double> > matrix);

vector<double> multiplyRow(double scalar, vector<double> row);

vector<double> addRows(vector<double> row1, vector<double> row2);

bool checkRREF(vector<vector<double> > matrix);

#endif //MATRIXREDUCTION_MATRIX_FUNCTIONS_H
