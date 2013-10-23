
// Use binary search to get square root of a given positive double

// Referenced from http://learn.akae.cn/media/ch11s06.html

/*
2、编写一个函数double mysqrt(double y);求y的正平方根，参数y是正实数。我们用折半查找来找这个平方根，在从0到y之间必定有一个取值是y的平方根，如果我们查找的数x比y的平方根小，则x2<y，如果我们查找的数x比y的平方根大，则x2>y，我们可以据此缩小查找范围，当我们查找的数足够准确时（比如满足|x2-y|<0.001），就可以认为找到了y的平方根。思考一下这个算法需要迭代多少次？迭代次数的多少由什么因素决定？
*/

#include <iostream>

using namespace std;

double SqrtRoot(double y, double left, double right)
{
    double x = (left+right)/2;
        
    // Base Case
    double diff = x*x-y;
    if ((-0.001 < diff) && (diff < 0.001))
    {
        return x;
    }
    
    if (x*x < y)
    {
        // x too small, search in the right half
        return SqrtRoot(y, x, right);
    }
    else if (x*x > y)
    {
        // x too big, search in the left half
        return SqrtRoot(y, left, x);
    }
}

// Test it

int main()
{
    
    cout << "square root of 4 is: " << SqrtRoot(4, 0, 4) << endl;           // returns 2
    cout << "square root of 9 is: " << SqrtRoot(9, 0, 9) << endl;           // returns 3.00009
    cout << "square root of 10 is: " << SqrtRoot(10, 0, 10) << endl;        // returns 3.16223
    cout << "square root of 13.3 is: " << SqrtRoot(13.3, 0, 13.3) << endl;  // returns 3.64687
    cout << "square root of 213.3 is: " << SqrtRoot(213.3, 0, 213.3) << endl;// returns 14.6048
    
    return 0;
}