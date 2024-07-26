#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
using namespace std;
int numEquivDominoPairs(vector<vector<int> >& dominoes) {
    set<pair<int, int> > s;
    // vector<pair<pair<int, int>, int>> tmp;
    map<pair<int, int>, int> m;
    int result=0;
    for(int i=0; i<dominoes.size(); i++)
    {
        if(!(s.insert(make_pair(min(dominoes[i][0], dominoes[i][1]), max(dominoes[i][0], dominoes[i][1]))).second))
            m[make_pair(min(dominoes[i][0], dominoes[i][1]), max(dominoes[i][0], dominoes[i][1]))]+=(m[make_pair(min(dominoes[i][0], dominoes[i][1]), max(dominoes[i][0], dominoes[i][1]))]+1);
        else
            m[make_pair(min(dominoes[i][0], dominoes[i][1]), max(dominoes[i][0], dominoes[i][1]))] = 0;
    }
    for (auto i : m)
        result+=i.second;
    return result;
}
int main()
{
    vector<vector<int> > nums = {{1,2},{2,1},{3,4},{5,6}};
    nums.push_back()
    cout<<numEquivDominoPairs(nums)<<endl;
    return 0;
}