#include <iostream>
#include <string>
#include <string.h>
using namespace std;
int maxVowels(string s, int k)
{
    string vowels = "aeiou";
    int maxlen=0, maxt=1, tmp=0;
    for(int i=0; i<s.length(); i++,maxt++)
    {
        
        if(vowels.find(s[i])!=string::npos)
            tmp++;
        if(maxt==k||i==s.length()-1) 
        {
            maxlen=max(maxlen, tmp);
            maxt-=2;
            tmp = vowels.find(s[i-k+1])!=string::npos?tmp-1:tmp;
        }
        cout<<i<<" "<<tmp<<" "<<maxt<<" "<<maxlen<<endl;
    }
    return maxlen;
}
int main()
{
    string str = "abciiidef";
    int k = 3;
    cout<<"maxlen: "<<maxVowels(str, k)<<endl;
}