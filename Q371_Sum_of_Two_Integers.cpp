#include <iostream>
using namespace std;

int getSum(int a, int b)
{
    int cout = a & b, rem = a ^ b;
    while (cout)
    {
        long int cc = cout << 1;
        cout = rem & cc;
        rem = rem ^ (cc);
        
    }
    return rem;
}

int main()
{
    int a = -1, b = 2;
    cout<<getSum(a, b)<<endl;
    int c = 2, d = 3;
    cout<<getSum(c, d)<<endl;
    return 0;
}