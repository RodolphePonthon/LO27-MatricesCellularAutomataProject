#ifndef __H_PROJECT__
#define __H_PROJECT__

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

/* Structs: */
typedef struct cellElement
{
	int rowIndex;
	int colIndex;
	_Bool value;
	struct cellElement* nextCol;
	struct cellElement* nextRow;
} cellElement;

typedef struct colElement
{
	int colN;
	cellElement* col;
	struct colElement* prevCol;
	struct colElement* nextCol;
} colElement;

typedef struct rowElement
{
	int rowN;
	cellElement* row;
	struct rowElement* prevRow;
	struct rowElement* nextRow;
} rowElement;

typedef struct Matrix
{
	int colCount;
	int  rowCount;
	colElement* cols;
	rowElement* rows;
} Matrix;


/* Functions:*/

/*
 *This function generates a random array and converts it into a double pointer
 *@param rows : number of rows in the new array
 *@param cols : number of cols in the new array
 *@return : a double pointer
*/
_Bool** createTable(int rows, int cols);


/*
 *This function builds a new Matrix from its array-based representation
 *@param table : a 2 dimensional array used to build the matrix
 *@return : the matrix
*/
Matrix newMatrix(_Bool** table, int rows, int cols);


/*
 *This function builds a new Matrix filled with 0
 *@param rows : number of rows in the new matrix
 *@param cols : number of cols in the new matrix
 *@return : the new matrix, filled with 0
*/
Matrix createAndAllocateMatrix(int rows, int cols);


/*
 *This function prints the matrix on the console
*/
void printMatrix(Matrix m);


/*
 *This function checks if the matrix is empty or not
 *@param m : the matrix 
 *@return : true if the specified Matrix is empty, false otherwise
*/
_Bool isMatrixEmpty(Matrix m);


/*
 *This function checks if a specified colum of the matrix is empty or not
 *@param m : the matrix 
 *@param nCol : the column to check
 *@return : true if the specified column is empty, false otherwise
*/
_Bool isColumnEmpty(Matrix m, int nCol);


/*
 *This function checks if a specified row of the matrix is empty or not
 *@param m : the matrix 
 *@param nRow : the row to check
 *@return : true if the specified row is empty, false otherwise
*/
_Bool isRowEmpty(Matrix m, int nRow);


/*
 *This function checks if the matrix is square or not
 *@param m : the matrix
 *@return : true if the specified Matrix is square, false otherwise
*/
_Bool isMatrixSquare(Matrix m);


/*
 *This function checks if two matrix are equal or not
 *@param m1 : the first matrix 
 *@param m2 : the second matrix 
 *@return : true if the two specified Matrix are equals, false otherwise
*/
_Bool equalsMatrix(Matrix m1, Matrix m2);


/*
 *This function computes a new matrix using the operator OR between two others
 *@param m1 : the first matrix
 *@param m2 : the second matrix
 *@return : the new matrix
*/
Matrix sumMatrix(Matrix m1, Matrix m2);


/*
 *This function computes a new matrix using the operator AND between two others
 *@param m1 : the first matrix
 *@param m2 : the second matrix
 *@return : the new matrix
*/
Matrix mulMatrix(Matrix m1, Matrix m2);


/*
 *This function returns a new matrix computed using an operator AND between columns of a given matrix
 *@param m : the initial matrix
 *@return : the matrix newMatrix
*/
Matrix andColSequenceOnMatrix(Matrix m);


/*
 *This function returns a new matrix computed using an operator OR between columns of a given matrix
 *@param m : the initial matrix
 *@return : the matrix newMatrix
*/
Matrix orColSequenceOnMatrix(Matrix m);


/*
 *This function returns a new matrix computed using an operator AND between rows of a given matrix
 *@param m : the initial matrix
 *@return : the matrix newMatrix
*/
Matrix andRowSequenceOnMatrix(Matrix m);


/*
 *This function returns a new matrix computed using an operator OR between rows of a given matrix
 *@param m : the initial matrix
 *@return : the matrix newMatrix
*/
Matrix orRowSequenceOnMatrix(Matrix m);


/*
 *This function returns the modified matrix of an input matrix on which the function applies rule(s) a certain number of time
 *It decompose the non-fundamental Rules in fundamental rules too
 *@param m : the initial matrix
 *@param ruleID : the rule that will be applied on the initial matrix
 *@param times : the number of time the rule will be applied on the initial matrix
 *@return : the matrix m modified with rule(s) applied on it
*/
Matrix applyRule(Matrix m, int ruleID, int times);


int power(int x, int n);


/*
 *This function copies a matrix in an other one
 *@param m1 : the matrix that will receive the copy of m2
 *@param m2 : the matrix that will be copied in m1
 *@return : the matrix m1 (the copy of m2)
*/
Matrix copyMatrix(Matrix m1, Matrix m2);


/*
 *This funtion computes a XOR operation between two initial matrix
 *@param m1 : the first matrix (to be modified)
 *@param m2 : the second matrix
 **@return : the matrix modified with the XOR operation
*/
Matrix xorMatrix(Matrix m1, Matrix m2);


/*
 *This function modifies a matrix with applying the fundamental rule 2 on it (direction of translation : Left)
 *@param m : the initial matrix
 *@return : the matrix m modified
*/
Matrix rule2(Matrix m);


/*
 *This function modifies a matrix with applying the fundamental rule 8 on it (direction of translation : Top)
 *@param m : the initial matrix
 *@return : the matrix m modified
*/
Matrix rule8(Matrix m);


/*
 *This function modifies a matrix with applying the fundamental rule 32 on it (direction of translation : Right)
 *@param m : the initial matrix
 *@return : the matrix m modified
*/
Matrix rule32(Matrix m);


/*
 *This function modifies a matrix with applying the fundamental rule 128 on it (direction of translation : Bottom)
 *@param m : the initial matrix
 *@return : the matrix m modified
*/
Matrix rule128(Matrix m);


/*
 *This function "compute" each cases (8 cases) of fundamental rules
 *@param m : the initial matrix
 *@return : the matrix m modified
*/
Matrix matRule(Matrix m, int ruleID);


/*
 *This function free the memory allocated on a given matrix
 *@param m : the matrix
*/
void freeMatrix(Matrix m);


#endif
