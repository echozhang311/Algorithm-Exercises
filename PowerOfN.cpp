// Use Binary Search to get the result of x to the power of n, time complex should be Ɵ(lgn)

// Referenced from http://learn.akae.cn/media/ch11s06.html

/*
3、编写一个函数double mypow(double x, int n);求x的n次方，参数n是正整数。最简单的算法是：

double product = 1;
for (i = 0; i < n; i++)
	product *= x;
这个算法的时间复杂度是Θ(n)。其实有更好的办法，比如mypow(x, 8)，第一次循环算出x·x=x2，第二次循环算出x2·x2=x4，第三次循环算出4·x4=x8。这样只需要三次循环，时间复杂度是Θ(lgn)。思考一下如果n不是2的整数次幂应该怎么处理。请分别用递归和循环实现这个算法。

*/

#include <iostream>

using namespace std;

// recusive
double power_recusive(double x, int n)
{
    if (n == 1)
        return x;
    
    int mid = n/2;
    
    // n is even number
    if (!(n%2))
    {
        double y = power_recusive(x, mid);
        return y*y;
    }
    else // n is odd number
    {
        return power_recusive(x, mid) * power_recusive(x, n-mid);
    }
}

// iterative
double power_iterative(double x, int n)
{
    double y = 1;
    int count = 0;
    
    while (count < n )
    {
        double z = x;
        int i = 1;
        
        while ((2*i) < (n-count) )
        {
            z = z*z;
            i = 2*i;
        }
        
        y = y*z;
        count += i;
    }
    
    return y;
}

// Test it

int main()
{
    cout << "2.9 to the power of 4 is: " << power_recusive(2.9, 4) << endl;  //returns 70.7281
    cout << "3.1 to the power of 3 is: " << power_recusive(3.1, 3) << endl;  //returns 29.791
    cout << "10 to the power of 7 is: " << power_recusive(10, 7) << endl;    //returns 1e+07
}