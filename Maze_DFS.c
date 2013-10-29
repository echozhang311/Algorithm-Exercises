// Walk out of a 2D maze. 
// We can go 4 directions: right, down, left, up.
// 0 means pass, 1 means wall,can't pass

// Depth First Search

/*
 From http://learn.akae.cn/media/ch12s03.html
 
 定义一个二维数组：
 
 int maze[5][5] = {
 0, 1, 0, 0, 0,
 0, 1, 0, 1, 0,
 0, 0, 0, 0, 0,
 0, 1, 1, 1, 0,
 0, 0, 0, 1, 0,
 };
 它表示一个迷宫，其中的1表示墙壁，0表示可以走的路，只能横着走或竖着走，不能斜着走，要求编程序找出从左上角到右下角的路线。
*/

#include <stdio.h>

#define MAX_ROW		5
#define MAX_COL		5
#define	VISITED		2

#define GETROW(x)	((x)/MAX_COL)
#define GETCOL(x)	((x)%MAX_COL)
#define GETINDEX(x,y)	(((x)*MAX_COL)+y)

typedef struct MY_POINT
{
	int row;
	int col;
}myPoint;

myPoint myStack[25];
int nTop = 0;

int maze[5][5] = {
	0, 1, 0, 0, 0,
	0, 1, 0, 1, 0,
	0, 0, 0, 0, 0,
	0, 1, 1, 1, 0,
	0, 0, 0, 1, 0,
};

int predecessor[25] = {-1};

void push(myPoint point)
{
	myStack[nTop++] = point;
}

myPoint pop()
{
	return myStack[--nTop];
}

int isEmpty()
{
	return (nTop == 0);
}

void visit(int nRow, int nCol, myPoint prePoint)
{
	myPoint visitingPoint = {nRow, nCol};
	push(visitingPoint);
	maze[visitingPoint.row][visitingPoint.col] = VISITED;

	// save predecessor
	predecessor[GETINDEX(nRow, nCol)] = GETINDEX(prePoint.row, prePoint.col);
}
 
void printPath()
{
	printf("(%d,%d)\n", MAX_ROW-1, MAX_COL-1);

	// end point index in predecessor array
	int indexOfPoint = (MAX_COL-1)*MAX_COL+(MAX_ROW-1);
	while (predecessor[indexOfPoint] != -1)
	{
		printf("(%d,%d)\n", GETROW(predecessor[indexOfPoint]), GETCOL(predecessor[indexOfPoint]));
		indexOfPoint = predecessor[indexOfPoint];
    }
}

int maze_DFS()
{
	if (isEmpty())
		return 0;

	myPoint step = pop();

	if ((step.col == (MAX_COL-1)) && (step.row == (MAX_ROW-1)))
		return 1;
	
	// Look left for the next step
	if (((step.col-1) >= 0) && (maze[step.row][step.col-1] == 0))
	{
		visit(step.row, step.col-1, step);
	}
	// Look up for the next step
	if (((step.row-1) >= 0) && (maze[step.row-1][step.col] == 0))
	{
		visit(step.row-1, step.col, step);
	}
	// Look right for the next step
	if (((step.col+1) <= (MAX_COL-1)) && (maze[step.row][step.col+1] == 0))
	{
		visit(step.row, step.col+1, step);
	}
	// Look down for the next step
	if (((step.row+1) <= (MAX_ROW-1)) && (maze[step.row+1][step.col] == 0))
	{
		visit(step.row+1, step.col, step);
	}

	return maze_DFS();
}

int main()
{
	// first step
	myPoint step = {0,0};
	push(step);
	maze[0][0] = VISITED;

	if (maze_DFS())
		printPath();
	else
		printf("Can't find the path out");

	return 0;
}