#include <iostream>
using namespace std;

int divide(int dividend, int divisor)
{
    int negative = (dividend & 0x80000000) ^ (divisor & 0x80000000);
    long int dend = dividend, sor = divisor, cnt = 0;
    if (dividend & 0x80000000)
        dend = ~dend + 1;
    if (divisor & 0x80000000)
        sor = ~sor + 1;
    while (dend >= sor)
    {
        dend = dend + (~sor + 1);
        cnt++;
    }
    if(cnt>0x7fffffff) cnt=0x7fffffff;
    return negative ? ~cnt + 1 : cnt;
}

int main()
{
    int a = -2147483648, b = -1;
    cout << divide(a, b) << endl;
    return 0;
}