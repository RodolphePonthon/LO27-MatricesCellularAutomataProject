#include "matrix.h"

_Bool** createTable(int rows, int cols)
{

	_Bool** table = (_Bool**)malloc(rows*sizeof(_Bool*));
	if (rows<1 || cols <1) 
	{
		return table;
	}

	int i,j;
	srand(time(0));
	for(i=0;i<rows;i++)
	{
		table[i]=(_Bool*)malloc(cols*sizeof(_Bool));
		for(j=0;j<cols;j++)
		{
			table[i][j] = rand()%2;
		}
	}
	return table;
}

Matrix newMatrix(_Bool** table, int rows, int cols)
{

	Matrix matrix;
	matrix = createAndAllocateMatrix(rows, cols);

	if (matrix.cols == NULL)
	{
		return matrix;
	}

	int i=0,j=0;
	rowElement* rowElem;
	rowElem = matrix.rows;

	cellElement* cellElem;
	for (i=0;i<rows;i++)
	{	
		cellElem = rowElem->row;
		for (j=0;j<cols;j++)
		{
			cellElem->value = table[i][j];
			cellElem = cellElem->nextCol;
		}
		rowElem = rowElem->nextRow;
	}

	return matrix;
}

Matrix createAndAllocateMatrix(int rows, int cols)
{
	int i =0,j =0;
	Matrix* matrix = (Matrix*)malloc(sizeof(Matrix));
	matrix->colCount = cols;
	matrix->rowCount = rows;
	
	if (rows<1 || cols <1)
	{
		matrix->cols = NULL;
		matrix->rows = NULL;
	}
	else
	{
		/*Creation of the first colElement*/
		colElement* firstColElement = (colElement*)malloc(sizeof(colElement));

		matrix->cols = firstColElement;
	
		firstColElement->prevCol = NULL;
		firstColElement->colN = 0;
		firstColElement->nextCol = NULL;
	

		/*Creation of the first rowElement*/
		rowElement* firstRowElement = (rowElement*)malloc(sizeof(rowElement));

		matrix->rows = firstRowElement;
	
		firstRowElement->prevRow = NULL;
		firstRowElement->rowN = 0;
		firstRowElement->nextRow = NULL;


		rowElement* secRowElement;

		cellElement* newCell;
		cellElement* prevCell;
		for (i=0; i<rows; i++)
		{	
			//Creation of the first col
			newCell = (cellElement*)malloc(sizeof(cellElement));
			newCell->rowIndex = i;
			newCell->colIndex = 0;
			newCell->nextCol = NULL;
			newCell->nextRow = NULL;
			newCell->value = 0;
			if (i != 0)
			{
				prevCell->nextRow = newCell;
			}
			else
			{
				firstColElement->col = newCell;
			}
			prevCell = newCell;
		

			//Linking the rowElements with every cellElements
			firstRowElement->row = newCell;
			if (i+1<rows)
			{
				secRowElement = (rowElement*)malloc(sizeof(rowElement));
				secRowElement->prevRow = firstRowElement;
				firstRowElement->nextRow = secRowElement;
				secRowElement->rowN = i+1;
				secRowElement->nextRow = NULL;
				firstRowElement = secRowElement;
			}
		}

		cellElement* firstCells;
		colElement* secColElement;
		for (j=1; j<cols; j++)
		{	
			//Creation of the other cells and linking them with the previous col cells'
			secColElement = (colElement*)malloc(sizeof(colElement));
			secColElement->prevCol = firstColElement;
			firstColElement->nextCol = secColElement;
			secColElement->colN = j;
			secColElement->nextCol = NULL;

			firstCells = firstColElement->col;
			for (i=0; i<rows; i++)
			{	
				newCell = (cellElement*)malloc(sizeof(cellElement));
				newCell->rowIndex = i;
				newCell->colIndex = j;
				newCell->nextCol = NULL;
				newCell->nextRow = NULL;
				newCell->value = 0;
				if (i != 0)
				{
					prevCell->nextRow = newCell;
				}
				else
				{
					secColElement->col = newCell;
				}
				prevCell = newCell;
				firstCells->nextCol = newCell;
				if (i+1<rows)
				{
					firstCells = firstCells->nextRow;
				}
			}
			firstColElement = secColElement;
		}
	}
	return *matrix;
}

