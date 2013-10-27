
// Walk out of a 2D maze. 
// We can go 4 directions: right, down, left, up.
// 0 means pass, 1 means wall,can't pass

// Use pure C to save path we've walked.

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

#define MAX_COL     5
#define MAX_ROW     5
#define NO_GO       2
#define MAX_STEPS   100

typedef struct MY_POINT
{
	int nCol;
	int nRow;
}myPoint;

myPoint stack[MAX_STEPS];

int maze[5][5] = {
	0, 1, 0, 0, 0,
	0, 1, 0, 1, 0,
	0, 0, 0, 0, 0,
	0, 1, 1, 1, 0,
	0, 0, 0, 1, 0,
};

static int n_TopOfStack = 0;



void push_back(myPoint newStep)
{
    if  (n_TopOfStack >= MAX_STEPS)
    {
        printf("History Stack Overflow!");
        return; // shouldn't come here
    }
    
    stack[n_TopOfStack++] = newStep;
}

// retrieve the top element without removing it
myPoint get_back()
{
    return stack[n_TopOfStack-1];
}

// remove the top element
void pop_back()
{
    if ((n_TopOfStack-1) < 0) 
    {
        printf("History Stack Already Empty!");
        return;
    }
    
    --n_TopOfStack;
}

int is_empty()
{
    return n_TopOfStack == 0;
}

void printPath()
{
    int i;
	for (i=0; i<n_TopOfStack; i++)
	{
        printf("(%d,%d)\n",stack[i].nRow,stack[i].nCol);
	}
 
}



int main(void)
{
    // starting point
	myPoint step;
	step.nCol = 0;
	step.nRow = 0;

	// save every step of the path we've walked
    push_back(step);

	// this is no longer the right way to go, otherwise we may go into a dead loop
	maze[0][0] = NO_GO;

    while (!(is_empty())) 
	{        
		// arrived our destination
		if ((step.nCol == (MAX_COL-1)) && (step.nRow == (MAX_ROW-1)))
		{
			break;
		}
		else if (((step.nRow+1) <= (MAX_ROW-1)) && (maze[step.nRow+1][step.nCol] == 0))
		{

			//advance one step to the bottom
			step.nRow++;
            push_back(step);

			// block this point
			maze[step.nRow][step.nCol] = NO_GO;
            printf("go ahead (%d,%d)\n",step.nRow,step.nCol);
		}
		else if (((step.nCol+1) <= (MAX_COL-1)) && (maze[step.nRow][step.nCol+1] == 0))
		{

			//advance one step to the right
			step.nCol++;
            push_back(step);

			// block this point
			maze[step.nRow][step.nCol] = NO_GO;
            printf("go ahead (%d,%d)\n",step.nRow,step.nCol);
		}
		else if (((step.nCol-1) >= 0) && (maze[step.nRow][step.nCol-1] == 0))
		{

			//advance one step to the left
			step.nCol--;
            push_back(step);

			// block this point
			maze[step.nRow][step.nCol] = NO_GO;
            printf("go ahead (%d,%d)\n",step.nRow,step.nCol);
		}
		else if (((step.nRow-1) >= 0) && (maze[step.nRow-1][step.nCol] == 0))
		{

			//advance one step to the top
			step.nRow--;
            push_back(step);

			// block this point
			maze[step.nRow][step.nCol] = NO_GO;
            printf("go ahead (%d,%d)\n",step.nRow,step.nCol);
		}
		else
		{
			//no way to go, back track the path we've walked

            // remove the last step where we have no way to go except backtrace
            pop_back();
            
			// retrieve previous step
            step = get_back();
            
            printf("pop back (%d,%d)\n",step.nRow,step.nCol);
		}
	}

	if (is_empty())
        printf("No path to go!");
	else
		printPath();
}