#include <iostream>
#include <string>
using namespace std;

int matchTail(string s, string p)
{
    int index, index = s.length() - 1;
    if (p.find('*') != string::npos)
    {
        index = matchTail(s, p.substr(p.find('*')+1));
    }
    for (int i = p.find('*'); i >= 0; i--)
    {
        if (s[index] == p[i])
            index--;
    }
    return index;
}

bool isMatch(string s, string p)
{
    if (p.find('*') != string::npos)
    {
        int index = matchTail(s, p.substr(p.find('*')+1));
    }
    int len = 0;
    bool any = false;
    for (int i = 0; i < p.length(); i++)
    {
        if (len == s.length())
            return false;
        if (p[i] == '.')
        {
            any = true;
            len++;
        }
        else if (p[i] == '*' && len != 0)
        {
            if (!any)
                while (s[len] == s[len - 1])
                    len++;
            else if (any && i == p.length() - 1)
                return true;
        }
        else if (p[i] == s[len])
        {
            len++;
            any = false;
        }
    }
}

int main()
{
    string str1 = "ab", str2 = ".*c";
    cout << (isMatch(str1, str2) ? "true" : "false") << endl;

    return 0;
}