void printMatrix(Matrix m)
{
	if (isMatrixEmpty(m))
	{
		printf("\nEmpty matrix!\n");
	}
	else
	{
		rowElement* rowElem;
		rowElem = m.rows;

		cellElement* cellElem;
		while (rowElem != NULL)
		{	
			cellElem = rowElem->row;
			while(cellElem != NULL)
			{
				/*printf("%i ",cellElem->value);*/
				if (cellElem->value == 1)
				{
					printf("■ ");
				}
				else
				{
					printf("□ ");
				}

				cellElem = cellElem->nextCol;
			}
			printf("\n");
			rowElem = rowElem->nextRow;
		}
	}
	
}

_Bool isMatrixEmpty(Matrix m)
{
	
	if (m.cols == NULL)
	{
		return 1;
	}
	return 0;
}

_Bool isMatrixSquare(Matrix m)
{
	if(m.colCount == m.rowCount)
	{
		return 1;
	}
	return 0;
}

_Bool equalsMatrix(Matrix m1, Matrix m2)
{
	_Bool m1Empty = isMatrixEmpty(m1);
	_Bool m2Empty = isMatrixEmpty(m2);

	if (m1Empty && m2Empty)
	{
		return 1;
	}
	else if(m1Empty || m2Empty)
	{
		return 0;
	}
	else if((m1.colCount == m2.colCount) && (m1.rowCount == m2.rowCount))
	{
		rowElement* m1RowElem;
		m1RowElem = m1.rows;
		rowElement* m2RowElem;
		m2RowElem = m2.rows;

		cellElement* m1CellElem;
		cellElement* m2CellElem;

		while (m1RowElem != NULL)
		{	
			m1CellElem = m1RowElem->row;
			m2CellElem = m2RowElem->row;
			while(m1CellElem != NULL)
			{
				if((m1CellElem->value) != (m2CellElem->value))
				{
					return 0;
				}
				m1CellElem = m1CellElem->nextCol;
				m2CellElem = m2CellElem->nextCol;
			}
			m1RowElem = m1RowElem->nextRow;
			m2RowElem = m2RowElem->nextRow;
		}
		return 1;
	}
	return 0;
}

Matrix sumMatrix(Matrix m1, Matrix m2)
{
	_Bool m1Empty = isMatrixEmpty(m1);
	_Bool m2Empty = isMatrixEmpty(m2);

	if (m1Empty || m2Empty)
	{
		printf("\nImpossible to compute due to empty matrix\n");
		return m1;
	}
	else if((m1.colCount == m2.colCount) && (m1.rowCount == m2.rowCount))
	{
		Matrix matrix;
		matrix = createAndAllocateMatrix(m1.rowCount, m1.colCount);

		rowElement* m1RowElem;
		m1RowElem = m1.rows;
		rowElement* m2RowElem;
		m2RowElem = m2.rows;
		rowElement* mRowElem;
		mRowElem = matrix.rows;

		cellElement* m1CellElem;
		cellElement* m2CellElem;
		cellElement* mCellElem;

		while (m1RowElem != NULL)
		{	
			m1CellElem = m1RowElem->row;
			m2CellElem = m2RowElem->row;
			mCellElem = mRowElem->row;

			while(m1CellElem != NULL)
			{
				mCellElem->value = m1CellElem->value || m2CellElem->value;
				
				m1CellElem = m1CellElem->nextCol;
				m2CellElem = m2CellElem->nextCol;
				mCellElem = mCellElem->nextCol;
			}
			m1RowElem = m1RowElem->nextRow;
			m2RowElem = m2RowElem->nextRow;
			mRowElem = mRowElem->nextRow;
		}
		return matrix;
	}
	printf("\nThe two input matrix have not the same size\n");
	return m1;
}

