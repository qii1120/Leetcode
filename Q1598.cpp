#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <string.h>
using namespace std;
string mergeAlternately(string word1, string word2) {
    int n=min(word1.length(), word2.length());
    if(word2.length()>word1.length()) 
        word1.append(word2.substr(word1.length()));
    for(int i=0; i<n; i++)
    {
        word1.insert(2*i+1, 1, word2[i]);
    }
    return word1;
}
int main()
{
    string word1="abcd", word2="qwerpppp";
    cout<<mergeAlternately(word1, word2)<<endl;
}