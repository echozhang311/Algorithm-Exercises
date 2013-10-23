
// Binary Search a pre-sorted array, return index of the 1st match

// Referenced from: http://learn.akae.cn/media/ch11s06.html

/*
Question 1: 本节的折半查找算法有一个特点：如果待查找的元素在数组中有多个则返回其中任意一个，以本节定义的数组int a[8] = { 1, 2, 2, 2, 5, 6, 8, 9 };为例，如果调用binarysearch(2)则返回3，即a[3]，而有些场合下要求这样的查找返回a[1]，也就是说，如果待查找的元素在数组中有多个则返回第一个。请修改折半查找算法实现这一特性。
*/

#include <iostream>

using namespace std;


int BinarySearch(int a[], int nStart, int nEnd, int key)
{
    // Base Case
	if (nStart > nEnd)
	{
        return -1; // can't find it
    }
    
    if (a[nStart] == key)
    {
        return nStart; // the 1st match
    }
    
    // The pivot
    int nMid = (nStart+nEnd)/2;
    if (a[nMid] == key)
    {
        return BinarySearch(a, nStart, nMid, key);// keep searching the left half
    }
    else if (a[nMid] < key)
    {
        return BinarySearch(a, nMid+1, nEnd, key);// keep searching the right half
    }
    else if (a[nMid] > key)
    {
        return BinarySearch(a, nStart, nMid-1, key);// keep searching the left half
    }
}

// Test it

int main()
{
    int nIndex;
    
    int a[8] = {1,2,2,2,5,6,8,9};
    nIndex = BinarySearch(a, 0, 7, 2);// returns 1
    cout << "Index of 1st match of a array is:" << nIndex << endl;
    
    int b[10] = {1,1,1,1,1,1,1,2,8,9};
    nIndex = BinarySearch(b, 0, 9, 2);//returns 7
    cout << "Index of 1st match of b array is:" << nIndex << endl;

    
    int c[8] = {0,1,2,3,5,6,8,9};
    nIndex = BinarySearch(c, 0, 7, 2);// returns 2
    cout << "Index of 1st match of c array is:" << nIndex << endl;
    return 0;
}