Matrix mulMatrix(Matrix m1, Matrix m2)
{
	_Bool m1Empty = isMatrixEmpty(m1);
	_Bool m2Empty = isMatrixEmpty(m2);

	if (m1Empty || m2Empty)
	{
		printf("\nImpossible to compute due to empty matrix\n");
		return m1;
	}
	else if((m1.colCount == m2.colCount) && (m1.rowCount == m2.rowCount))
	{
		Matrix matrix;
		matrix = createAndAllocateMatrix(m1.rowCount, m1.colCount);

		rowElement* m1RowElem;
		m1RowElem = m1.rows;
		rowElement* m2RowElem;
		m2RowElem = m2.rows;
		rowElement* mRowElem;
		mRowElem = matrix.rows;

		cellElement* m1CellElem;
		cellElement* m2CellElem;
		cellElement* mCellElem;

		while (m1RowElem != NULL)
		{	
			m1CellElem = m1RowElem->row;
			m2CellElem = m2RowElem->row;
			mCellElem = mRowElem->row;

			while(m1CellElem != NULL)
			{
				mCellElem->value = m1CellElem->value && m2CellElem->value;
				
				m1CellElem = m1CellElem->nextCol;
				m2CellElem = m2CellElem->nextCol;
				mCellElem = mCellElem->nextCol;
			}
			m1RowElem = m1RowElem->nextRow;
			m2RowElem = m2RowElem->nextRow;
			mRowElem = mRowElem->nextRow;
		}
		return matrix;
	}
	printf("\nThe two input matrix have not the same size\n");
	return m1;
}

_Bool isColumnEmpty(Matrix m, int nCol)
{
	if (isMatrixEmpty(m))
	{
		return 1;
	}
	if(nCol < 0)
	{
		return 1;
	}
	if(nCol >= m.colCount)
	{
		return 1;	
	}
	
	colElement* mColElem;
	mColElem = m.cols;
	
	while(mColElem->colN < nCol)
	{
		mColElem = mColElem->nextCol;
	}

	if(mColElem->colN == nCol)
	{
		return 0;
	}
		return 1;
}

_Bool isRowEmpty(Matrix m, int nRow)
{
	if (isMatrixEmpty(m))
	{
		return 1;
	}
	if(nRow < 0)
	{
		return 1;
	}
	if(nRow >= m.rowCount)
	{
		return 1;	
	}

	rowElement* mRowElem;
	mRowElem = m.rows;
	
	while(mRowElem->rowN < nRow)
	{
		mRowElem = mRowElem->nextRow;
	}

	if(mRowElem->rowN == nRow)
	{
		return 0;
	}
		return 1;
}


Matrix andColSequenceOnMatrix(Matrix m)
{
	if (isMatrixEmpty(m))
	{
		printf("\nEmpty matrix, unable to compute the operation\n");
		return m;
	}

	colElement* colElem;
	colElem = m.cols;

	if (colElem->nextCol == NULL)
	{
		printf("\nThe matrix has not enough colum to compute the operation, it will be returned without any modification\n");
		return m;
	}	

	Matrix newMatrix;
	newMatrix = createAndAllocateMatrix(m.rowCount, m.colCount-1);
	colElement* newColElem;
	cellElement* newCell;
	newColElem = newMatrix.cols;
	newCell = newColElem->col;

	cellElement* cell;
	
	while (colElem->nextCol != NULL)
	{
		cell = colElem->col;
		newCell = newColElem->col;

		while (cell != NULL)
		{
			newCell->value = cell->value && cell->nextCol->value;		

			newCell = newCell->nextRow;
			cell = cell->nextRow;
		}
		
		colElem = colElem->nextCol;
		newColElem = newColElem->nextCol;
	}
	
	
	
	return newMatrix;
}


Matrix orColSequenceOnMatrix(Matrix m)
{
	if (isMatrixEmpty(m))
	{
		printf("\nEmpty matrix, unable to compute the operation\n");
		return m;
	}

	colElement* colElem;
	colElem = m.cols;

	if (colElem->nextCol == NULL)
	{
		printf("\nThe matrix has not enough colum to compute the operation, it will be returned without any modification\n");
		return m;
	}	

	Matrix newMatrix;
	newMatrix = createAndAllocateMatrix(m.rowCount, m.colCount-1);
	colElement* newColElem;
	cellElement* newCell;
	newColElem = newMatrix.cols;
	newCell = newColElem->col;

	cellElement* cell;
	
	while (colElem->nextCol != NULL)
	{
		cell = colElem->col;
		newCell = newColElem->col;

		while (cell != NULL)
		{
			newCell->value = cell->value || cell->nextCol->value;		

			newCell = newCell->nextRow;
			cell = cell->nextRow;
		}
		
		colElem = colElem->nextCol;
		newColElem = newColElem->nextCol;
	}
	
	
	
	return newMatrix;
}


