#include <iostream>
#include <string>
#include <stack>
using namespace std;

bool isValid(string s)
{
    stack<char> st;
    for(int i = 0; i <s.length();i++)
    {
        if(s[i] == '(' || s[i] == '[' || s[i] == '{')
            st.push(s[i]);
        else if(st.empty() ||(s[i] == '}' && st.top()!='{') || (s[i] == ')' && st.top()!='(') || (s[i] == ']'&&st.top()!='['))
            return false;
        else if((s[i] == '}' && st.top()=='{') || (s[i] == ')' && st.top()=='(') || (s[i] == ']'&&st.top()=='['))
            st.pop();
    }
    return st.empty()?true:false;
}


int main()
{
    string str = "]";
    if(isValid(str)) cout<<"true"<<endl;
    else cout<<"false"<<endl;
    return 0;
}
