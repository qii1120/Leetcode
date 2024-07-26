#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int maxScore(string s) {
    int dp[s.length()], dp2[s.length()], maxScore=0;
    dp[0]=(s[0]=='1'?0:1);
    dp2[s.length()-1]=(s[s.length()-1]=='1'?1:0);
    for(int i=1;i<s.length()-1;i++)
    {
        if(s[i]=='0') dp[i]=dp[i-1]+1;
        else dp[i]=dp[i-1];
    }
    dp[s.length()-1]=dp[s.length()-2];

    for(int i=s.length()-2;i>=0;i--)
    {
        if(s[i]=='1') dp2[i]=dp2[i+1]+1;
        else dp2[i]=dp2[i+1];
        if(i==0) dp2[0]=dp2[1];
        maxScore = max(maxScore, dp[i]+dp2[i]);
    }

    return maxScore;
}
int main()
{
    string str="00";
    cout<<maxScore(str)<<endl;
    return 0;
}



