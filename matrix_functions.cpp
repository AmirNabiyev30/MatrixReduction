//
// Created by Amir Nabiyev on 2/24/24.
//
#include "matrix_functions.h"
#include <vector>
#include <iostream>
#include <iomanip>
using namespace std;

void printMatrix(int rows, int cols, vector<vector<double> > matrix)
{
    //putting decimal points to 2 values
    cout<<fixed<<setprecision(1);

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

//recursive function call
vector<vector<double>> matrixReducer(vector<vector<double> > matrix, vector<double> (*addRows)(vector<double> row1, vector<double> row2) ,
     vector<double> (*multiplyRow)(double scalar, vector<double> row),
             bool (*checkRREF)(vector<vector<double> > matrix), int currRow,int currCol,
             void (*printMatrix)(int rows,int cols,vector<vector<double> > matrix)){

    //defining number of and number of columns for easy use in recursive algo(saving time)
    int numRows = matrix.size();
    int numCols = matrix.at(0).size();

    //if the matrix is in reduced row-echelon form the recursion will end


    //if rows and cols are not in the bounds
    if(currRow >=numRows){
        cout<<"we are out of bounds in the matrix"<<endl;
        //looping through matrix to find a non-zero leading 1
        for(int i = 0;i<numRows;i++){
            for(int j = 0;j<numCols;j++){
                if(matrix.at(i).at(j) != 0){
                    //if the first number is 1 then break the loop and continue going down the rows
                    // if the first number is non-zero and not 1  then make numbers above and below zero and divide the row by zero
                    if(matrix.at(i).at(j)  != 1 ) {
                        cout<<"WE FOUND A NONZERO 1 AT POSITION: ("<<i<<", "<<j<<")"<<endl;
                        matrix.at(i) = multiplyRow(1 / matrix.at(i).at(j), matrix.at(i));
                        vector<double> currentRow = matrix.at(i);
                        //eliminating values lower the current value
                        for (int row = i + 1; row < matrix.size(); row++) {
                            matrix.at(row) = addRows(matrix.at(row),
                                                   multiplyRow(-1 * matrix.at(row).at(j), currentRow));
                        }
                        //eliminating all values above than the current value
                        for (int row = i - 1; row > -1; row--) {
                            matrix.at(row) = addRows(matrix.at(row),
                                                   multiplyRow(-1 * matrix.at(row).at(j), currentRow));
                        }
                        break;
                    }
                    else{
                        break;
                    }
                }

            }
        }
    }

    if(checkRREF(matrix)){
        return matrix;
    }

    printMatrix(numRows ,numCols,matrix);

    vector<double> currentRow = matrix.at(currRow);
    double currentValue = currentRow.at(currCol);
    if(currentValue != 1 && currentValue != 0){
        //dividing row by the currentValue  value
        matrix.at(currRow) = multiplyRow(1/currentValue,matrix.at(currRow));
        currentRow = matrix.at(currRow);
        //eliminating the values under the current values by making them go to zero
        for(int i = currRow+1; i < matrix.size();i++){
            matrix.at(i) = addRows(matrix.at(i),multiplyRow(-1*matrix.at(i).at(currCol),currentRow));
        }
        //eliminating all values over the current value
        for(int i = currRow-1 ;i>-1;i--){
            matrix.at(i) = addRows(matrix.at(i),multiplyRow(-1*matrix.at(i).at(currCol),currentRow));
        }
    }
    else if( currentValue == 1){
        //ELIMINATING ALL VALUES ABOVE AND UNDER THAT VALUE
        //eliminating values below the current value
        for(int i = currRow+1; i < matrix.size();i++){
            matrix.at(i) = addRows(matrix.at(i),multiplyRow(-1*matrix.at(i).at(currCol),currentRow));
        }
        //eliminating all values over the current value
        for(int i = currRow-1 ;i>-1;i--){
            matrix.at(i) = addRows(matrix.at(i),multiplyRow(-1*matrix.at(i).at(currCol),currentRow));
        }

    }









        //recursive call
        return matrixReducer(matrix,addRows,multiplyRow,checkRREF,currRow+1,currCol+1,printMatrix);

}

// row operations
vector<double> multiplyRow(double scalar, vector<double> row)
{
    cout << "Multiply row (";
    for(int  i = 0;i<row.size();i++){
        cout<<row.at(i);
        if(i!=row.size()-1){
            cout<<",";
        }
    }

    cout <<") by " << scalar << endl;

    for(double & i : row)
    {
        i *=scalar;
    }

    return row;
}

vector<double> addRows(vector<double> row1, vector<double> row2)
{
    cout<< "Adding (";
    for(int  i = 0;i<row2.size();i++){
        cout<<row2.at(i);
        if(i!=row2.size()-1){
            cout<<",";
        }
    }
    cout<<") to (";
    for(int  i = 0;i<row1.size();i++){
        cout<<row1.at(i);
        if(i!=row1.size()-1){
            cout<<",";
        }
    }
    cout<<") "<<endl;

    vector<double> sumRow;
    sumRow.reserve(row1.size());
for (int i = 0; i < row1.size(); i++)
    {
        sumRow.push_back(row1.at(i) + row2.at(i));
    }
    return sumRow;
}

//Checks if the matrix is in RREF
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
