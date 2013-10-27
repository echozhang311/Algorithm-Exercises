
// Walk out of a 2D maze. 
// We can go 4 directions: right, down, left, up.
// 0 means pass, 1 means wall,can't pass

// Used vector from C++ to save path we've walked.

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

#include <vector>
#include <iostream>

#define MAX_COL 5
#define MAX_ROW	5
#define NO_GO	2

using namespace std;

int maze[5][5] = {
	0, 1, 0, 0, 0,
	0, 1, 0, 1, 0,
	0, 0, 0, 0, 0,
	0, 1, 1, 1, 0,
	0, 0, 0, 1, 0,
};


typedef struct MY_POINT
{
	int nCol;
	int nRow;
}myPoint;

void printPath(const vector<myPoint> & points)
{
    cout << "\n*** Print path ***" << endl;
    
	vector<myPoint>::const_iterator it;
	for (it = points.begin(); it != points.end(); it++)
	{
		cout << "(" << (*it).nRow << "," << (*it).nCol << ")" << endl;
	}
}

int main(void)
{   
	// starting point
	myPoint step;
	step.nCol = 0;
	step.nRow = 0;

	// save every step of the path we've walked
	vector<myPoint> history;
    history.push_back(step);

	// this is no longer the right way to go, otherwise we may go into a dead loop
	maze[0][0] = NO_GO;

    while ( 1 ) 
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
			history.push_back(step);

			// block this point
			maze[step.nRow][step.nCol] = NO_GO;
            cout << "go ahead (" << step.nRow << "," << step.nCol << ")" << endl;
		}
		else if (((step.nCol+1) <= (MAX_COL-1)) && (maze[step.nRow][step.nCol+1] == 0))
		{

			//advance one step to the right
			step.nCol++;
			history.push_back(step);

			// block this point
			maze[step.nRow][step.nCol] = NO_GO;
            cout << "go ahead (" << step.nRow << "," << step.nCol << ")" << endl;
		}
		else if (((step.nCol-1) >= 0) && (maze[step.nRow][step.nCol-1] == 0))
		{

			//advance one step to the left
			step.nCol--;
			history.push_back(step);

			// block this point
			maze[step.nRow][step.nCol] = NO_GO;
            cout << "go ahead (" << step.nRow << "," << step.nCol << ")" << endl;
		}
		else if (((step.nRow-1) >= 0) && (maze[step.nRow-1][step.nCol] == 0))
		{

			//advance one step to the top
			step.nRow--;
			history.push_back(step);

			// block this point
			maze[step.nRow][step.nCol] = NO_GO;
            cout << "go ahead (" << step.nRow << "," << step.nCol << ")" << endl;
		}
		else
		{
			//no way to go, back track the path we've walked

			// remove last step from history
			history.pop_back();
            
            if ( ! history.empty()) 
            {
                // retrieve previous step
                step = history.back();
            
                cout << "pop back (" << step.nRow << "," << step.nCol << ")" << endl;
            }
            else
            {
                // empty. No way to go
                break;
            }
		}
	}

	if (history.empty())
		cout << "No path to go!" << endl;
	else
		printPath(history);
}