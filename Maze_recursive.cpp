
// Walk out of a 2D maze. 
// We can go 4 directions: right, down, left, up.
// 0 means pass, 1 means wall,can't pass

// Use recursion

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


class myPoint
{
public:
	int nCol;
	int nRow;
    
    myPoint():nCol(0), nRow(0)
    {
        
    }
    
    myPoint(int row, int col):nRow(row), nCol(col)
    {
        
    }
};


bool mazewalk(vector<myPoint> & history, myPoint currentPoint)
{
    if (((currentPoint.nCol+1) == MAX_COL) && ((currentPoint.nRow+1) == MAX_ROW))
        return true;
    
    
    if (((currentPoint.nRow+1) <= (MAX_ROW-1)) && (maze[currentPoint.nRow+1][currentPoint.nCol] == 0))
    {
        
        //advance one step to the bottom
        currentPoint.nRow++;
        history.push_back(currentPoint);
        
        // block this point
        maze[currentPoint.nRow][currentPoint.nCol] = NO_GO;
        cout << "go ahead (" << currentPoint.nRow << "," << currentPoint.nCol << ")" << endl;
    }
    else if (((currentPoint.nCol+1) <= (MAX_COL-1)) && (maze[currentPoint.nRow][currentPoint.nCol+1] == 0))
    {
        
        //advance one step to the right
        currentPoint.nCol++;
        history.push_back(currentPoint);
        
        // block this point
        maze[currentPoint.nRow][currentPoint.nCol] = NO_GO;
        cout << "go ahead (" << currentPoint.nRow << "," << currentPoint.nCol << ")" << endl;
    }
    else if (((currentPoint.nCol-1) >= 0) && (maze[currentPoint.nRow][currentPoint.nCol-1] == 0))
    {
        
        //advance one step to the left
        currentPoint.nCol--;
        history.push_back(currentPoint);
        
        // block this point
        maze[currentPoint.nRow][currentPoint.nCol] = NO_GO;
        cout << "go ahead (" << currentPoint.nRow << "," << currentPoint.nCol << ")" << endl;
    }
    else if (((currentPoint.nRow-1) >= 0) && (maze[currentPoint.nRow-1][currentPoint.nCol] == 0))
    {
        
        //advance one step to the top
        currentPoint.nRow--;
        history.push_back(currentPoint);
        
        // block this point
        maze[currentPoint.nRow][currentPoint.nCol] = NO_GO;
        cout << "go ahead (" << currentPoint.nRow << "," << currentPoint.nCol << ")" << endl;
    }
    else
    {
        // No way to go in current route. Back track to find another way
        history.pop_back();
        
        if (history.empty())
        {
            return false;
        }
        
        currentPoint = history.back();
        cout << "pop back (" << currentPoint.nRow << "," << currentPoint.nCol << ")" << endl;
    }
    
    return mazewalk(history, currentPoint);
}

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
    // array to save steps we've already walked
	vector<myPoint> history;
    
    // the first step
	myPoint step;
    
    // save the first step to array
    history.push_back(step);
    
    if (mazewalk(history, step) == false)
		cout << "No path to go!" << endl;
    else
		printPath(history);
        
}