Matrix andRowSequenceOnMatrix(Matrix m)
{
	if (isMatrixEmpty(m))
	{
		printf("\nEmpty matrix, unable to compute the operation\n");
		return m;
	}

	rowElement* rowElem;
	rowElem = m.rows;

	if (rowElem->nextRow == NULL)
	{
		printf("\nThe matrix has not enough rows to compute the operation, it will be returned without any modification\n");
		return m;
	}	

	Matrix newMatrix;
	newMatrix = createAndAllocateMatrix(m.rowCount-1, m.colCount);
	rowElement* newRowElem;
	cellElement* newCell;
	newRowElem = newMatrix.rows;
	newCell = newRowElem->row;

	cellElement* cell;
	
	while (rowElem->nextRow != NULL)
	{
		cell = rowElem->row;
		newCell = newRowElem->row;

		while (cell != NULL)
		{
			newCell->value = cell->value && cell->nextRow->value;		

			newCell = newCell->nextCol;
			cell = cell->nextCol;
		}
		
		rowElem = rowElem->nextRow;
		newRowElem = newRowElem->nextRow;
	}
	
	
	
	return newMatrix;
}


Matrix orRowSequenceOnMatrix(Matrix m)
{
	if (isMatrixEmpty(m))
	{
		printf("\nEmpty matrix, unable to compute the operation\n");
		return m;
	}

	rowElement* rowElem;
	rowElem = m.rows;

	if (rowElem->nextRow == NULL)
	{
		printf("\nThe matrix has not enough rows to compute the operation, it will be returned without any modification\n");
		return m;
	}	

	Matrix newMatrix;
	newMatrix = createAndAllocateMatrix(m.rowCount-1, m.colCount);
	rowElement* newRowElem;
	cellElement* newCell;
	newRowElem = newMatrix.rows;
	newCell = newRowElem->row;

	cellElement* cell;
	
	while (rowElem->nextRow != NULL)
	{
		cell = rowElem->row;
		newCell = newRowElem->row;

		while (cell != NULL)
		{
			newCell->value = cell->value || cell->nextRow->value;		

			newCell = newCell->nextCol;
			cell = cell->nextCol;
		}
		
		rowElem = rowElem->nextRow;
		newRowElem = newRowElem->nextRow;
	}
	
	
	
	return newMatrix;
}


Matrix xorMatrix(Matrix m1, Matrix m2)
{
	_Bool m1Empty = isMatrixEmpty(m1);
	_Bool m2Empty = isMatrixEmpty(m2);

	if (m1Empty || m2Empty)
	{
		printf("\nImpossible to compute due to empty matrix\n");
		return m1;
	}
	else if((m1.colCount == m2.colCount) && (m1.rowCount == m2.rowCount))
	{
		rowElement* m1RowElem;
		m1RowElem = m1.rows;
		rowElement* m2RowElem;
		m2RowElem = m2.rows;

		cellElement* m1CellElem;
		cellElement* m2CellElem;

		while (m1RowElem != NULL)
		{	
			m1CellElem = m1RowElem->row;
			m2CellElem = m2RowElem->row;

			while(m1CellElem != NULL)
			{
				m1CellElem->value = (m1CellElem->value && !m2CellElem->value) || (!m1CellElem->value && m2CellElem->value);
				
				m1CellElem = m1CellElem->nextCol;
				m2CellElem = m2CellElem->nextCol;
			}
			m1RowElem = m1RowElem->nextRow;
			m2RowElem = m2RowElem->nextRow;
		}
		return m1;
	}
	printf("\nThe two input matrix have not the same size\n");
	return m1;
}

Matrix copyMatrix(Matrix m1, Matrix m2)
{
	_Bool m1Empty = isMatrixEmpty(m1);
	_Bool m2Empty = isMatrixEmpty(m2);

	if (m1Empty || m2Empty)
	{
		return m1;
	}
	else if((m1.colCount == m2.colCount) && (m1.rowCount == m2.rowCount))
	{
		rowElement* m1RowElem;
		m1RowElem = m1.rows;

		rowElement* m2RowElem;
		m2RowElem = m2.rows;

		cellElement* m1CellElem;
		cellElement* m2CellElem;

		while (m1RowElem != NULL)
		{	
			m1CellElem = m1RowElem->row;
			m2CellElem = m2RowElem->row;

			while(m1CellElem != NULL)
			{
				m1CellElem->value = m2CellElem->value;
				
				m1CellElem = m1CellElem->nextCol;
				m2CellElem = m2CellElem->nextCol;
			}
			m1RowElem = m1RowElem->nextRow;
			m2RowElem = m2RowElem->nextRow;
		}
		return m1;
	}
	printf("\nThe two input matrix have not the same size\n");
	return m1;
}

