// Walk out of a 2D maze. 
// We can go 4 directions: right, down, left, up.
// 0 means pass, 1 means wall,can't pass

// Breadth First Search, Circular Queue

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
#include <assert.h>

#define MAX_ROW		5
#define MAX_COL		5
#define QUEUE_LEN   25
#define	VISITED		2

#define false       0
#define true        1

typedef struct MY_POINT
{
	int row;
	int col;
}myPoint;


int maze[MAX_ROW][MAX_COL] = {
	0, 1, 0, 0, 0,
	0, 1, 0, 1, 0,
	0, 0, 0, 0, 0,
	0, 1, 1, 1, 0,
	0, 0, 0, 1, 0,
};

myPoint queue[QUEUE_LEN];
int m_nHead = -1;
int m_nTail = -1;

int push_back(myPoint step)
{
    // full
    if (((m_nTail+1) == m_nHead) || ((m_nHead == 0) && (m_nTail == (QUEUE_LEN-1))))
    {
        return false;
    }
    
    if (m_nTail == -1)
    {
        m_nTail++;
        m_nHead++;
    }
    else if ((m_nTail+1) == QUEUE_LEN)
    {
        // jump to the beginning of queue
        m_nTail = 0;
    }
    else
    {
        // forward one step
        m_nTail++;
    }
        
    queue[m_nTail] = step;
    return true;
}

int pop_front(myPoint *step)
{
    // empty
    if (m_nHead == -1)
    {
        return false;
    }
    
    step->row = queue[m_nHead].row;
    step->col = queue[m_nHead].col;
    
    if (m_nHead == m_nTail)
    {
        m_nHead = m_nTail = -1;
    }
    else if ((m_nHead+1) == QUEUE_LEN)
    {
        m_nHead = 0;
    }
    else
    {
        m_nHead++;
    }
    
    return true;
}

int is_empty()
{
    return (m_nHead == -1);
}

void visit(int row, int col)
{
    myPoint visitingPoint = {row, col};
    assert(push_back(visitingPoint));
    maze[row][col] = VISITED;
    
    printf("push point (%d,%d)\n", row, col);
}


int maze_BFS()
{
    if (is_empty())
    {
        // fail to find the path out
        return 0;
    }
    
    myPoint step;
    assert(pop_front(&step));
    printf("pop point (%d,%d)\n", step.row, step.col);
    
   if ((step.row == (MAX_ROW-1)) && (step.col == (MAX_COL-1)))
    {
        // arrived destination
        return 1;
    }
    
    // look down
    if (((step.row+1) <= (MAX_ROW-1)) && (maze[step.row+1][step.col] == 0)) 
    {
        visit(step.row+1, step.col);
    }
    // look right
    if (((step.col+1) <= (MAX_COL-1)) && (maze[step.row][step.col+1] == 0)) 
    {
        visit(step.row, step.col+1);
    }
    // look up
    if (((step.row-1) >= 0) && (maze[step.row-1][step.col] == 0)) 
    {
        visit(step.row-1, step.col);
    }
    // look left
    if (((step.col-1) >= 0) && (maze[step.row][step.col-1] == 0)) 
    {
        visit(step.row, step.col-1);
    }
    
    return maze_BFS();
}

int main()
{
    myPoint step = {0,0};
    push_back(step);
    maze[0][0] = VISITED;
    
    if (maze_BFS())
        printf("Find a path out successfully!\n");
    else
        printf("Fail to find a path out!\n");
    
    return 0;
}