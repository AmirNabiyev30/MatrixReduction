#include <iostream>
#include <vector>
using namespace std;

void printMatrix(int rows, int cols, vector<vector<double> > matrix);

void matrixReducer(vector<vector<double> > matrix);

vector<double> multiplyRow(double scalar, vector<double> row);

vector<double> addRows(vector<double> row1 , vector<double> row2);

int main()
{
    // intilizing matrix
    int rows, cols;
    cout << "How many rows does the matrix have" << endl;
    cin >> rows;
    cout << "How many columns does the matrix have" << endl;
    cin >> cols;
    vector<double> row(cols, 0);
    vector<vector<double> > matrix(rows, row);
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

    matrix.at(0) = multiplyRow(.5, matrix.at(0));

    printMatrix(rows, cols, matrix);

    matrix.at(1) = addRows(matrix.at(0),multiplyRow(1,matrix.at(1)));

    printMatrix(rows, cols, matrix);
    // Reduction Algorithm

    return 0;
}

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
    cout << endl<< endl;
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

vector<double> multiplyRow(double scalar, vector<double> row)
{
    cout << "Mutliply row  by " << scalar << endl;

    for (int i = 0; i < row.size(); i++)
    {
        row.at(i) *= scalar;
    }

    return row;
}

vector<double> addRows(vector<double> row1 , vector<double> row2){
     vector<double> sumRow;
     for(int i =  0; i< row1.size();i++){
        sumRow.push_back(row1.at(i) + row2.at(i));
     }
     return sumRow;
}