int power(int x, int n)
{
	int i=0;
	int result = x;
	if (n == 0)
	{
		return 1;
	}

	for (i=0; i<n-1; i++)
	{
		result = result*x;
	}
	return result;
}

Matrix applyRule(Matrix m, int ruleID, int times)
{	
	Matrix m1 = createAndAllocateMatrix(m.rowCount,m.colCount);
	Matrix m2 = createAndAllocateMatrix(m.rowCount,m.colCount);
	m1 = copyMatrix(m1,m);

	if (ruleID<512 && ruleID>0)
	{
		int k = 0;
		for(k=0;k<times;k++)
		{
			m = copyMatrix(m,m1);
			int result = ruleID;
			int n = 0, i = 0;
	
			while (result != 0)
			{
				if (result%2 == 1)
				{
					i++;
					if (i == 1)
					{
						m1 = matRule(m1,power(2,n));
					}
					else
					{
						m2 = copyMatrix(m2,m);
						m2 = matRule(m2,power(2,n));
						m1 = xorMatrix(m1,m2);
					}
				}
				result = result/2;
				n++;

			}
		}
	}
	else
	{
		printf("Wrong Rule id");
	}
	freeMatrix(m2);
	m = copyMatrix(m,m1);
	freeMatrix(m1);
	return m;		
 }


Matrix matRule(Matrix m, int ruleID)
{		
	/*printf("RuleID = %i\n",ruleID);*/
	switch(ruleID)
	{
		case 2 :
			m = rule2(m);
		break;
		
		case 4 :
			m = rule2(m);
			m = rule8(m);

		break;
		
		case 8 :
			m = rule8(m);
		break;

		case 16 :
			m = rule8(m);
			m = rule32(m);				
		break;

		case 32 :
			m = rule32(m);	
		break;

		case 64 :
			m = rule128(m);
			m = rule32(m);
		break;

		case 128 :
			m = rule128(m);
		break;

		case 256 :
			m = rule2(m);
			m = rule128(m);
		break;
	}

	return m;
}

Matrix rule2(Matrix m)
{
	if (isMatrixEmpty(m))
	{
		return m;
	}
	
	if (m.colCount == 1)
	{
		colElement* colElem;
		colElem = m.cols;
		
		cellElement* cellElem;
		cellElem = colElem->col;
		
		while(cellElem != NULL)
		{
			cellElem->value = 0;
			cellElem = cellElem->nextRow;
		}
	
	}
	else
	{
		colElement* colElem;
		colElem = m.cols;
		
		colElement* nextColElem;
		nextColElem = colElem->nextCol;

		cellElement* cellElem;
		cellElement* nextCellElem;

		while (nextColElem != NULL)
		{	
			cellElem = colElem->col;
			nextCellElem = nextColElem->col;

			while(cellElem != NULL)
			{
				cellElem->value = nextCellElem->value;
				cellElem = cellElem->nextRow;
				nextCellElem = nextCellElem->nextRow;
			}
			colElem = colElem->nextCol;
			nextColElem = nextColElem->nextCol;
		}
		
		cellElem = colElem->col;
		while(cellElem != NULL)
		{
			cellElem->value = 0;
			cellElem = cellElem->nextRow;
		}
	}
	return m;
}

Matrix rule8(Matrix m)
{
	if (isMatrixEmpty(m))
	{
		return m;
	}
	
	if (m.rowCount == 1)
	{
		rowElement* rowElem;
		rowElem = m.rows;
		
		cellElement* cellElem;
		cellElem = rowElem->row;
		
		while(cellElem != NULL)
		{
			cellElem->value = 0;
			cellElem = cellElem->nextCol; 
		}
	
	}
	else
	{
		rowElement* rowElem;
		rowElem = m.rows;
		
		rowElement* nextRowElem;
		nextRowElem = rowElem->nextRow;

		cellElement* cellElem;
		cellElement* nextCellElem;

		while (nextRowElem != NULL)
		{	
			cellElem = rowElem->row;
			nextCellElem = nextRowElem->row;

			while(cellElem != NULL)
			{
				cellElem->value = nextCellElem->value;
				cellElem = cellElem->nextCol;
				nextCellElem = nextCellElem->nextCol;      
			}
			rowElem = rowElem->nextRow;
			nextRowElem = nextRowElem->nextRow;
		}
		
		cellElem = rowElem->row;
		while(cellElem != NULL)
		{
			cellElem->value = 0;
			cellElem = cellElem->nextCol;  
		}
	}
	return m;
}

