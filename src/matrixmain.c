#include "matrix.h"

int main()
{
	_Bool** table;
	int choice, rows, cols, c, x, r;

	do
	{
		x = 0;
		printf("\nYou are going to generate 2 random matrices in order to test each functions in the program.\n\n");
		printf("Please enter the number size of the first matrix m1 : \n");
		printf("Rows : ");
		scanf("%i", &rows);
		printf("Columns : ");
		scanf("%i", &cols);
		table = createTable(rows, cols);
		Matrix m1;
		m1 = newMatrix(table, rows, cols);
		printf("Matrix m1 :\n\n");
		printMatrix(m1);

		printf("Please enter the number size of the first matrix m2 : \n");
		printf("Rows : ");
		scanf("%i", &rows);
		printf("Columns : ");
		scanf("%i", &cols);
		table = createTable(rows, cols);
		Matrix m2;
		m2 = newMatrix(table, rows, cols);
		printf("Matrix m2 :\n\n");
		printMatrix(m2);
	
		Matrix m3;

		while(x == 0)
		{
			printf("\n\n		- Matrices and Cellular Automata -\n\n");
			printf("-1- To check if a column is empty in m1\n");
			printf("-2- To check if a row is empty in m1\n");
			printf("-3- To summurize two matrices\n");
			printf("-4- To multiply two matrices\n");
			printf("-5- To compute a new matrix using an operator AND between columns of m1\n");
			printf("-6- To compute a new matrix using an operator OR between columns of m1\n");
			printf("-7- To compute a new matrix using an operator AND between rows of m1\n");
			printf("-8- To compute a new matrix using an operator OR between rows of m1\n");
			printf("-9- To check if the matrix m1 is empty\n");
			printf("-10- To check if m1 is a square matrix\n");
			printf("-11- To apply a rule a certain number of times on m1\n");
			printf("-12- To modify the random matrices\n");
			printf("-13- To leave the program\n\n");

			scanf("%i", &choice);

			switch(choice)
			{
				case 1 :
					printf("\n\nPlease enter the index of the column you want to check : ");
					scanf("%i", &c);
					if(isColumnEmpty(m1, c))
					{
						printf("\nThe column with index %i is empty\n\n", c);
						sleep(1);
					}
					else
					{
						printf("\nThe column with index %i isnt empty\n\n", c);
						sleep(1);
					}
					break;
				case 2 :
					printf("\n\nPlease enter the index of the row you want to check : ");
					scanf("%i", &c);
					if(isRowEmpty(m1, c))
					{
						printf("\nThe row with index %i is empty\n\n", c);
						sleep(1);
					}
					else
					{
						printf("\nThe row with index %i isnt empty\n\n", c);
						sleep(1);
					}
					break;
				case 3 :
					printf("This function will return the sum between m1 and m2\n\n");
					printf("Matrix m1 :\n\n");
					printMatrix(m1);
					printf("\n\nMatrix m2 :\n\n");
					printMatrix(m2);
					m3 = sumMatrix(m1, m2);
					printf("\nThe sum between m1 and m2 is :\n(if the two matrix m1 and m2 havent the same size, the result that will be returned is m1)\n\n");
					printMatrix(m3);
					freeMatrix(m3);
					sleep(1);
					break;
				case 4 :
					printf("This function will return the multiplication between m1 and m2\n\n");
					printf("Matrix m1 :\n\n");
					printMatrix(m1);
					printf("\n\nMatrix m2 :\n\n");
					printMatrix(m2);
					m3 = mulMatrix(m1, m2);
					printf("\nThe multiplication between m1 and m2 is :\n(if the two matrix m1 and m2 havent the same size, the result that will be returned is m1)\n\n");
					printMatrix(m3);
					freeMatrix(m3);
					sleep(1);
					break;
				case 5 :
					printf("Matrix m1 :\n\n");
					printMatrix(m1);
					m3 = andColSequenceOnMatrix(m1);
					printf("\nThe new matrix returned :\n\n");
					printMatrix(m3);
					freeMatrix(m3);
					sleep(1);
					break;
				case 6 :
					printf("Matrix m1 :\n\n");
					printMatrix(m1);
					m3 = orColSequenceOnMatrix(m1);
					printf("\nThe new matrix returned :\n\n");
					printMatrix(m3);
					freeMatrix(m3);
					sleep(1);
					break;
				case 7 :
					printf("Matrix m1 :\n\n");
					printMatrix(m1);
					m3 = andRowSequenceOnMatrix(m1);
					printf("\nThe new matrix returned :\n\n");
					printMatrix(m3);
					freeMatrix(m3);
					sleep(1);
					break;
				case 8 :
					printf("Matrix m1 :\n\n");
					printMatrix(m1);
					m3 = orRowSequenceOnMatrix(m1);
					printf("\nThe new matrix returned :\n\n");
					printMatrix(m3);
					freeMatrix(m3);
					sleep(1);
					break;
				case 9 :
					printf("Matrix m1 :\n\n");
					printMatrix(m1);
					if(isMatrixEmpty(m1))
					{
						printf("\nThe matrix m1 is empty.\n\n");
					}
					else
					{
						printf("\nThe matrix m1 isn't empty.\n\n");
					}
					sleep(1);
					break;
				case 10 :
					printf("Matrix m1 :\n\n");
					printMatrix(m1);
					if(isMatrixSquare(m1))
					{
						printf("\nThe matrix m1 is a square matrix.\n\n");
					}
					else
					{
						printf("\nThe matrix m1 isn't a square matrix.\n\n");
					}
					sleep(1);
					break;
				case 11 : 
					printf("\nFirst, you will have to choose the rule ID you want to apply on matrix m1 that will be modified.\n");
					printf("Rule ID : ");
					scanf("%i", &r);
					printf("Choose now the number of time you want to apply the rule on m1 : ");
					scanf("%i", &c);
					printf("Matrix m1 :\n\n");
					printMatrix(m1);
					printf("Matrix m1 modified :\n\n");
					m1 = applyRule(m1, r, c);
					printMatrix(m1);
					break;
				case 12 : x = 1;
					break;
				case 13 : x = 2;
					break;
				default : printf("Please enter a number between 1 and 11\n\n");
					sleep(1);
			}
		}

		freeMatrix(m1);
		freeMatrix(m2);
	}
	while(x != 2);
	return 0;
}