Matrix rule32(Matrix m)
{
	if (isMatrixEmpty(m))
	{
		return m;
	}
	
	if (m.colCount == 1)
	{
		colElement* colElem;
		colElem = m.cols;
		
		cellElement* cellElem;
		cellElem = colElem->col;
		
		while(cellElem != NULL)
		{
			cellElem->value = 0;
			cellElem = cellElem->nextRow;
		}
	
	}
	else
	{
		colElement* colElem;
		
		colElement* nextColElem;
		nextColElem = m.cols;

		cellElement* cellElem;
		cellElement* nextCellElem;
		
		while(nextColElem->nextCol != NULL)
		{
			nextColElem = nextColElem->nextCol;
		}
		colElem = nextColElem->prevCol;

		while (colElem != NULL)
		{	
			cellElem = colElem->col;
			nextCellElem = nextColElem->col;

			while(cellElem != NULL)
			{
				nextCellElem->value = cellElem->value;
				cellElem = cellElem->nextRow;
				nextCellElem = nextCellElem->nextRow;
			}
			colElem = colElem->prevCol;
			nextColElem = nextColElem->prevCol;
		}
		
		cellElem = nextColElem->col;
		while(cellElem != NULL)
		{
			cellElem->value = 0;
			cellElem = cellElem->nextRow;
		}
	}
	return m;
}

Matrix rule128(Matrix m)
{
	if (isMatrixEmpty(m))
	{
		return m;
	}
	
	if (m.rowCount == 1)
	{
		rowElement* rowElem;
		rowElem = m.rows;
		
		cellElement* cellElem;
		cellElem = rowElem->row;
		
		while(cellElem != NULL)
		{
			cellElem->value = 0;
			cellElem = cellElem->nextCol;
		}
	
	}
	else
	{
		rowElement* rowElem;
		
		rowElement* nextRowElem;
		nextRowElem = m.rows;

		cellElement* cellElem;
		cellElement* nextCellElem;
		
		while(nextRowElem->nextRow != NULL)
		{
			nextRowElem = nextRowElem->nextRow;
		}
		rowElem = nextRowElem->prevRow;

		while (rowElem != NULL)
		{	
			cellElem = rowElem->row;
			nextCellElem = nextRowElem->row;

			while(cellElem != NULL)
			{
				nextCellElem->value = cellElem->value;
				cellElem = cellElem->nextCol;		
				nextCellElem = nextCellElem->nextCol;	
			}
			rowElem = rowElem->prevRow;
			nextRowElem = nextRowElem->prevRow;
		}
		
		cellElem = nextRowElem->row;
		while(cellElem != NULL)
		{
			cellElem->value = 0;
			cellElem = cellElem->nextCol;			
		}
	}
	return m;
}

void freeMatrix(Matrix m)
{
	if(!isMatrixEmpty(m))
	{
		rowElement* rowElem;
		rowElem = m.rows;
		while(rowElem->nextRow != NULL)
		{
			rowElem = rowElem->nextRow;
		}

		colElement* colElem;
		colElem = m.cols;
		while(colElem->nextCol != NULL)
		{
			colElem = colElem->nextCol;
		}

		cellElement* cellElem1;
		cellElement* cellElem2;

		while(colElem != NULL)
		{
			cellElem1 = colElem->col;
			cellElem2 = cellElem1->nextRow;

			while(cellElem1 != NULL)
			{
				free(cellElem1);
				cellElem1 = cellElem2;
				if(cellElem2 != NULL)
				{
					cellElem2 = cellElem2->nextRow;
				}
			}
			colElem = colElem->prevCol;
			if(colElem == NULL)
			{
				free(m.cols);
			}
			else
			{
				free(colElem->nextCol);
			}
		}

		while(rowElem != NULL)
		{
			rowElem = rowElem->prevRow;
			if(rowElem == NULL)
			{
				free(m.rows);
			}
			else
			{
				free(rowElem->nextRow);
			}
		}
	}
}

